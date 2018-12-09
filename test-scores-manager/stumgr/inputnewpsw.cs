using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace stumgr
{
    public partial class inputnewpsw : Form
    {
        public bool cancel;

        private Pen pen;
        private Rectangle rect;

        public inputnewpsw()
        {
            InitializeComponent();
        }

        void clickOK()
        {
            if (textBox1.Text == textBox2.Text)
            {
                if (textBox1.Text == "")
                {
                    MessageBox.Show("密码不能为空。", "密码输入", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    textBox2.Focus();
                    cancel = true;
                    return;
                }
                Program.newpassword = textBox1.Text;
                cancel = false;
            }
            else
            {
                MessageBox.Show("两次输入不一致！", "密码输入", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                textBox2.Focus();
                cancel = true;
            }
            this.DialogResult = DialogResult.OK;

        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            clickOK();

        }

        private void inputpsw_Load(object sender, EventArgs e)
        {
            CancelButton = button2;
            //AcceptButton = button1;
            cancel = false;
            pen = new Pen(Color.DodgerBlue);
            rect = new Rectangle(0, 0, Width - 1, Height - 1);
        }

        private void inputpsw_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (cancel) e.Cancel = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            cancel = false;
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                clickOK();
        }

        private void inputnewpsw_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(pen, rect);
            
        }

    }
}
