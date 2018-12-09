using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using InTheHand.Windows.Forms;
using InTheHand.Net;

namespace pinghengxiaoche {
    public partial class MainWindow : Form {

        private Color BorderColor = Color.FromArgb(41, 204, 41);
        private Brush BorderBrush;
        private Pen BorderPen;

        private ControlBorderManager bordermanager = new ControlBorderManager();


        private int button_Connect_State;    //0：显示“连接”  1：显示“连接中” 2：显示“已连接”
        private float button_Connect_CurrentBorderLen;
        private Graphics button_Connect_Graphics;

        private int button_Send_State;    //0：显示“发送”  1：显示“正在发送” 


        private string FormerValue;


        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            BorderBrush = new SolidBrush(BorderColor);
            BorderPen = new Pen(BorderBrush, 1);
            button_Connect_State = 0;
            button_Connect_CurrentBorderLen = 0;
            button_Connect_Graphics = button_Connect.CreateGraphics();

            dataGridView_Variables.MouseWheel += new System.Windows.Forms.MouseEventHandler(dataGridView_Variables_MouseWheel);

            bordermanager.AddControlGroup(
                this,
                new Control[] { textBox_Receive, scrollBar_Receive },
                Color.FromArgb(80, 80, 80),
                Color.FromArgb(150, 150, 150),
                BorderColor,
                () =>
                {
                    return new Rectangle(
                        textBox_Receive.Left - 1,
                        textBox_Receive.Top - 1,
                        textBox_Receive.Width + scrollBar_Receive.Width + 1,
                        textBox_Receive.Height + 1
                        );
                });

            bordermanager.AddControlGroup(
                this,
                new Control[] { textBox_Send, scrollBar_Send },
                Color.FromArgb(80, 80, 80),
                Color.FromArgb(150, 150, 150),
                BorderColor,
                () =>
                {
                    return new Rectangle(
                        textBox_Send.Left - 1,
                        textBox_Send.Top - 1,
                        textBox_Send.Width + scrollBar_Send.Width + 1,
                        textBox_Send.Height + 1
                        );
                });

            bordermanager.AddControlGroup(
                this,
                new Control[] { dataGridView_Variables, button_Refresh, button_Commit },
                Color.FromArgb(80, 80, 80),
                Color.FromArgb(150, 150, 150),
                BorderColor,
                () =>
                {
                    return new Rectangle(
                        dataGridView_Variables.Left - 1,
                        dataGridView_Variables.Top - 1,
                        dataGridView_Variables.Width + 1,
                        dataGridView_Variables.Height + button_Refresh.Height + 1
                        );
                });
        }

        private void ShowBluetoothInfo()
        {
            Label_BluetoothName.Text = ProgramData.Name;
            Label_BluetoothAddress.Text = ProgramData.Address.ToString();
        }

        private void OnGetMessage()
        {
            string MessageStr = Program.CurrentMessage.Item1;
            byte[] ReceivedMsg = new byte[MessageStr.Length + 1];
            int i ;
            for(i=0;i< MessageStr.Length;i++) {
                ReceivedMsg[i] = (byte)MessageStr[i];
            }
            ReceivedMsg[i] = 0;           //计算CRC32校验时字符串结尾的'\0'也计算在内。

            UInt32 crc32 = CRC32.GetSTM32CRC32(ReceivedMsg, i + 1);

            if (crc32 == Program.CurrentMessage.Item2) {
                textBox_Receive_Append(AddNewLineMarks(MessageStr), crc32, true);

                string[] Commands = MessageStr.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);         //空命令会被去除
                foreach(string Cmd in Commands) {

                    ProcessSingleCommand(Cmd);

                }

            }
            else {
                textBox_Receive_Append("收到一条CRC32校验值不正确的消息。");
            }

        }

        private void ProcessSingleCommand(string FullCmd)
        {
            //PARSED:CRC32, nSucceeded, nTotal

            string[] Parts = FullCmd.Split(':', ',');

            for(int i = 0; i < Parts.Length; i++) {        //除去命令或者参数两遍的空格、跳格、回车符、换行符
                Parts[i] = Parts[i].Trim(' ', '\t', '\r', '\n');
            }

            try {
                switch (Parts[0].ToLower()) {
                    case "parsed":
                        textBox_Receive_Append("消息[" + Parts[1].ToUpper() + "]反馈 - 成功处理" + Parts[2] + "条，共" + Parts[3]+"条。");

                        break;
                    case "var":
                        string[] NameAndValue = Parts[1].Split('=');
                        dataGridView_Variables_Add(NameAndValue[0], NameAndValue[1]);

                        break;


                    default:
                        break;
                }
            }
            catch(Exception ex) {

            }



        }

        private string AddNewLineMarks(string Msg)
        {
            StringBuilder sb = new StringBuilder(Msg.Length * 2);
            foreach(char c in Msg) {
                if (c != ';') {
                    sb.Append(c);
                }
                else {
                    sb.Append(";\r\n");
                }
            }
            return sb.ToString();
        }

        private void OnStreamClosed()
        {
            textBox_Receive_Append("连接中断。");
            button_Connect_toClosed();
        }

        private void textBox_Receive_Append(string str)
        {
            textBox_Receive.AppendText("[" + DateTime.Now.ToLongTimeString() + "] System: " + str + "\r\n\r\n");
        }

        
        private void textBox_Receive_Append(string msg,UInt32 crc32,bool isReceive)
        {
            textBox_Receive.AppendText("[" + DateTime.Now.ToLongTimeString() + "] ");
            if (isReceive) textBox_Receive.AppendText("Reiceived[");
            else textBox_Receive.AppendText("Sent[");
            textBox_Receive.AppendText(string.Format("{0:X8}", crc32) + "]:\r\n");
            textBox_Receive.AppendText(msg.TrimEnd('\r','\n') + "\r\n\r\n");
        }


        //只读变量以"@"开头
        //会找是否已经有相应的变量，有的话就更新，没有的话才添加
        private void dataGridView_Variables_Add(string name,string value)
        {
            //row.tag: bool类型，是否被用户更改过

            string realname = name;

            if (name[0] == '@') {
                realname = name.Substring(1);
            }

            //查找列表里是不是已经有这个变量了
            foreach(DataGridViewRow row in dataGridView_Variables.Rows) {
                if ((string)row.Cells[0].Value == realname) {
                    row.Cells[1].Value = value;
                    row.Tag = false;
                    if (row.Cells[1].ReadOnly)
                        row.Cells[1].Style.ForeColor = Color.FromArgb(180, 180, 180);
                    else
                        row.Cells[1].Style.ForeColor = Color.White;
                    return;
                }
            }



            int index = dataGridView_Variables.Rows.Add();
            dataGridView_Variables.Rows[index].Tag = false;
            var c1 = dataGridView_Variables.Rows[index].Cells[0];
            var c2 = dataGridView_Variables.Rows[index].Cells[1];

            if (name[0] == '@') {
                c1.Value = realname;
                c2.Value = value;
                c2.Style.SelectionForeColor = Color.FromArgb(0, 0, 0);
                c2.Style.ForeColor = Color.FromArgb(180, 180, 180);
                c2.ReadOnly = true;

            }
            else {
                c1.Value = realname;
                c2.Value = value;
                c2.ReadOnly = false;
            }


        }

        private void dataGridView_Variables_Clear()
        {
            dataGridView_Variables.Rows.Clear();
        }



        private void button_Connect_DrawBorder(Graphics g)
        {

            int LineLen = (int)Math.Round(button_Connect_CurrentBorderLen);
            if (LineLen > 0 && LineLen <= button_Connect.Height - 1) {
                g.DrawLine(                              //画左边
                    BorderPen, 
                    new Point(0, 0), 
                    new Point(0, LineLen)
                );
            }
            else if ((LineLen -= button_Connect.Height - 1) <= button_Connect.Width - 1) {
                g.DrawLine(                              //画左边
                    BorderPen,
                    new Point(0, 0),
                    new Point(0, button_Connect.Height - 1)
                );
                g.DrawLine(                              //画下边
                    BorderPen,
                    new Point(0, button_Connect.Height - 1),
                    new Point(LineLen, button_Connect.Height - 1)
                );
            }
            else if ((LineLen -= button_Connect.Width - 1) <= button_Connect.Height - 1) {
                g.DrawLine(                              //画左边
                    BorderPen,
                    new Point(0, 0),
                    new Point(0, button_Connect.Height - 1)
                );
                g.DrawLine(                              //画下边
                    BorderPen,
                    new Point(0, button_Connect.Height - 1),
                    new Point(button_Connect.Width - 1, button_Connect.Height - 1)
                );
                g.DrawLine(                              //画右边
                    BorderPen,
                    new Point(button_Connect.Width - 1, button_Connect.Height - 1),
                    new Point(button_Connect.Width - 1, button_Connect.Height - 1 - LineLen)
                );
            }
            else {
                LineLen -= button_Connect.Height - 1;
                g.DrawLine(                              //画左边
                    BorderPen,
                    new Point(0, 0),
                    new Point(0, button_Connect.Height - 1)
                );
                g.DrawLine(                              //画下边
                    BorderPen,
                    new Point(0, button_Connect.Height - 1),
                    new Point(button_Connect.Width - 1, button_Connect.Height - 1)
                );
                g.DrawLine(                              //画右边
                    BorderPen,
                    new Point(button_Connect.Width - 1, button_Connect.Height - 1),
                    new Point(button_Connect.Width - 1, 0)
                );
                g.DrawLine(                              //画上边
                    BorderPen,
                    new Point(button_Connect.Width - 1, 0),
                    new Point(button_Connect.Width - 1 - LineLen, 0)
                );
            }
        }

        private void button_Connect_Paint(object sender, PaintEventArgs e)
        {
            if (button_Connect_State == 1) {
                button_Connect_DrawBorder(e.Graphics);
            }
        }


        private void button_Connect_toConnecting()
        {
            button_Connect_State = 1;      //正在连接

            button_Connect.Text = "连接中";

            button_Connect_CurrentBorderLen = 0;

            //这个timer使用窗体主线程调用回调函数，无需考虑多线程同步，延迟不是很精确。
            var timer = new System.Windows.Forms.Timer();   
            timer.Interval = 10;
            timer.Tick += new EventHandler((_sender, _e) =>
            {
                button_Connect_CurrentBorderLen += 2 * (button_Connect.Height + button_Connect.Width) / 60;

                if (button_Connect_CurrentBorderLen > 2 * (button_Connect.Height + button_Connect.Width) || button_Connect_State != 1) {
                    //当已经画完或者状态已经改变时
                    timer.Stop();
                    timer.Dispose();
                    return;
                }
                button_Connect_DrawBorder(button_Connect_Graphics);
            });

            timer.Start();
        }

        private void button_Connect_toConnected()
        {
            button_Connect_State = 2;      //已连接

            button_Connect.Text = "已连接";
            button_Connect.ForeColor = Color.FromArgb(255, 255, 255);

            float Opacity = 50;

            //这个timer使用窗体主线程调用回调函数，无需考虑多线程同步，延迟不是很精确。
            var timer = new System.Windows.Forms.Timer();
            timer.Interval = 10;
            timer.Tick += new EventHandler((_sender, _e) =>
            {
                Opacity += (float)(255 - 50) / (float)60;

                if (Opacity > 255 || button_Connect_State != 2) {
                    timer.Stop();
                    timer.Dispose();
                    return;
                }
                button_Connect.FlatAppearance.MouseOverBackColor =
                button_Connect.BackColor =
                button_Connect.FlatAppearance.MouseDownBackColor = Color.FromArgb((int)Opacity, BorderColor);
            });

            timer.Start();


        }
        private void button_Connect_toClosed()
        {
            button_Connect_State = 0;    //未连接

            button_Connect.Text = "连接";
            button_Connect.BackColor = Color.FromArgb(60, 60, 60);
            button_Connect.ForeColor = Color.White;
            button_Connect.FlatAppearance.MouseOverBackColor = Color.FromArgb(80, 80, 80);
            button_Connect.FlatAppearance.MouseDownBackColor = Color.Black;
        }


        private async void button_Connect_Click(object sender, EventArgs e)
        {

            if (button_Connect_State == 0) {
                try {
                    button_Connect_toConnecting();

                    await Task.Run(() =>
                    {
                        Program.OpenBluetoothSerialPort(this, OnGetMessage, OnStreamClosed);
                    });

                    textBox_Receive_Append("已连接设备:" + Label_BluetoothName.Text + "(" + Label_BluetoothAddress.Text + ")");
                    button_Connect_toConnected();

                }
                catch(Exception ex) {
                    Program.ShowErrorMessage(ex.Message);
                    button_Connect_toClosed();
                }

            }
            else if (button_Connect_State == 2) {
                try {
                    button_Connect_toClosed();
                    await Task.Run(() =>
                    {
                        Program.CloseBluetoothSerialPort();
                    });

                }
                catch (Exception ex) {
                    Program.ShowErrorMessage(ex.Message);
                    button_Connect_toClosed();
                }


            }


        }


        //如果是程序自动发的命令，传入false
        private async void SendCommands(string Cmds, bool IsUserCmd)
        {
            if (button_Send_State == 0) {
                button_Send_toSending();

                UInt32 crc32;
                    crc32 = Program.FormatBluetoothMessage(Cmds);
                    await Task.Run(() =>
                    {
                        if (!Program.sendBluetoothMessage()) {
                            textBox_Receive_Append("发送失败。");
                            button_Send_toDefault();
                        }
                    });

                    textBox_Receive_Append(Cmds, crc32, false);
                    button_Send_toDefault();

                    if (IsUserCmd) textBox_Send.Clear();

            }
        }


        private void textBox_Receive_TextChanged(object sender, EventArgs e)
        {

        }

        private void button_ChooseDevice_Click(object sender, EventArgs e)
        {
            if (button_Connect_State == 0) {
                SelectBluetoothDeviceDialog dlg = new SelectBluetoothDeviceDialog();
                dlg.ShowRemembered = true;
                dlg.ShowAuthenticated = true;
                dlg.ShowUnknown = true;
                if (dlg.ShowDialog() == DialogResult.OK) {
                    ProgramData.Address = dlg.SelectedDevice.DeviceAddress;
                    ProgramData.Name = dlg.SelectedDevice.DeviceName;
                    ShowBluetoothInfo();
                }
            }
        }



        private void button_Send_Click(object sender, EventArgs e)
        {
            SendCommands(textBox_Send.Text, true);

        }

        private void button_Send_toSending()
        {
            button_Send_State = 1;

            button_Send.FlatAppearance.BorderColor = Color.FromArgb(150, 150, 150);
            button_Send.Text = "发送中";

        }

        private void button_Send_toDefault()
        {
            button_Send_State = 0;

            button_Send.FlatAppearance.BorderColor = BorderColor;
            button_Send.Text = "发送";
        }

        private void textBox_Send_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox_Send_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.Enter) {
                SendCommands(textBox_Send.Text, true);
            }
            if (e.Control && e.KeyCode == Keys.A) {
                textBox_Send.SelectAll();
            }
        }

        private void button_ClearReiceive_Click(object sender, EventArgs e)
        {
            textBox_Receive.Clear();

        }

        private void button_ClearSend_Click(object sender, EventArgs e)
        {
            textBox_Send.Clear();
        }

        private void dataGridView_Variables_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0) {
                if (dataGridView_Variables.FirstDisplayedScrollingRowIndex > 3)
                    dataGridView_Variables.FirstDisplayedScrollingRowIndex -= 3;
                else
                    dataGridView_Variables.FirstDisplayedScrollingRowIndex = 0;
            }
            else {
                if (dataGridView_Variables.FirstDisplayedScrollingRowIndex < dataGridView_Variables.Rows.Count - 10)
                    dataGridView_Variables.FirstDisplayedScrollingRowIndex += 3;

            }
        }

        private void button_Commit_Click(object sender, EventArgs e)
        {
            StringBuilder cmd=new StringBuilder("VAR:");
            bool datachanged = false;
            foreach(DataGridViewRow row in dataGridView_Variables.Rows) {
                if ((bool)row.Tag || true) {                //如果数据有变化         ---------------------------------------------------------------------------
                    
                    if (!row.Cells[1].ReadOnly) {                    //如果不是只读变量
                        cmd.Append((string)row.Cells[0].Value + "=" + (string)row.Cells[1].Value + ",");
                        datachanged = true;
                    }
                }
            }

            if (datachanged) {       //如果至少有一个数据有改动
                cmd[cmd.Length - 1] = ';';            //将最后一个","换成";"
                cmd.Append("VAR");                    //同时刷新列表

                dataGridView_Variables_Clear();
                SendCommands(cmd.ToString(), false);
            }
            else {
                SendCommands("VAR;", false);
            }




        }

        private void button_Refresh_Click(object sender, EventArgs e)
        {
            dataGridView_Variables_Clear();
            SendCommands("VAR", false);
        }

        private void dataGridView_Variables_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            if ((string)dataGridView_Variables[e.ColumnIndex, e.RowIndex].Value != FormerValue) {
                dataGridView_Variables[e.ColumnIndex, e.RowIndex].Style.ForeColor =
                dataGridView_Variables[e.ColumnIndex, e.RowIndex].Style.SelectionForeColor = Color.FromArgb(255, 255, 0);
                dataGridView_Variables.Rows[e.RowIndex].Tag = true;
            }
        }

        private void dataGridView_Variables_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            FormerValue = (string)dataGridView_Variables[e.ColumnIndex, e.RowIndex].Value;
        }

        private void dataGridView_Variables_Leave(object sender, EventArgs e)
        {
            dataGridView_Variables.ClearSelection();
        }

        private void dataGridView_Variables_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (dataGridView_Variables[e.ColumnIndex, e.RowIndex].ReadOnly) {
                SendCommands(
                    "VAR:@" +
                    (string)dataGridView_Variables.Rows[e.RowIndex].Cells[0].Value,
                    false
                );
            }
            else {
                SendCommands(
                    "VAR:" +
                    (string)dataGridView_Variables.Rows[e.RowIndex].Cells[0].Value,
                    false
                );
            }
        }

        private void button_ShowControlWindow_Click(object sender, EventArgs e)
        {
            ControlWindow ControlWindowInstance = new ControlWindow();
            ControlWindowInstance.Show();
        }

        private void textBox_Receive_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.A) {
                textBox_Receive.SelectAll();
            }
        }
    }
}

