namespace pinghengxiaoche {
    partial class MainWindow {
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
            if (disposing && (components != null)) {
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button_Connect = new System.Windows.Forms.Button();
            this.Label_BluetoothName = new System.Windows.Forms.Label();
            this.Label_BluetoothAddress = new System.Windows.Forms.Label();
            this.textBox_Receive = new System.Windows.Forms.TextBox();
            this.textBox_Send = new System.Windows.Forms.TextBox();
            this.dataGridView_Variables = new System.Windows.Forms.DataGridView();
            this.VarName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.VarValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button_ChooseDevice = new System.Windows.Forms.Button();
            this.button_Refresh = new System.Windows.Forms.Button();
            this.button_Send = new System.Windows.Forms.Button();
            this.button_ClearReiceive = new System.Windows.Forms.Button();
            this.button_ClearSend = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.button_ShowControlWindow = new System.Windows.Forms.Button();
            this.scrollBar_Send = new MyControlLibrary.ScrollBar();
            this.scrollBar_Receive = new MyControlLibrary.ScrollBar();
            this.button_Commit = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Variables)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(22, 58);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 20);
            this.label1.TabIndex = 15;
            this.label1.Text = "蓝牙名称：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(22, 87);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 20);
            this.label2.TabIndex = 16;
            this.label2.Text = "蓝牙地址：";
            // 
            // button_Connect
            // 
            this.button_Connect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(60)))), ((int)(((byte)(60)))));
            this.button_Connect.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(204)))), ((int)(((byte)(41)))));
            this.button_Connect.FlatAppearance.BorderSize = 0;
            this.button_Connect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_Connect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(90)))), ((int)(((byte)(90)))), ((int)(((byte)(90)))));
            this.button_Connect.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Connect.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_Connect.ForeColor = System.Drawing.Color.White;
            this.button_Connect.Location = new System.Drawing.Point(148, 124);
            this.button_Connect.Margin = new System.Windows.Forms.Padding(2);
            this.button_Connect.Name = "button_Connect";
            this.button_Connect.Size = new System.Drawing.Size(122, 39);
            this.button_Connect.TabIndex = 17;
            this.button_Connect.Text = "连接";
            this.button_Connect.UseVisualStyleBackColor = false;
            this.button_Connect.Click += new System.EventHandler(this.button_Connect_Click);
            this.button_Connect.Paint += new System.Windows.Forms.PaintEventHandler(this.button_Connect_Paint);
            // 
            // Label_BluetoothName
            // 
            this.Label_BluetoothName.AutoEllipsis = true;
            this.Label_BluetoothName.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Label_BluetoothName.ForeColor = System.Drawing.Color.White;
            this.Label_BluetoothName.Location = new System.Drawing.Point(106, 58);
            this.Label_BluetoothName.Name = "Label_BluetoothName";
            this.Label_BluetoothName.Size = new System.Drawing.Size(102, 20);
            this.Label_BluetoothName.TabIndex = 18;
            this.Label_BluetoothName.Text = "蓝牙名称";
            // 
            // Label_BluetoothAddress
            // 
            this.Label_BluetoothAddress.AutoSize = true;
            this.Label_BluetoothAddress.Font = new System.Drawing.Font("Consolas", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_BluetoothAddress.ForeColor = System.Drawing.Color.White;
            this.Label_BluetoothAddress.Location = new System.Drawing.Point(107, 90);
            this.Label_BluetoothAddress.Name = "Label_BluetoothAddress";
            this.Label_BluetoothAddress.Size = new System.Drawing.Size(72, 17);
            this.Label_BluetoothAddress.TabIndex = 19;
            this.Label_BluetoothAddress.Text = "蓝牙地址";
            // 
            // textBox_Receive
            // 
            this.textBox_Receive.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_Receive.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.textBox_Receive.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox_Receive.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox_Receive.ForeColor = System.Drawing.Color.White;
            this.textBox_Receive.Location = new System.Drawing.Point(286, 62);
            this.textBox_Receive.Margin = new System.Windows.Forms.Padding(2);
            this.textBox_Receive.MaxLength = 10000000;
            this.textBox_Receive.Multiline = true;
            this.textBox_Receive.Name = "textBox_Receive";
            this.textBox_Receive.Size = new System.Drawing.Size(573, 389);
            this.textBox_Receive.TabIndex = 20;
            this.textBox_Receive.TextChanged += new System.EventHandler(this.textBox_Receive_TextChanged);
            this.textBox_Receive.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_Receive_KeyDown);
            // 
            // textBox_Send
            // 
            this.textBox_Send.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_Send.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.textBox_Send.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox_Send.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox_Send.ForeColor = System.Drawing.Color.White;
            this.textBox_Send.Location = new System.Drawing.Point(286, 467);
            this.textBox_Send.Margin = new System.Windows.Forms.Padding(2);
            this.textBox_Send.Multiline = true;
            this.textBox_Send.Name = "textBox_Send";
            this.textBox_Send.Size = new System.Drawing.Size(573, 146);
            this.textBox_Send.TabIndex = 21;
            this.textBox_Send.TextChanged += new System.EventHandler(this.textBox_Send_TextChanged);
            this.textBox_Send.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_Send_KeyDown);
            // 
            // dataGridView_Variables
            // 
            this.dataGridView_Variables.AllowUserToAddRows = false;
            this.dataGridView_Variables.AllowUserToDeleteRows = false;
            this.dataGridView_Variables.AllowUserToResizeColumns = false;
            this.dataGridView_Variables.AllowUserToResizeRows = false;
            dataGridViewCellStyle4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(60)))), ((int)(((byte)(60)))));
            this.dataGridView_Variables.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle4;
            this.dataGridView_Variables.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.dataGridView_Variables.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;
            this.dataGridView_Variables.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.dataGridView_Variables.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGridView_Variables.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.dataGridView_Variables.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(60)))), ((int)(((byte)(60)))));
            dataGridViewCellStyle5.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView_Variables.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
            this.dataGridView_Variables.ColumnHeadersHeight = 25;
            this.dataGridView_Variables.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.dataGridView_Variables.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.VarName,
            this.VarValue});
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            dataGridViewCellStyle6.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.Color.White;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(204)))), ((int)(((byte)(41)))));
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView_Variables.DefaultCellStyle = dataGridViewCellStyle6;
            this.dataGridView_Variables.EnableHeadersVisualStyles = false;
            this.dataGridView_Variables.GridColor = System.Drawing.SystemColors.ControlDarkDark;
            this.dataGridView_Variables.Location = new System.Drawing.Point(26, 182);
            this.dataGridView_Variables.Margin = new System.Windows.Forms.Padding(2);
            this.dataGridView_Variables.MultiSelect = false;
            this.dataGridView_Variables.Name = "dataGridView_Variables";
            this.dataGridView_Variables.RowHeadersVisible = false;
            this.dataGridView_Variables.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dataGridView_Variables.RowTemplate.Height = 25;
            this.dataGridView_Variables.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.dataGridView_Variables.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_Variables.Size = new System.Drawing.Size(244, 401);
            this.dataGridView_Variables.TabIndex = 22;
            this.dataGridView_Variables.CellBeginEdit += new System.Windows.Forms.DataGridViewCellCancelEventHandler(this.dataGridView_Variables_CellBeginEdit);
            this.dataGridView_Variables.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_Variables_CellDoubleClick);
            this.dataGridView_Variables.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_Variables_CellEndEdit);
            this.dataGridView_Variables.Leave += new System.EventHandler(this.dataGridView_Variables_Leave);
            // 
            // VarName
            // 
            this.VarName.HeaderText = "Name";
            this.VarName.Name = "VarName";
            this.VarName.ReadOnly = true;
            this.VarName.Width = 143;
            // 
            // VarValue
            // 
            this.VarValue.HeaderText = "Value";
            this.VarValue.Name = "VarValue";
            // 
            // button_ChooseDevice
            // 
            this.button_ChooseDevice.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(60)))), ((int)(((byte)(60)))));
            this.button_ChooseDevice.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(204)))), ((int)(((byte)(41)))));
            this.button_ChooseDevice.FlatAppearance.BorderSize = 0;
            this.button_ChooseDevice.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_ChooseDevice.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(90)))), ((int)(((byte)(90)))), ((int)(((byte)(90)))));
            this.button_ChooseDevice.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_ChooseDevice.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_ChooseDevice.ForeColor = System.Drawing.Color.White;
            this.button_ChooseDevice.Location = new System.Drawing.Point(26, 124);
            this.button_ChooseDevice.Margin = new System.Windows.Forms.Padding(2);
            this.button_ChooseDevice.Name = "button_ChooseDevice";
            this.button_ChooseDevice.Size = new System.Drawing.Size(122, 39);
            this.button_ChooseDevice.TabIndex = 23;
            this.button_ChooseDevice.Text = "选择";
            this.button_ChooseDevice.UseVisualStyleBackColor = false;
            this.button_ChooseDevice.Click += new System.EventHandler(this.button_ChooseDevice_Click);
            // 
            // button_Refresh
            // 
            this.button_Refresh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Refresh.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.button_Refresh.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.button_Refresh.FlatAppearance.BorderSize = 0;
            this.button_Refresh.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_Refresh.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.button_Refresh.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Refresh.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_Refresh.ForeColor = System.Drawing.Color.White;
            this.button_Refresh.Location = new System.Drawing.Point(26, 583);
            this.button_Refresh.Margin = new System.Windows.Forms.Padding(2);
            this.button_Refresh.Name = "button_Refresh";
            this.button_Refresh.Size = new System.Drawing.Size(122, 30);
            this.button_Refresh.TabIndex = 24;
            this.button_Refresh.Text = "刷新";
            this.toolTip1.SetToolTip(this.button_Refresh, "双击条目以刷新单条");
            this.button_Refresh.UseVisualStyleBackColor = false;
            this.button_Refresh.Click += new System.EventHandler(this.button_Refresh_Click);
            // 
            // button_Send
            // 
            this.button_Send.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Send.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(41)))), ((int)(((byte)(204)))), ((int)(((byte)(41)))));
            this.button_Send.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_Send.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.button_Send.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Send.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_Send.ForeColor = System.Drawing.Color.White;
            this.button_Send.Location = new System.Drawing.Point(889, 583);
            this.button_Send.Margin = new System.Windows.Forms.Padding(2);
            this.button_Send.Name = "button_Send";
            this.button_Send.Size = new System.Drawing.Size(79, 30);
            this.button_Send.TabIndex = 25;
            this.button_Send.Text = "发送";
            this.toolTip1.SetToolTip(this.button_Send, "按 Ctrl+Enter 键发送");
            this.button_Send.UseVisualStyleBackColor = true;
            this.button_Send.Click += new System.EventHandler(this.button_Send_Click);
            // 
            // button_ClearReiceive
            // 
            this.button_ClearReiceive.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button_ClearReiceive.BackgroundImage = global::pinghengxiaoche.Properties.Resources.关闭;
            this.button_ClearReiceive.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button_ClearReiceive.FlatAppearance.BorderSize = 0;
            this.button_ClearReiceive.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_ClearReiceive.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.button_ClearReiceive.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_ClearReiceive.Location = new System.Drawing.Point(877, 60);
            this.button_ClearReiceive.Name = "button_ClearReiceive";
            this.button_ClearReiceive.Size = new System.Drawing.Size(18, 17);
            this.button_ClearReiceive.TabIndex = 26;
            this.button_ClearReiceive.UseVisualStyleBackColor = true;
            this.button_ClearReiceive.Click += new System.EventHandler(this.button_ClearReiceive_Click);
            // 
            // button_ClearSend
            // 
            this.button_ClearSend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_ClearSend.BackgroundImage = global::pinghengxiaoche.Properties.Resources.关闭;
            this.button_ClearSend.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button_ClearSend.FlatAppearance.BorderSize = 0;
            this.button_ClearSend.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_ClearSend.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.button_ClearSend.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_ClearSend.Location = new System.Drawing.Point(877, 465);
            this.button_ClearSend.Name = "button_ClearSend";
            this.button_ClearSend.Size = new System.Drawing.Size(18, 17);
            this.button_ClearSend.TabIndex = 27;
            this.button_ClearSend.UseVisualStyleBackColor = true;
            this.button_ClearSend.Click += new System.EventHandler(this.button_ClearSend_Click);
            // 
            // toolTip1
            // 
            this.toolTip1.IsBalloon = true;
            this.toolTip1.ToolTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.toolTip1.ToolTipTitle = "提示";
            // 
            // button_ShowControlWindow
            // 
            this.button_ShowControlWindow.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_ShowControlWindow.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(150)))), ((int)(((byte)(150)))), ((int)(((byte)(150)))));
            this.button_ShowControlWindow.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_ShowControlWindow.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.button_ShowControlWindow.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_ShowControlWindow.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_ShowControlWindow.ForeColor = System.Drawing.Color.White;
            this.button_ShowControlWindow.Location = new System.Drawing.Point(889, 342);
            this.button_ShowControlWindow.Margin = new System.Windows.Forms.Padding(2);
            this.button_ShowControlWindow.Name = "button_ShowControlWindow";
            this.button_ShowControlWindow.Size = new System.Drawing.Size(79, 30);
            this.button_ShowControlWindow.TabIndex = 31;
            this.button_ShowControlWindow.Text = "遥控...";
            this.toolTip1.SetToolTip(this.button_ShowControlWindow, "按 Ctrl+Enter 键发送");
            this.button_ShowControlWindow.UseVisualStyleBackColor = true;
            this.button_ShowControlWindow.Click += new System.EventHandler(this.button_ShowControlWindow_Click);
            // 
            // scrollBar_Send
            // 
            this.scrollBar_Send.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.scrollBar_Send.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.scrollBar_Send.EnterColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(100)))));
            this.scrollBar_Send.Location = new System.Drawing.Point(859, 467);
            this.scrollBar_Send.MinSlideBarLenght = 30;
            this.scrollBar_Send.Name = "scrollBar_Send";
            this.scrollBar_Send.PressedColor = System.Drawing.Color.Gainsboro;
            this.scrollBar_Send.Sense = 5D;
            this.scrollBar_Send.Size = new System.Drawing.Size(12, 146);
            this.scrollBar_Send.TabIndex = 29;
            this.scrollBar_Send.TextBox = this.textBox_Send;
            this.scrollBar_Send.WakedColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(100)))));
            // 
            // scrollBar_Receive
            // 
            this.scrollBar_Receive.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.scrollBar_Receive.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.scrollBar_Receive.EnterColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(100)))));
            this.scrollBar_Receive.Location = new System.Drawing.Point(859, 63);
            this.scrollBar_Receive.MinSlideBarLenght = 30;
            this.scrollBar_Receive.Name = "scrollBar_Receive";
            this.scrollBar_Receive.PressedColor = System.Drawing.Color.Gainsboro;
            this.scrollBar_Receive.Sense = 5D;
            this.scrollBar_Receive.Size = new System.Drawing.Size(12, 388);
            this.scrollBar_Receive.TabIndex = 28;
            this.scrollBar_Receive.TextBox = this.textBox_Receive;
            this.scrollBar_Receive.WakedColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(100)))));
            // 
            // button_Commit
            // 
            this.button_Commit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Commit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.button_Commit.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.button_Commit.FlatAppearance.BorderSize = 0;
            this.button_Commit.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.button_Commit.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.button_Commit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Commit.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_Commit.ForeColor = System.Drawing.Color.White;
            this.button_Commit.Location = new System.Drawing.Point(148, 583);
            this.button_Commit.Margin = new System.Windows.Forms.Padding(2);
            this.button_Commit.Name = "button_Commit";
            this.button_Commit.Size = new System.Drawing.Size(122, 30);
            this.button_Commit.TabIndex = 30;
            this.button_Commit.Text = "提交";
            this.button_Commit.UseVisualStyleBackColor = false;
            this.button_Commit.Click += new System.EventHandler(this.button_Commit_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.ClientSize = new System.Drawing.Size(983, 632);
            this.Controls.Add(this.button_ShowControlWindow);
            this.Controls.Add(this.button_Commit);
            this.Controls.Add(this.scrollBar_Send);
            this.Controls.Add(this.scrollBar_Receive);
            this.Controls.Add(this.button_ClearSend);
            this.Controls.Add(this.button_ClearReiceive);
            this.Controls.Add(this.button_Send);
            this.Controls.Add(this.button_Refresh);
            this.Controls.Add(this.button_ChooseDevice);
            this.Controls.Add(this.dataGridView_Variables);
            this.Controls.Add(this.textBox_Send);
            this.Controls.Add(this.textBox_Receive);
            this.Controls.Add(this.Label_BluetoothAddress);
            this.Controls.Add(this.Label_BluetoothName);
            this.Controls.Add(this.button_Connect);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "MainWindow";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Variables)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button_Connect;
        private System.Windows.Forms.Label Label_BluetoothName;
        private System.Windows.Forms.Label Label_BluetoothAddress;
        private System.Windows.Forms.TextBox textBox_Receive;
        private System.Windows.Forms.TextBox textBox_Send;
        private System.Windows.Forms.DataGridView dataGridView_Variables;
        private System.Windows.Forms.Button button_ChooseDevice;
        private System.Windows.Forms.Button button_Refresh;
        private System.Windows.Forms.Button button_Send;
        private System.Windows.Forms.Button button_ClearReiceive;
        private System.Windows.Forms.Button button_ClearSend;
        private System.Windows.Forms.ToolTip toolTip1;
        private MyControlLibrary.ScrollBar scrollBar_Receive;
        private MyControlLibrary.ScrollBar scrollBar_Send;
        private System.Windows.Forms.Button button_Commit;
        private System.Windows.Forms.DataGridViewTextBoxColumn VarName;
        private System.Windows.Forms.DataGridViewTextBoxColumn VarValue;
        private System.Windows.Forms.Button button_ShowControlWindow;
    }
}

