namespace stumgr
{
    partial class MainWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle9 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle10 = new System.Windows.Forms.DataGridViewCellStyle();
            this.DataSheet = new System.Windows.Forms.DataGridView();
            this.MainWindowMenuStrip = new System.Windows.Forms.MenuStrip();
            this.MenuItem_file = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_new = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_open = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_add = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_save = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_saveas = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.MenuItem_export = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.MenuItem_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_edit = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_changepsw = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.MenuItem_addsubject = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_deletesubject = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.学科统计ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.button_addcolumn = new System.Windows.Forms.Button();
            this.button_stat = new System.Windows.Forms.Button();
            this.button_exit = new System.Windows.Forms.Button();
            this.button_beginedit = new System.Windows.Forms.Button();
            this.button_export = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.button_new = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.DataSheet)).BeginInit();
            this.MainWindowMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // DataSheet
            // 
            this.DataSheet.AllowUserToAddRows = false;
            this.DataSheet.AllowUserToDeleteRows = false;
            resources.ApplyResources(this.DataSheet, "DataSheet");
            this.DataSheet.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(48)))), ((int)(((byte)(48)))), ((int)(((byte)(51)))));
            dataGridViewCellStyle9.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle9.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle9.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle9.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle9.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle9.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle9.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataSheet.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
            this.DataSheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            dataGridViewCellStyle10.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle10.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle10.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle10.ForeColor = System.Drawing.Color.Silver;
            dataGridViewCellStyle10.NullValue = "<无数据>";
            dataGridViewCellStyle10.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle10.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle10.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.DataSheet.DefaultCellStyle = dataGridViewCellStyle10;
            this.DataSheet.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.DataSheet.Name = "DataSheet";
            this.DataSheet.RowTemplate.Height = 23;
            this.DataSheet.CellBeginEdit += new System.Windows.Forms.DataGridViewCellCancelEventHandler(this.DataSheet_CellBeginEdit);
            this.DataSheet.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataSheet_CellEndEdit);
            this.DataSheet.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.DataSheet_ColumnHeaderMouseClick);
            this.DataSheet.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.DataSheet_DataError);
            this.DataSheet.UserAddedRow += new System.Windows.Forms.DataGridViewRowEventHandler(this.DataSheet_UserAddedRow);
            this.DataSheet.UserDeletedRow += new System.Windows.Forms.DataGridViewRowEventHandler(this.DataSheet_UserDeletedRow);
            this.DataSheet.KeyDown += new System.Windows.Forms.KeyEventHandler(this.DataSheet_KeyDown);
            // 
            // MainWindowMenuStrip
            // 
            this.MainWindowMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_file,
            this.MenuItem_edit});
            resources.ApplyResources(this.MainWindowMenuStrip, "MainWindowMenuStrip");
            this.MainWindowMenuStrip.Name = "MainWindowMenuStrip";
            // 
            // MenuItem_file
            // 
            this.MenuItem_file.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_new,
            this.MenuItem_open,
            this.MenuItem_add,
            this.MenuItem_save,
            this.MenuItem_saveas,
            this.toolStripSeparator1,
            this.MenuItem_export,
            this.toolStripSeparator2,
            this.MenuItem_exit});
            this.MenuItem_file.Name = "MenuItem_file";
            resources.ApplyResources(this.MenuItem_file, "MenuItem_file");
            // 
            // MenuItem_new
            // 
            this.MenuItem_new.Name = "MenuItem_new";
            resources.ApplyResources(this.MenuItem_new, "MenuItem_new");
            this.MenuItem_new.Click += new System.EventHandler(this.MenuItem_new_Click);
            // 
            // MenuItem_open
            // 
            this.MenuItem_open.Name = "MenuItem_open";
            resources.ApplyResources(this.MenuItem_open, "MenuItem_open");
            this.MenuItem_open.Click += new System.EventHandler(this.MenuItem_open_Click);
            // 
            // MenuItem_add
            // 
            resources.ApplyResources(this.MenuItem_add, "MenuItem_add");
            this.MenuItem_add.Name = "MenuItem_add";
            this.MenuItem_add.Click += new System.EventHandler(this.MenuItem_add_Click);
            // 
            // MenuItem_save
            // 
            resources.ApplyResources(this.MenuItem_save, "MenuItem_save");
            this.MenuItem_save.Name = "MenuItem_save";
            this.MenuItem_save.Click += new System.EventHandler(this.MenuItem_save_Click);
            // 
            // MenuItem_saveas
            // 
            resources.ApplyResources(this.MenuItem_saveas, "MenuItem_saveas");
            this.MenuItem_saveas.Name = "MenuItem_saveas";
            this.MenuItem_saveas.Click += new System.EventHandler(this.MenuItem_saveas_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            resources.ApplyResources(this.toolStripSeparator1, "toolStripSeparator1");
            // 
            // MenuItem_export
            // 
            this.MenuItem_export.Name = "MenuItem_export";
            resources.ApplyResources(this.MenuItem_export, "MenuItem_export");
            this.MenuItem_export.Click += new System.EventHandler(this.MenuItem_export_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            resources.ApplyResources(this.toolStripSeparator2, "toolStripSeparator2");
            // 
            // MenuItem_exit
            // 
            this.MenuItem_exit.Name = "MenuItem_exit";
            resources.ApplyResources(this.MenuItem_exit, "MenuItem_exit");
            this.MenuItem_exit.Click += new System.EventHandler(this.MenuItem_exit_Click);
            // 
            // MenuItem_edit
            // 
            this.MenuItem_edit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_changepsw,
            this.toolStripSeparator3,
            this.MenuItem_addsubject,
            this.MenuItem_deletesubject,
            this.toolStripSeparator4,
            this.学科统计ToolStripMenuItem});
            resources.ApplyResources(this.MenuItem_edit, "MenuItem_edit");
            this.MenuItem_edit.Name = "MenuItem_edit";
            // 
            // MenuItem_changepsw
            // 
            this.MenuItem_changepsw.Name = "MenuItem_changepsw";
            resources.ApplyResources(this.MenuItem_changepsw, "MenuItem_changepsw");
            this.MenuItem_changepsw.Click += new System.EventHandler(this.MenuItem_changepsw_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            resources.ApplyResources(this.toolStripSeparator3, "toolStripSeparator3");
            // 
            // MenuItem_addsubject
            // 
            this.MenuItem_addsubject.Name = "MenuItem_addsubject";
            resources.ApplyResources(this.MenuItem_addsubject, "MenuItem_addsubject");
            this.MenuItem_addsubject.Click += new System.EventHandler(this.MenuItem_addsubject_Click);
            // 
            // MenuItem_deletesubject
            // 
            this.MenuItem_deletesubject.Name = "MenuItem_deletesubject";
            resources.ApplyResources(this.MenuItem_deletesubject, "MenuItem_deletesubject");
            this.MenuItem_deletesubject.Click += new System.EventHandler(this.MenuItem_deletesubject_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            resources.ApplyResources(this.toolStripSeparator4, "toolStripSeparator4");
            // 
            // 学科统计ToolStripMenuItem
            // 
            this.学科统计ToolStripMenuItem.Name = "学科统计ToolStripMenuItem";
            resources.ApplyResources(this.学科统计ToolStripMenuItem, "学科统计ToolStripMenuItem");
            this.学科统计ToolStripMenuItem.Click += new System.EventHandler(this.学科统计ToolStripMenuItem_Click);
            // 
            // button_addcolumn
            // 
            resources.ApplyResources(this.button_addcolumn, "button_addcolumn");
            this.button_addcolumn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_addcolumn.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.button_addcolumn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_addcolumn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_addcolumn.ForeColor = System.Drawing.Color.Silver;
            this.button_addcolumn.Name = "button_addcolumn";
            this.button_addcolumn.UseVisualStyleBackColor = false;
            this.button_addcolumn.Click += new System.EventHandler(this.button_addcolumn_Click);
            // 
            // button_stat
            // 
            resources.ApplyResources(this.button_stat, "button_stat");
            this.button_stat.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_stat.FlatAppearance.BorderColor = System.Drawing.Color.Gray;
            this.button_stat.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_stat.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_stat.ForeColor = System.Drawing.Color.Silver;
            this.button_stat.Name = "button_stat";
            this.button_stat.UseVisualStyleBackColor = false;
            this.button_stat.Click += new System.EventHandler(this.button_stat_Click);
            // 
            // button_exit
            // 
            resources.ApplyResources(this.button_exit, "button_exit");
            this.button_exit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_exit.FlatAppearance.BorderColor = System.Drawing.Color.Gray;
            this.button_exit.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_exit.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_exit.ForeColor = System.Drawing.Color.Silver;
            this.button_exit.Name = "button_exit";
            this.button_exit.UseVisualStyleBackColor = false;
            this.button_exit.Click += new System.EventHandler(this.button_exit_Click);
            // 
            // button_beginedit
            // 
            resources.ApplyResources(this.button_beginedit, "button_beginedit");
            this.button_beginedit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_beginedit.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.button_beginedit.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_beginedit.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_beginedit.ForeColor = System.Drawing.Color.Silver;
            this.button_beginedit.Name = "button_beginedit";
            this.button_beginedit.UseVisualStyleBackColor = false;
            this.button_beginedit.Click += new System.EventHandler(this.button_beginedit_Click);
            // 
            // button_export
            // 
            resources.ApplyResources(this.button_export, "button_export");
            this.button_export.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_export.FlatAppearance.BorderColor = System.Drawing.Color.Gray;
            this.button_export.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_export.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_export.ForeColor = System.Drawing.Color.Silver;
            this.button_export.Name = "button_export";
            this.button_export.UseVisualStyleBackColor = false;
            this.button_export.Click += new System.EventHandler(this.button_export_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "dat";
            // 
            // button_new
            // 
            resources.ApplyResources(this.button_new, "button_new");
            this.button_new.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.button_new.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.button_new.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_new.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.button_new.ForeColor = System.Drawing.Color.Silver;
            this.button_new.Name = "button_new";
            this.button_new.UseVisualStyleBackColor = false;
            this.button_new.Click += new System.EventHandler(this.button_new_Click);
            // 
            // MainWindow
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(38)))), ((int)(((byte)(38)))));
            this.Controls.Add(this.button_new);
            this.Controls.Add(this.button_export);
            this.Controls.Add(this.button_beginedit);
            this.Controls.Add(this.button_exit);
            this.Controls.Add(this.button_stat);
            this.Controls.Add(this.button_addcolumn);
            this.Controls.Add(this.DataSheet);
            this.Controls.Add(this.MainWindowMenuStrip);
            this.ForeColor = System.Drawing.Color.Silver;
            this.MainMenuStrip = this.MainWindowMenuStrip;
            this.Name = "MainWindow";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWindow_FormClosing);
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DataSheet)).EndInit();
            this.MainWindowMenuStrip.ResumeLayout(false);
            this.MainWindowMenuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView DataSheet;
        private System.Windows.Forms.MenuStrip MainWindowMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_file;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_open;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_add;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_save;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_saveas;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_export;
        private System.Windows.Forms.Button button_addcolumn;
        private System.Windows.Forms.Button button_stat;
        private System.Windows.Forms.Button button_exit;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_exit;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_edit;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_changepsw;
        private System.Windows.Forms.Button button_beginedit;
        private System.Windows.Forms.Button button_export;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_addsubject;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_deletesubject;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_new;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem 学科统计ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.Button button_new;
    }
}

