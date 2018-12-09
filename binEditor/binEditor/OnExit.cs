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
    public partial class OnExit : Form {

        private Pen WindowBorder;

        public OnExit()
        {
            InitializeComponent();
        }

        private void OnExit_Load(object sender, EventArgs e)
        {
            label1.Text = "是否保存更改至文件\n(" + Program.DatFileName + ")？";
            WindowBorder = new Pen(Color.FromArgb(72, 213, 90));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Yes;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.No;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button3_Enter(object sender, EventArgs e)
        {
            //button1.Focus();
        }

        private void OnExit_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(WindowBorder, 0, 0, Width - 1, Height - 1);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }
    }
}
