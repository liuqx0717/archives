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
    public partial class inputsbj : Form
    {
        public bool cancel;

        private Pen pen;
        private Rectangle rect;

        public inputsbj()
        {
            InitializeComponent();
        }

        private void clickOK()
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("名称不能为空。", "输入学科名", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                textBox1.Focus();
                cancel = true;
                return;
            }
            if (textBox1.Text.Length >= DataFile.MAX_SUBJECT_WIDTH)
            {
                MessageBox.Show("名称过长，请重新输入。", "输入学科名", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                textBox1.Focus();
                cancel = true;
                return;
            }
            Program.subjectname = textBox1.Text;
            cancel = false;
            this.DialogResult = DialogResult.OK;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            clickOK();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            cancel = false;
        }

        private void inputsbj_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (cancel) e.Cancel = true;
        }

        private void inputsbj_Load(object sender, EventArgs e)
        {
            CancelButton = button2;
            pen = new Pen(Color.DodgerBlue);
            rect = new Rectangle(0, 0, Width-1, Height-1);
        }


        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                clickOK();
        }

        private void inputsbj_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(pen, rect);
        }
    }
}
