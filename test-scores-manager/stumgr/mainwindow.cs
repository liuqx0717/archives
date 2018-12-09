using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

//C:\刘权兴\代码\stumgr_krnl\Debug\stumgr_krnl.dll

namespace stumgr
{
    public partial class MainWindow : Form
    {

        //[DllImport(@"C:\刘权兴\代码\stumgr_krnl\Debug\stumgr_krnl.dll", EntryPoint = "_f@4")]
        //static extern void f(float[] array);
        public const int PREFERED_ID_WIDTH = 120;
        public const int PREFERED_NAME_WIDTH = 80;
        public const int PREFERED_GENDER_WIDTH = 80;
        public const int PREFERED_SCORE_WIDTH = 80;

        private int nStudent = 0;
        private int nSubject = 0;
        private bool edit = false;
        private object oldvalue;
        private bool saved = false;
        private static string currentfile;

        private void datasheetinit()
        {
            DataSheet.Columns.Clear();
            nStudent = 0;
            nSubject = 0;
            var newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = 50;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            //newcolumn.HeaderCell.Style.Alignment = DataGridViewContentAlignment.MiddleCenter;
            newcolumn.ReadOnly = true;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "序号";
            DataSheet.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = PREFERED_ID_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "学号";
            DataSheet.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = PREFERED_NAME_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "姓名";
            DataSheet.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = PREFERED_GENDER_WIDTH;
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.Name = newcolumn.HeaderText = "性别";
            DataSheet.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = PREFERED_SCORE_WIDTH;
            newcolumn.DefaultCellStyle.Format = "#.00";
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.ReadOnly = true;
            newcolumn.ValueType = typeof(float);
            newcolumn.Name = newcolumn.HeaderText = "总分";
            DataSheet.Columns.Add(newcolumn);
            newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newcolumn.Width = PREFERED_SCORE_WIDTH;
            newcolumn.DefaultCellStyle.Format = "#.00";
            newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
            newcolumn.ReadOnly = true;
            newcolumn.ValueType = typeof(float);
            newcolumn.Name = newcolumn.HeaderText = "均分";
            DataSheet.Columns.Add(newcolumn);


        }

        private bool ask(string question,string title)
        {
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = MessageBox.Show(question, title, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
            if (result == DialogResult.Yes)
                return true;
            else
                return false;
        }

        private DataFile.ErrorType LoadData()
        {
            DataFile.ErrorType result;
            byte[] SubjectNames = new byte[nSubject * DataFile.MAX_SUBJECT_WIDTH];
            byte[] StudentInfos = new byte[nStudent * DataFile.MAX_STUDENTINFO_WIDTH];

            float[] scores = new float[nStudent * nSubject];
            result = DataFile.LoadDataFile(SubjectNames, StudentInfos, scores);
            if (result == DataFile.ErrorType.FILE_ERROR)
                return DataFile.ErrorType.FILE_ERROR;
            DataGridViewRow newrow;
            for (int i = 0; i < nSubject; ++i)
            {
                var newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
                newcolumn.Width = PREFERED_SCORE_WIDTH;
                newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
                newcolumn.DefaultCellStyle.Format = "#.00";
                newcolumn.ValueType = typeof(float);
                newcolumn.Name = newcolumn.HeaderText = Encoding.Unicode.GetString(
                    SubjectNames,
                    i * DataFile.MAX_SUBJECT_WIDTH,
                    DataFile.MAX_SUBJECT_WIDTH
                ).TrimEnd('\0');
                DataSheet.Columns.Add(newcolumn);
                newcolumn.DisplayIndex = 4 + i;
            }

            for (int i = 0; i < nStudent; ++i)
            {
                newrow = new DataGridViewRow();
                DataSheet.Rows.Add(newrow);
                DataSheet[0, i].Value = i + 1;
                DataSheet[1, i].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH,
                    DataFile.MAX_ID_WIDTH
                ).TrimEnd('\0'); 
                DataSheet[2, i].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH,
                    DataFile.MAX_NAME_WIDTH
                ).TrimEnd('\0'); 
                DataSheet[3, i].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH + DataFile.MAX_NAME_WIDTH,
                    DataFile.MAX_GENDER_WIDTH
                ).TrimEnd('\0'); 
                for (int j = 0; j < nSubject; ++j) 
                {
                    float s = scores[i * nSubject + j];
                    if (s >= 0)
                        DataSheet[6 + j, i].Value = s;
                    else
                        DataSheet[6 + j, i].Value = null;
                }
                calc(i);
            }
            return DataFile.ErrorType.SUCCEEDED;
        }

        private DataFile.ErrorType AddFile(string filename)
        {
            int nsub = 0, nstu = 0;
            DataFile.ErrorType result = DataFile.OpenDataFile(
                filename,
                "123456",
                ref nsub,
                ref nstu
            );
            if (result == DataFile.ErrorType.FILE_ERROR)
                return DataFile.ErrorType.FILE_ERROR;
            byte[] SubjectNames = new byte[nsub * DataFile.MAX_SUBJECT_WIDTH];
            byte[] StudentInfos = new byte[nstu * DataFile.MAX_STUDENTINFO_WIDTH];
            float[] scores = new float[nstu * nsub];
            result = DataFile.LoadDataFile(SubjectNames, StudentInfos, scores);
            if (result == DataFile.ErrorType.FILE_ERROR)
                return DataFile.ErrorType.FILE_ERROR;
            DataGridViewRow newrow;
            for (int i = 0; i < nsub; ++i)
            {
                string subjectname = Encoding.Unicode.GetString(
                    SubjectNames,
                    i * DataFile.MAX_SUBJECT_WIDTH,
                    DataFile.MAX_SUBJECT_WIDTH
                ).TrimEnd('\0');
                if (nsub != nSubject || subjectname != DataSheet.Columns[6 + i].HeaderText) 
                {
                    MessageBox.Show("此文件学科的种类、顺序与当前不符。选择的数据文件中学科的种类、顺序必须与当前相同。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return DataFile.ErrorType.SUCCEEDED;
                }
            }

            for (int i = 0; i < nstu; ++i)
            {
                newrow = new DataGridViewRow();
                DataSheet.Rows.Add(newrow);
                DataSheet[0, nStudent].Value = nStudent + 1;
                DataSheet[1, nStudent].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH,
                    DataFile.MAX_ID_WIDTH
                ).TrimEnd('\0');
                DataSheet[2, nStudent].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH,
                    DataFile.MAX_NAME_WIDTH
                ).TrimEnd('\0');
                DataSheet[3, nStudent].Value = Encoding.Unicode.GetString(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH + DataFile.MAX_NAME_WIDTH,
                    DataFile.MAX_GENDER_WIDTH
                ).TrimEnd('\0');
                for (int j = 0; j < nSubject; ++j)
                {
                    float s = scores[i * nSubject + j];
                    if (s >= 0)
                        DataSheet[6 + j, nStudent].Value = s;
                    else
                        DataSheet[6 + j, nStudent].Value = null;
                }
                calc(nStudent);
                ++nStudent;
            }
            return DataFile.ErrorType.SUCCEEDED;
        }

        private DataFile.ErrorType SaveData(string filename)
        {
            byte[] SubjectNames = new byte[nSubject * DataFile.MAX_SUBJECT_WIDTH];
            byte[] StudentInfos = new byte[nStudent * DataFile.MAX_STUDENTINFO_WIDTH];
            
            float[] scores = new float[nStudent * nSubject];
            for (int j = 6; j < nSubject+6; ++j)
            {
                Encoding.Unicode.GetBytes(DataSheet.Columns[j].HeaderText).CopyTo(
                    SubjectNames,
                    DataFile.MAX_SUBJECT_WIDTH * (j - 6)
                );
            }
            for (int i = 0; i < nStudent; ++i)
            {
                if (DataSheet[1, i].Value != null)
                {
                    Encoding.Unicode.GetBytes(DataSheet[1, i].Value.ToString()).CopyTo(
                        StudentInfos,
                        i * DataFile.MAX_STUDENTINFO_WIDTH
                    );
                }
                else
                    StudentInfos[i * DataFile.MAX_STUDENTINFO_WIDTH] = 0;

                if (DataSheet[2, i].Value != null)
                {
                    Encoding.Unicode.GetBytes(DataSheet[2, i].Value.ToString()).CopyTo(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH
                    );
                }
                else
                    StudentInfos[i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH] = 0;

                if (DataSheet[3, i].Value != null)
                {
                    Encoding.Unicode.GetBytes(DataSheet[3, i].Value.ToString()).CopyTo(
                    StudentInfos,
                    i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH + DataFile.MAX_NAME_WIDTH
                    );
                }
                else
                    StudentInfos[i * DataFile.MAX_STUDENTINFO_WIDTH + DataFile.MAX_ID_WIDTH + DataFile.MAX_NAME_WIDTH] = 0;

                for (int j = 6; j < nSubject+6; ++j)
                {
                    if (DataSheet[j, i].Value == null)
                    {
                        scores[i * nSubject + j - 6] = -1F;
                        continue;
                    }
                    scores[i * nSubject + j - 6] = Convert.ToSingle(DataSheet[j, i].Value);
                }

            }
            return DataFile.SaveDataFile(
                filename,
                nSubject,
                nStudent,
                Program.newpassword,
                SubjectNames,
                StudentInfos,
                scores
            );

        }

        private void calc(int RowNumber)
        {
            int div = nSubject;
            object score;
            float gross = 0;
            for (int i = 6; i < nSubject + 6; ++i) 
            {
                score = DataSheet[i,RowNumber].Value;
                if (score == null)
                {
                    --div;
                    continue;
                }
                gross += Convert.ToSingle(score);
            }
            DataSheet[4, RowNumber].Value = gross;
            DataSheet[5, RowNumber].Value = div == 0 ? 0 : gross / div;
        }

        private void stat()
        {
            float gross, gross2;
            float average;
            object score;
            int div = nStudent;

            Program.subjects = new string[nSubject];
            Program.averages = new float[nSubject];
            Program.variances = new float[nSubject];
            for (int i = 6; i < 6 + nSubject; ++i)
            {
                gross = gross2 = 0;
                Program.subjects[i - 6] = DataSheet.Columns[i].HeaderText;
                for (int j = 0; j < nStudent; ++j)
                {
                    score = DataSheet[i, j].Value;
                    if (score == null)
                    {
                        --div;
                        continue;
                    }
                    gross += Convert.ToSingle(score);
                }
                average = div == 0 ? 0 : gross / div;
                Program.averages[i - 6] = average;
                for (int j = 0; j < nStudent; ++j)
                {
                    score = DataSheet[i, j].Value;
                    if (score == null)
                        continue;
                    gross2 += (Convert.ToSingle(score) - average) * (Convert.ToSingle(score) - average);
                }
                Program.variances[i - 6] = div == 0 ? 0 : gross2 / div;
            }
            Program.nSubject = nSubject;
            var objstat = new statistics();
            objstat.Show();
        }

        private void newsheet()
        {
            var objinputpsw = new inputnewpsw();

            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = objinputpsw.ShowDialog();
            if (result == DialogResult.OK)
            {
                datasheetinit();
                beginedit();
                button_new.Visible = false;
                currentfile = "";
            }
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
        }

        public static bool ExportExcel(string fileName, DataGridView myDGV)
        {  
           if (myDGV.Rows.Count > 0)  
           {
                
                 Microsoft.Office.Interop.Excel.Application xlApp = new Microsoft.Office.Interop.Excel.Application();
                if (xlApp == null)
                {
                    return false;
                }

                Microsoft.Office.Interop.Excel.Workbooks workbooks = xlApp.Workbooks;
                Microsoft.Office.Interop.Excel.Workbook workbook = workbooks.Add(Microsoft.Office.Interop.Excel.XlWBATemplate.xlWBATWorksheet);
                Microsoft.Office.Interop.Excel.Worksheet worksheet = (Microsoft.Office.Interop.Excel.Worksheet)workbook.Worksheets[1];//取得sheet1  

                //写入标题  
                int j2 = 0;
                for (int i = 0; i < 4; i++, j2++)
                    worksheet.Cells[1, j2 + 1] = myDGV.Columns[i].HeaderText;
                for (int i = 6; i < myDGV.ColumnCount; i++, j2++)
                    worksheet.Cells[1, j2 + 1] = myDGV.Columns[i].HeaderText;
                for (int i = 4; i <=5; i++, j2++)
                    worksheet.Cells[1, j2 + 1] = myDGV.Columns[i].HeaderText;
                //写入数值  
                for (int r = 0; r < myDGV.Rows.Count; r++)
                {
                    int j = 0;
                    for (int i = 0; i < 4; i++, j++) 
                        worksheet.Cells[r + 2, j + 1] = myDGV.Rows[r].Cells[i].Value;
                    for (int i = 6; i < myDGV.ColumnCount; i++, j++)
                        worksheet.Cells[r + 2, j + 1] = myDGV.Rows[r].Cells[i].Value;
                    for (int i = 4; i <= 5; i++, j++)
                        worksheet.Cells[r + 2, j + 1] = myDGV.Rows[r].Cells[i].Value;
                    System.Windows.Forms.Application.DoEvents();
                }
                worksheet.Columns.EntireColumn.AutoFit();//列宽自适应  

                try
                {
                    workbook.Saved = true;
                    workbook.SaveCopyAs(fileName);
                }
                catch (Exception ex)
                {
                    return false;
                }


                xlApp.Quit();
                GC.Collect();//强行销毁   
                return true;
            }
            else
            {
                MessageBox.Show("报表为空,无表格需要导出", "提示",MessageBoxButtons.OK,MessageBoxIcon.Information);
                return true;
            }

        }


        private void save()
        {
            if (currentfile == "")
            {
                saveFileDialog1.Title = "另存为...";
                saveFileDialog1.Filter = "数据文件|*.dat";
                saveFileDialog1.FileName = "";
                for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
                var result = saveFileDialog1.ShowDialog();
                for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
                if (result != DialogResult.OK)
                {
                    return;
                }
                currentfile = saveFileDialog1.FileName;
            }
            if (SaveData(currentfile) != DataFile.ErrorType.SUCCEEDED)
            {
                MessageBox.Show("保存文件失败。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                saved = false;
                return;
            }
            saved = true;
        }

        private void addsubject()
        {
            var objinputsbj = new inputsbj();
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = objinputsbj.ShowDialog();
            if (result == DialogResult.OK)
            {
                ++nSubject;
                var newcolumn = new DataGridViewColumn(new DataGridViewTextBoxCell());
                newcolumn.Width = PREFERED_SCORE_WIDTH;
                newcolumn.SortMode = DataGridViewColumnSortMode.Automatic;
                newcolumn.DefaultCellStyle.Format = "#.00";
                newcolumn.ValueType = typeof(float);
                newcolumn.Name = newcolumn.HeaderText = Program.subjectname;
                DataSheet.Columns.Add(newcolumn);
                newcolumn.DisplayIndex = 3 + nSubject;

            }
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
        }

        private void beginedit()
        {
            MenuItem_save.Enabled = true;
            MenuItem_edit.Enabled = true;
            MenuItem_add.Enabled = true;
            MenuItem_saveas.Enabled = true;
            button_beginedit.Visible = false;
            button_addcolumn.Visible = true;
            MenuItem_add.Enabled = true;
            DataSheet.AllowUserToAddRows = true;
            DataSheet.AllowUserToDeleteRows = true;
            DataSheet.EditMode = DataGridViewEditMode.EditOnKeystrokeOrF2;
            edit = true;
        }
        
        private void endedit()
        {
            MenuItem_save.Enabled = false;
            MenuItem_edit.Enabled = false;
            MenuItem_add.Enabled = false;
            MenuItem_saveas.Enabled = false;
            button_beginedit.Visible = true;
            button_addcolumn.Visible = false;
            MenuItem_add.Enabled = false;
            DataSheet.AllowUserToAddRows = false;
            DataSheet.AllowUserToDeleteRows = false;
            DataSheet.EditMode = DataGridViewEditMode.EditProgrammatically;
            edit = false; 
        }


        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            //DataSheet.BackgroundColor = Color.FromArgb(48, 48, 51);
            DataSheet.DefaultCellStyle.ForeColor = Color.Black;
            CancelButton = button_exit;

        }

        private void button_beginedit_Click(object sender, EventArgs e)
        {
            var objinputpsw = new inputpsw();
            int nsub = 0, nstu = 0;
            DataFile.ErrorType result;
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var diaresult = objinputpsw.ShowDialog();
            if (diaresult == DialogResult.OK)
            {
                result = DataFile.OpenDataFile(
                    currentfile,
                    Program.password,
                    ref nsub,
                    ref nstu
                );
                if (result == DataFile.ErrorType.SUCCEEDED)
                    beginedit();
                else
                    MessageBox.Show("密码错误", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
        }

        private void MenuItem_new_Click(object sender, EventArgs e)
        {
            newsheet();
        }

        private void MenuItem_open_Click(object sender, EventArgs e)
        {
            DataFile.ErrorType retval;
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            openFileDialog1.Title = "打开文件";
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = "数据文件|*.dat";
            var result = openFileDialog1.ShowDialog();
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
            if (result == DialogResult.OK)
            {
                button_new.Visible = false;
                currentfile = openFileDialog1.FileName;
                datasheetinit();
                retval = DataFile.OpenDataFile(
                    currentfile,
                    Program.newpassword,
                    ref nSubject,
                    ref nStudent
                );
                switch (retval)
                {
                    case DataFile.ErrorType.SUCCEEDED:
                        if (LoadData() == DataFile.ErrorType.FILE_ERROR)
                        {
                            MessageBox.Show("打开文件时遇到错误。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            DataSheet.Columns.Clear();
                        }
                        else
                        {
                            beginedit();
                        }
                        break;
                    case DataFile.ErrorType.FILE_ERROR:
                        MessageBox.Show("打开文件时遇到错误。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        DataSheet.Columns.Clear();
                        break;
                    case DataFile.ErrorType.INCORRECT_PASSWORD:
                        if (LoadData() == DataFile.ErrorType.FILE_ERROR)
                        {
                            MessageBox.Show("打开文件时遇到错误。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            DataSheet.Columns.Clear();
                        }
                        else
                        {
                            endedit();
                            button_beginedit.Visible = true;
                        }
                        break;
                    default:
                        break;
                }
            }


        }

        private void button_exit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void MenuItem_save_Click(object sender, EventArgs e)
        {
            save();
        }

        private void MenuItem_saveas_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Title = "另存为...";
            saveFileDialog1.Filter = "数据文件|*.dat";
            saveFileDialog1.FileName = "";
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = saveFileDialog1.ShowDialog();
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
            if (result == DialogResult.OK)
            {
                if (SaveData(saveFileDialog1.FileName) != DataFile.ErrorType.SUCCEEDED)
                    MessageBox.Show("保存文件失败。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                else
                    saved = true;
            }
        }

        private void MenuItem_changepsw_Click(object sender, EventArgs e)
        {
            var objinputpsw = new inputnewpsw();
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            objinputpsw.ShowDialog();
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;

        }

        private void MenuItem_addsubject_Click(object sender, EventArgs e)
        {
            addsubject();
        }

        private void MenuItem_deletesubject_Click(object sender, EventArgs e)
        {
            bool delete;
            if (!ask("确定删除所选的学科？", "确认")) return;
            for (int i = 6; i < nSubject + 6;) 
            {
                delete = false;
                foreach (DataGridViewCell cell in DataSheet.SelectedCells)
                {
                    if (cell.ColumnIndex == i) 
                    {
                        delete = true;
                        break;
                    }
                }
                if(delete)
                {
                    DataSheet.Columns.RemoveAt(i);
                    --nSubject;
                    i = 6;
                    continue;
                }
                ++i;
            }
        }

        private void DataSheet_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete && DataSheet.EditMode != DataGridViewEditMode.EditProgrammatically) 
            {

                foreach (DataGridViewCell cell in DataSheet.SelectedCells)
                {
                    if (cell.ColumnIndex == 0 || cell.ColumnIndex == 4 || cell.ColumnIndex == 5)
                        continue;
                    cell.Value = null;
                    calc(cell.RowIndex);
                }
            }
        }

        private void DataSheet_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            MessageBox.Show("输入的值无效，请重新输入。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            DataSheet.RefreshEdit();
        }
        private void DataSheet_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            for (int i = 0; i < DataSheet.RowCount; ++i)
                DataSheet[0, i].Value = i + 1;
        }

        private void button_addcolumn_Click(object sender, EventArgs e)
        {
            addsubject();
        }

        private void DataSheet_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            if (e.RowIndex == nStudent) return;
            oldvalue = DataSheet[e.ColumnIndex, e.RowIndex].Value;
        }

        private void DataSheet_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            if (DataSheet[e.ColumnIndex, e.RowIndex].Value == null) return;
            if (e.RowIndex == nStudent) return;
            if (e.ColumnIndex == 1 &&
                DataSheet[e.ColumnIndex, e.RowIndex].Value.ToString().Length >= DataFile.MAX_ID_WIDTH) 
            {
                MessageBox.Show("学号过长，请重新输入。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DataSheet[e.ColumnIndex, e.RowIndex].Value = oldvalue;
                return;
            }
            if (e.ColumnIndex == 2 &&
                DataSheet[e.ColumnIndex, e.RowIndex].Value.ToString().Length >= DataFile.MAX_NAME_WIDTH)
            {
                MessageBox.Show("姓名过长，请重新输入。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DataSheet[e.ColumnIndex, e.RowIndex].Value = oldvalue;
                return;
            }
            if (e.ColumnIndex == 3 &&
                DataSheet[e.ColumnIndex, e.RowIndex].Value.ToString().Length >= DataFile.MAX_GENDER_WIDTH)
            {
                MessageBox.Show("性别过长，请重新输入。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DataSheet[e.ColumnIndex, e.RowIndex].Value = oldvalue;
                return;
            }
            if (e.ColumnIndex >= 6) 
            {
                if (Convert.ToSingle(DataSheet[e.ColumnIndex, e.RowIndex].Value) < 0) 
                {
                    MessageBox.Show("分数应为非负数，请重新输入。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    DataSheet[e.ColumnIndex, e.RowIndex].Value = oldvalue;
                }
            }
            calc(e.RowIndex);

        }

        private void DataSheet_UserAddedRow(object sender, DataGridViewRowEventArgs e)
        {
            ++nStudent;
            for (int i = 0; i < DataSheet.RowCount-1; ++i)
                DataSheet[0, i].Value = i + 1;
        }

        private void DataSheet_UserDeletedRow(object sender, DataGridViewRowEventArgs e)
        {
            --nStudent;
            for (int i = 0; i < DataSheet.RowCount-1; ++i)
                DataSheet[0, i].Value = i + 1;
        }

        private void MenuItem_add_Click(object sender, EventArgs e)
        {
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            openFileDialog1.Title = "打开文件";
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = "数据文件|*.dat";
            var result = openFileDialog1.ShowDialog();
            if(result==DialogResult.OK)
            {
                if(AddFile(openFileDialog1.FileName)==DataFile.ErrorType.FILE_ERROR)
                    MessageBox.Show("打开文件失败。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
        }

        private void MenuItem_exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button_stat_Click(object sender, EventArgs e)
        {
            stat();

        }

        private void 学科统计ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            stat();
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(edit)
            {
                if (saved) return;
                if (ask("是否保存当前数据？", "提示"))
                    save();
            }
        }

        private void button_export_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Title = "另存为...";
            saveFileDialog1.Filter = "电子表格|*.xlsx";
            saveFileDialog1.FileName = "";
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = saveFileDialog1.ShowDialog();
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
            if (result == DialogResult.OK)
            {
                ExportExcel(saveFileDialog1.FileName, DataSheet);
            }
        }

        private void button_new_Click(object sender, EventArgs e)
        {
            newsheet();
        }

        private void MenuItem_export_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Title = "另存为...";
            saveFileDialog1.Filter = "电子表格|*.xlsx";
            saveFileDialog1.FileName = "";
            for (float f = 1F; f >= 0.5F; f -= 0.01F, Thread.Sleep(3)) this.Opacity = f;
            var result = saveFileDialog1.ShowDialog();
            for (float f = 0.5F; f <= 1F; f += 0.01F, Thread.Sleep(3)) this.Opacity = f;
            if (result == DialogResult.OK)
            {
                ExportExcel(saveFileDialog1.FileName, DataSheet);
            }
        }
    }
}
