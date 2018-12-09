using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace binEditor {
    public partial class MainWindow : Form {

        private bool edited {
            get {
                if (state == 0 || state == 1)
                    return false;
                else
                    return true;
            }
            set {
                if (!value)
                    state = 0;
                else {
                    if (state == 0)
                        state = 1;
                    else if (state == 1)
                        state = 2;
                }
            }
        }

        private int state;
        private bool IsMouseDown;
        private int oldX, oldY;
        private bool programatically;
        private _item CurrentItem;
        private int CurrentItemIndex;
        private DrawBorders drawborders;
        private Pen WindowBorder;
        private Image iconImage;

        //private Pen NormalBorder;
        //private Rectangle[] BorderRects = new Rectangle[3];

        public MainWindow()
        {
            InitializeComponent();

        }

        private void init()
        {
            CurrentItem = null;
            edited = false;
            programatically = true;
            IsMouseDown = false;
            dataGridView1.Rows.Clear();
            label6.Text = label2.Text = textBox1.Text = textBox2.Text = "";
            dataGridView1.Columns[1].Width = dataGridView1.Width - dataGridView1.Columns[0].Width;
            foreach (var item in Program.items) {
                int i = dataGridView1.Rows.Add();
                dataGridView1.Rows[i].Cells[0].Value = item.enabled;
                dataGridView1.Rows[i].Cells[1].Value = item.name;
            }
            programatically = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label7.Text = Text = Program.OriFileName + " - binEditor";
            //NormalBorder = new Pen(BorderBrush);
            //SetBorderRects();            //blue: 51,153,255     bright green: 116,231,1   
            Pen[] Pens = new Pen[3] { new Pen(Color.FromArgb(80, 80, 80)),new Pen(Color.FromArgb(140, 140, 140)),new Pen(Color.FromArgb(72,213,90)) };
            WindowBorder = new Pen(Color.FromArgb(72, 213, 90));
            iconImage = Resource1.图标2;
            drawborders = new DrawBorders(Pens,CreateGraphics());
            drawborders.AddControl(dataGridView1);
            drawborders.AddControl(textBox1);
            drawborders.AddControl(textBox2);
            drawborders.UpdateBorderPositions();

            //textBox1.MouseWheel += new System.Windows.Forms.MouseEventHandler(textBox1_MouseWheel);
            //textBox2.MouseWheel += new System.Windows.Forms.MouseEventHandler(textBox2_MouseWheel);
            dataGridView1.MouseWheel += new System.Windows.Forms.MouseEventHandler(dataGridView1_MouseWheel);
            init();
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            edited = true;
            int index = dataGridView1.Rows.Add();
            var c1 = dataGridView1.Rows[index].Cells[0];
            var c2 = dataGridView1.Rows[index].Cells[1];
            Program.items.Add(new _item());
            c1.Value = true;
            c2.Value = "<new>";
            dataGridView1.CurrentCell = c2;
            dataGridView1.Focus();
            dataGridView1.BeginEdit(true);
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DelSelectedRows();
        }

        private void DelSelectedRows()
        {
            if (Program.ShowQuestionMessage("确定删除此条目？")) {
                edited = true;
                foreach (DataGridViewRow row in dataGridView1.SelectedRows) {
                    Program.items.RemoveAt(row.Index);
                    if (CurrentItemIndex == row.Index) {
                        CurrentItem = null;
                        label6.Text = label2.Text = textBox1.Text = textBox2.Text = "";
                        Program.tmppos = 0;
                    }
                    dataGridView1.Rows.Remove(row);
                }
            }
        }

        private void dataGridView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
                DelSelectedRows();
            else if (e.KeyCode == Keys.F2) {
                dataGridView1.CurrentCell = dataGridView1[1, dataGridView1.SelectedCells[0].RowIndex];
                dataGridView1.BeginEdit(true);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            GetPosWindow gpw = new GetPosWindow();
            if (gpw.ShowDialog() == DialogResult.OK) {
                edited = true;
                Showtmppos();
            }
        }
        
        private void Showtmppos()
        {
            if (Program.tmppos != -1) {
                label2.Text = string.Format("0x{0:X16}", Program.tmppos);
                button6.Visible = false;
            }
            else {
                label2.Text = "未指定";
                button6.Visible = true;
            }
        }

        private void ShowCurrentItem()
        {
            label6.Text = CurrentItem.name;
            Program.tmppos = CurrentItem.newpos;
            Showtmppos();
            programatically = true;
            textBox1.Text = CurrentItem.newdescription;
            textBox2.Text = Program.BytesToString(CurrentItem.newpatchdata);
            programatically = false;
        }

        private void SetCurrentItem(int index)
        {
            try {
                SaveCurrentItem();
            }
            catch(Exception ex) {
                Program.ShowErrorMessage(ex.Message);
                return;
            }

            if (index < Program.items.Count) {
                CurrentItem = Program.items[index];
                CurrentItemIndex = index;
                ShowCurrentItem();

            }
        }

        private void SaveCurrentItem()
        {
            if (CurrentItem == null) return;
            
            byte[] tmp = Program.StringToBytes(textBox2.Text);
            CurrentItem.newpatchdata = tmp;
            CurrentItem.newdescription = textBox1.Text;
            CurrentItem.newpos = Program.tmppos;

        }

        private void SaveAll()
        {

            SaveCurrentItem();
            ShowCurrentItem();

            foreach (_item item in Program.items)
                item.AcceptChange();
            Program.SaveDatFile();
            edited = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try {
                SaveAll();
            }
            catch(Exception ex) {
                Program.ShowErrorMessage("将数据保存至文件(" + Program.DatFileName + ")中时失败。\n  -" + ex.Message);
                return;
            }

            Program.ShowInfoMessage("成功将数据保存至文件(" + Program.DatFileName + ")中。");

        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (Program.ShowQuestionMessage("将从(" + Program.DatFileName + ")中恢复上一次保存的数据，目前的所有更改将丢失。\n是否确定？")) {
                Program.ReadDatFile();
                init();
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (CurrentItem == null) return;

            CurrentItem.RejectChange();
            ShowCurrentItem();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            try {
                SaveAll();
            }
            catch (Exception ex) {
                Program.ShowErrorMessage("将数据保存至文件(" + Program.DatFileName + ")中时失败。\n  -" + ex.Message);
                return;
            }
            try {
                Program.Execute();
            }
            catch(Exception ex) {
                Program.ShowErrorMessage(ex.Message);
                return;
            }
            Program.ShowInfoMessage("成功写入文件(" + Program.OriFileName + ")。");
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (!programatically) edited = true;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (!programatically) edited = true;
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (edited) {
                OnExit window = new OnExit();
                switch (window.ShowDialog()) {
                    case DialogResult.Yes:
                        try {
                            SaveAll();
                        }
                        catch(Exception ex) {
                            Program.ShowErrorMessage("将数据保存至文件(" + Program.DatFileName + ")中时失败。\n  -" + ex.Message);
                            e.Cancel = true;
                        }
                        break;
                    case DialogResult.No:

                        break;
                    case DialogResult.Cancel:
                        e.Cancel = true;
                        break;
                }

            }
        }

        private void dataGridView1_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            edited = true;
            string str= (string)dataGridView1[1, e.RowIndex].Value;
            if (e.ColumnIndex == 1) {
                Program.items[e.RowIndex].name = str;
                if (e.RowIndex == CurrentItemIndex && CurrentItem != null)
                    label6.Text = str;
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            bool b;
            if (e.ColumnIndex == 0) {
                b = Program.items[e.RowIndex].enabled;
                Program.items[e.RowIndex].enabled = !b;
                //label7.Text = (!b).ToString();
                //MessageBox.Show(e.RowIndex.ToString() + Program.items[e.RowIndex].enabled.ToString());
                //dataGridView1[e.ColumnIndex, e.RowIndex].Value = b;
            }

        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 1)
                SetCurrentItem(e.RowIndex);
        }

        private void MainWindow_Resize(object sender, EventArgs e)
        {
            //if(drawborders!= null) drawborders.UpdateBorderPositions();
        }


        private void dataGridView1_Resize(object sender, EventArgs e)
        {
            //dataGridView1.Columns[1].Width = dataGridView1.Width - dataGridView1.Columns[0].Width;
        }

        private void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(WindowBorder, 0, 0, Width - 1, Height - 1);
            e.Graphics.DrawImage(iconImage, 10, 6, 31, 31);
            drawborders.Paint(e.Graphics);

        }

        private void dataGridView1_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(dataGridView1);
        }

        private void dataGridView1_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(dataGridView1);
        }

        private void dataGridView1_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(dataGridView1);
        }

        private void dataGridView1_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(dataGridView1);
        }

        private void textBox1_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox1);
        }

        private void textBox1_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox1);
        }

        private void textBox1_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox1);
        }

        private void textBox1_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox1);
        }

        private void textBox2_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox2);
        }

        private void textBox2_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox2);
        }

        private void textBox2_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox2);
        }

        private void textBox2_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox2);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            
        }


        private void button9_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button8_Click_1(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }

        private void MainWindow_MouseDown(object sender, MouseEventArgs e)
        {
            IsMouseDown = true;
            oldX = Cursor.Position.X;
            oldY = Cursor.Position.Y;
        }

        private void MainWindow_MouseUp(object sender, MouseEventArgs e)
        {
            IsMouseDown = false;
        }

        private void MainWindow_MouseMove(object sender, MouseEventArgs e)
        {
            if (IsMouseDown) {
                Left += Cursor.Position.X - oldX;
                Top += Cursor.Position.Y - oldY;
                oldX = Cursor.Position.X;
                oldY = Cursor.Position.Y;
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            textBox2.Text = "";
        }

        //private void textBox1_MouseWheel(object sender, MouseEventArgs e)
        //{
        //    textBox1.SelectionLength = 0;
        //    if (e.Delta > 0)
        //        textBox1.SelectionStart -= 2;
        //    else
        //        textBox1.SelectionStart += 2;
        //}

        //private void textBox2_MouseWheel(object sender, MouseEventArgs e)
        //{

        //}
        private void dataGridView1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0) {
                if (dataGridView1.FirstDisplayedScrollingRowIndex > 0)
                    dataGridView1.FirstDisplayedScrollingRowIndex--;

            }
            else {
                if (dataGridView1.FirstDisplayedScrollingRowIndex < dataGridView1.Rows.Count - 10)
                    dataGridView1.FirstDisplayedScrollingRowIndex++;
                
            }
        }
    }
}
