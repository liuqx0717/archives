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
    public partial class inputpsw : Form
    {

        private Pen pen;
        private Rectangle rect;

        public inputpsw()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Program.password = textBox1.Text;
        }

        private void inputpsw_Load(object sender, EventArgs e)
        {
            CancelButton = button2;
            pen = new Pen(Color.DodgerBlue);
            rect = new Rectangle(0, 0, Width - 1, Height - 1);
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                Program.password = textBox1.Text;
                this.DialogResult = DialogResult.OK;

            }
        }

        private void inputpsw_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(pen, rect);

        }
    }
}
