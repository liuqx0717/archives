using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace binEditor {
    public partial class GetPosWindow : Form {

        private Pen NormalBorder;
        private Pen WindowBorder;
        private SolidBrush TabBackground;

        private DrawBorders drawborders;

        public GetPosWindow()
        {
            InitializeComponent();
        }

        private void GetPosWindow_Load(object sender, EventArgs e)
        {
            NormalBorder = new Pen(Color.FromArgb(100, 100, 100));
            WindowBorder = new Pen(Color.FromArgb(72, 213, 90));
            TabBackground = new SolidBrush(Color.FromArgb(0, 0, 0));

            Pen[] Pens = new Pen[3] { new Pen(Color.FromArgb(80, 80, 80)), new Pen(Color.FromArgb(140, 140, 140)), new Pen(Color.FromArgb(72, 213, 90)) };
            drawborders = new DrawBorders(Pens, CreateGraphics());
            drawborders.AddControl(textBox1);
            drawborders.AddControl(textBox2);
            drawborders.AddControl(textBox3);
            drawborders.AddControl(textBox4);
            drawborders.AddControl(textBox5);
            drawborders.UpdateBorderPositions();
            

        }

        private void CloseWindow()
        {
            if (
                Program.isEmpty(textBox1.Text) &&
                Program.isEmpty(textBox1.Text) &&
                Program.isEmpty(textBox1.Text) &&
                Program.isEmpty(textBox1.Text) &&
                Program.isEmpty(textBox1.Text)
            ) {
                DialogResult = DialogResult.Cancel;
                Close();
            }
            else {
                if (Program.ShowQuestionMessage("当前已有内容输入。确定取消？")) {
                    DialogResult = DialogResult.Cancel;
                    Close();
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            long IDAPos = -1, IDAPos1 = -1, IDAPos2 = -1;
            List<long> tmppos1, tmppos2;
            try {
                if (Program.isEmpty(textBox5.Text) || Program.isEmpty(textBox1.Text) || Program.isEmpty(textBox2.Text))
                    throw (new Exception("参数数量不足。"));
                IDAPos = Convert.ToInt64(textBox5.Text, 16);
                IDAPos1 = Convert.ToInt64(textBox1.Text, 16);
                tmppos1 = Program.FindPos(Program.StringToBytes(textBox2.Text));

                if (tmppos1.Count == 0)
                    throw (new Exception("附近位置1未找到。"));
                else if (tmppos1.Count == 1) {
                    Program.tmppos = tmppos1[0] + IDAPos - IDAPos1;
                    DialogResult = DialogResult.OK;
                    Close();
                }
                else {
                    if (Program.isEmpty(textBox4.Text) || Program.isEmpty(textBox3.Text))
                        throw (new Exception("附近位置1有多处匹配。需要附近位置2。"));
                    IDAPos2 = Convert.ToInt64(textBox4.Text, 16);
                    tmppos2 = Program.FindPos(Program.StringToBytes(textBox3.Text));
                    var result = from p1 in tmppos1
                                 from p2 in tmppos2
                                 where p2 - p1 == IDAPos2 - IDAPos1
                                 select p1 + IDAPos - IDAPos1;
                    if (result.Count() == 0)
                        throw (new Exception("附近位置2未找到。"));
                    if (result.Count() == 1) {
                        Program.tmppos = result.First();
                        DialogResult = DialogResult.OK;
                        Close();
                    }
                    else {
                        throw (new Exception("仍然找到多处匹配。"));
                    }
                }
            }
            catch (Exception ex) {
                Program.ShowErrorMessage(ex.Message);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            CloseWindow();

        }

        private void GetPosWindow_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillRectangle(TabBackground, 17, 83, 260, 140);
            e.Graphics.DrawRectangle(NormalBorder, 17, 83, 260, 140);

            e.Graphics.DrawRectangle(WindowBorder, 0, 0, Width - 1, Height - 1);

            drawborders.Paint(e.Graphics);
        }

        private void label6_Click(object sender, EventArgs e)
        {
            label6.BackColor = Color.FromArgb(0, 0, 0);

            label7.BackColor = Color.FromArgb(0,40, 40, 40);
            textBox1.Visible = textBox2.Visible = true;
            textBox3.Visible = textBox4.Visible = false;
        }

        private void label7_Click(object sender, EventArgs e)
        {
            label7.BackColor = Color.FromArgb(0, 0, 0);
            label6.BackColor = Color.FromArgb(0,40, 40, 40);
            textBox1.Visible = textBox2.Visible = false;
            textBox3.Visible = textBox4.Visible = true;
        }

        private void textBox5_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox5);
        }

        private void textBox5_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox5);
        }

        private void textBox5_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox5);
        }

        private void textBox5_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox5);
        }

        private void textBox4_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox4);
        }

        private void textBox4_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox4);
        }

        private void textBox4_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox4);
        }

        private void textBox4_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox4);
        }

        private void textBox3_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox3);
        }

        private void textBox3_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox3);
        }

        private void textBox3_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox3);
        }

        private void textBox3_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox3);
        }

        private void textBox2_MouseEnter(object sender, EventArgs e)
        {
            drawborders.MouseEnter(textBox2);
        }

        private void textBox2_MouseLeave(object sender, EventArgs e)
        {
            drawborders.MouseLeave(textBox2);
        }

        private void textBox2_Enter(object sender, EventArgs e)
        {
            drawborders.GetFocus(textBox2);
        }

        private void textBox2_Leave(object sender, EventArgs e)
        {
            drawborders.LoseFocus(textBox2);
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

        private void button9_Click(object sender, EventArgs e)
        {
            CloseWindow();
        }
    }
}
