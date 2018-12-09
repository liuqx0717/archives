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
    public partial class statistics : Form
    {
        public statistics()
        {
            InitializeComponent();
        }

        private void statistics_Load(object sender, EventArgs e)
        {
            dataGridView1.BackgroundColor = Color.FromArgb(45, 45, 48);
            DataGridViewRow newrow;
            DataGridViewColumn newcolumn;
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = MainWindow.PREFERED_SCORE_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "学科";
            dataGridView1.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = MainWindow.PREFERED_SCORE_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "平均值";
            dataGridView1.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = MainWindow.PREFERED_SCORE_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "方差";
            dataGridView1.Columns.Add(newcolumn);
            for (int i=0;i<Program.nSubject;++i)
            {
                newrow = new DataGridViewRow();
                dataGridView1.Rows.Add(newrow);
                dataGridView1[0, i].Value = Program.subjects[i];
                dataGridView1[1, i].Value = Program.averages[i];
                dataGridView1[2, i].Value = Program.variances[i];
            }

        }
    }
}
