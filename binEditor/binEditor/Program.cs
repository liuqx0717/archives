using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;

namespace binEditor {
    static class Program {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        /// 
        private const int MaxBuffSize = 200 * 1024 * 1024;
        private const string ext = ".BEdat";

        public static string FileName;
        public static string FullOriFileName;
        public static string FullDatFileName;
        public static string OriFileName;
        public static string DatFileName;
        public static FileStream DatFile;
        public static FileStream OriFile;
        public static long OriFileLen;
        public static bool buffered;
        public static byte[] FileBuffer;
        public static List<_item> items;

        public static long tmppos;
        

        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            if (args.Length > 0) {
                FileName = args[0];
            }
            else {
                OpenFileDialog OF = new OpenFileDialog();
                OF.FileName = "";
                OF.Filter = "所有文件|*.*";
                OF.Title = "打开文件 - binEditor";
                OF.CheckFileExists = OF.CheckPathExists = true;
                if (OF.ShowDialog() == DialogResult.Cancel) return;
                FileName = OF.FileName;
            }

            if (!File.Exists(FileName)) {
                ShowErrorMessage("文件(" + FileName + ")不存在。");
                return;
            }
            string tmp;
            tmp = Path.GetExtension(FileName);
            try {
                if (Path.GetExtension(FileName) == ext) {
                    FullDatFileName = FileName;
                    FullOriFileName = FullDatFileName.Substring(0, FullDatFileName.Length - ext.Length);
                    DatFileName = Path.GetFileName(FullDatFileName);
                    OriFileName = Path.GetFileName(FullOriFileName);
                    DatFile = new FileStream(FullDatFileName, FileMode.Open, FileAccess.ReadWrite, FileShare.None);
                    OriFile = new FileStream(FullOriFileName, FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
                    InitWithDatFile();
                }
                else {

                    FullOriFileName = FileName;
                    FullDatFileName = FullOriFileName + ext;
                    DatFileName = Path.GetFileName(FullDatFileName);
                    OriFileName = Path.GetFileName(FullOriFileName);
                    OriFile = new FileStream(FullOriFileName, FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
                    if (
                        File.Exists(FullDatFileName) &&
                        ShowQuestionMessage("检测到有关此文件的数据文件(" + Path.GetFileName(Program.FullDatFileName) + ")。\n单击“确定”打开现有数据文件；\n单击“取消”创建新的数据文件。")
                    ) {
                            DatFile = new FileStream(FullDatFileName, FileMode.Open, FileAccess.ReadWrite, FileShare.None);
                            InitWithDatFile();
                    }
                    else {
                        DatFile = new FileStream(FullDatFileName, FileMode.Create, FileAccess.ReadWrite, FileShare.None);
                        InitWithOriFile();
                    }

                    
                }
            }
            catch (Exception ex) {
                Program.ShowErrorMessage("打开文件(" + Program.FullOriFileName + ")（或其数据文件）失败。\n  -" + ex.Message);
                return;
            }

            Application.Run(new MainWindow());
        }



        public static void ShowErrorMessage(string str)
        {
            MessageBox.Show(str, "binEditor", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static bool ShowQuestionMessage(string str)
        {
            if (MessageBox.Show(str, "binEditor", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK)
                return true;
            else
                return false;
        }

        public static void ShowInfoMessage(string str)
        {
            MessageBox.Show(str, "binEditor", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        }

        private static void InitWithOriFile()
        {
            OriFileLen = OriFile.Length;
            if(OriFileLen<=MaxBuffSize) {
                FileBuffer = new byte[OriFileLen];
                OriFile.Position = 0;
                OriFile.Read(FileBuffer, 0, (int)OriFileLen);
                buffered = true;
            }
            else {
                buffered = false;
            }
            items = new List<_item>();
            SaveDatFile();
        }

        private static void InitWithDatFile()
        {
            OriFileLen = OriFile.Length;
            if (OriFileLen <= MaxBuffSize) {
                FileBuffer = new byte[OriFileLen];
                OriFile.Position = 0;
                OriFile.Read(FileBuffer, 0, (int)OriFileLen);
                buffered = true;
            }
            else {
                buffered = false;
            }
            if (DatFile.Length == 0) {
                items = new List<_item>();
                SaveDatFile();
            }
            else
                ReadDatFile();
        }
        
        public static void SaveDatFile()
        {
            IFormatter bf = new BinaryFormatter();
            DatFile.Position = 0;
            bf.Serialize(DatFile, items);
            DatFile.Flush();
        }

        public static void ReadDatFile()
        {
            IFormatter bf = new BinaryFormatter();
            DatFile.Position = 0;
            items = (List<_item>)bf.Deserialize(DatFile);
            if (buffered) {
                foreach(_item item in items) {
                    if (item.oridata != null && item.newpos!=-1) 
                        item.oridata.CopyTo(FileBuffer, item.newpos);
                    
                }
            }
        }

        public static void GetOriData(_item item)
        {
            int len, i, j;
            len = item.newpatchdata.Length;
            item.oridata = new byte[len];
            if (buffered) {
                if (item.newpos + len > OriFileLen) {
                    item.oridata = null;
                    throw (new Exception("读取条目(" + item.name + ")在(" + OriFileName + "中对应的原始数据失败。\n  -读取超出文件尾"));
                }
                for (i = (int)item.newpos, j = 0; j < len; i++, j++)
                    item.oridata[j] = FileBuffer[i];
            }
            else {
                OriFile.Position = item.newpos;
                if (OriFile.Read(item.oridata, 0, len) != len) {
                    item.oridata = null;
                    throw (new Exception("读取条目(" + item.name + ")在(" + OriFileName + "中对应的原始数据失败。\n  -读取超出文件尾"));
                }
            }
        }

        public static void Execute()
        {
            foreach(_item item in items) {
                if (item.newpos == -1) continue;
                if (item.oridata != null) {
                    OriFile.Position = item.newpos;
                    OriFile.Write(item.oridata, 0, item.oridata.Length);
                }
                if (item.enabled) {
                    try {
                        GetOriData(item);
                        OriFile.Position = item.newpos;
                        OriFile.Write(item.newpatchdata, 0, item.newpatchdata.Length);
                    }
                    catch(Exception ex) {
                        throw (new Exception("向(" + OriFileName + ")中写入条目(" + item.name + ")对应的数据失败。\n  -" + ex.Message));
                    }
                }
            }
            OriFile.Flush();
        }

        public static byte[] StringToBytes(string Str)
        {
            string tmp = string.Empty;
            List<byte> rettmp = new List<byte>(64);
            int n = 0;
            int i = 0;
            for(int j=0;j<Str.Length;j++) {
                char c = Str[j];
                if (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f') {
                    tmp += c;
                    n++;
                    if (n == 2) {
                        rettmp.Add( Convert.ToByte(tmp, 16));
                        i++;
                        n = 0;
                        tmp = "";
                    }
                }
            }
            if (n != 0) throw (new Exception("字符 0~9，a~f，A~F 出现的次数不是偶数。"));
            return rettmp.ToArray();

        }

        public static List<long> FindPos(byte[] bytes)
        {
            bool f;
            List<long> ret = new List<long>(10);
            if (bytes.Length == 0) return ret;
            if (buffered) {
                for (int i = 0; i < OriFileLen; i++) {
                    f = true;
                    for (int j = 0; j < bytes.Length; j++) {
                        if (FileBuffer[i + j] != bytes[j]) {
                            f = false;
                            break;
                        }
                    }
                    if (f) ret.Add(i);
                }
                return ret;
            }
            else {
                OriFile.Position = 0;
                for (int i = 0; i < OriFileLen; i++) {
                    f = true;
                    for (int j = 0; j < bytes.Length; j++) {
                        if (OriFile.ReadByte() != bytes[j]) {
                            f = false;
                            break;
                        }
                    }
                    if (f) ret.Add(i);
                }
                return ret;
            }

        }

        public static string BytesToString(byte[] bytes)
        {
            if (bytes == null) return "";
            StringBuilder str = new StringBuilder(bytes.Length * 3 + 5);
            for (int i = 0; i < bytes.Length; i++)
                str.AppendFormat("{0:X2} ", bytes[i]);

            return str.ToString();
        }

        public static bool isEmpty(string Str)
        {
            if (Str.Trim().Length == 0) return true;
            else return false;
        }
    }


    [Serializable]
    public class _item {
        public string name;
        public string oridescription;
        public string newdescription;
        public bool enabled;
        public long oripos;
        public long newpos;
        public byte[] oridata;
        public byte[] oripatchdata;
        public byte[] newpatchdata;

        public _item()
        {
            enabled = true;
            oripos = newpos = -1;
        }
        public void RejectChange()
        {
            newdescription = oridescription;
            newpos = oripos;
            newpatchdata = oripatchdata;
        }
        public void AcceptChange()
        {
            oridescription = newdescription;
            oripos = newpos;
            oripatchdata = newpatchdata;
        }
    }



    public class DrawBorders {
        private List<Control> _Controls;
        private Rectangle[] _Rects;
        private int[] _Indexes;
        private Pen[] _Pens;
        private Graphics _Graphics;

        public DrawBorders(Pen[] Pens, Graphics graphics)
        {
            _Controls = new List<Control>();
            _Pens = Pens;
            _Graphics = graphics;
        }

        public void AddControl(Control control)
        {
            _Controls.Add(control);
            _Rects = new Rectangle[_Controls.Count];
            _Indexes = new int[_Controls.Count];
        }

        public void UpdateBorderPositions()
        {
            for(int i = 0; i < _Controls.Count; i++) {
                _Rects[i].X = _Controls[i].Left - 1;
                _Rects[i].Y = _Controls[i].Top - 1;
                _Rects[i].Width = _Controls[i].Width + 1;
                _Rects[i].Height = _Controls[i].Height + 1;
            }
        }

        public void MouseEnter(Control control)
        {
            int index = _Controls.FindIndex(c => c == control);
            if (_Indexes[index] == 0) {
                _Indexes[index] = 1;
                _Graphics.DrawRectangle(_Pens[1], _Rects[index]);
            }
        }

        public void MouseLeave(Control control)
        {
            int index = _Controls.FindIndex(c => c == control);
            if (_Indexes[index] == 1) {
                _Indexes[index] = 0;
                _Graphics.DrawRectangle(_Pens[0], _Rects[index]);
            }
        }

        public void GetFocus(Control control)
        {
            int index = _Controls.FindIndex(c => c == control);
            _Indexes[index] = 2;
            _Graphics.DrawRectangle(_Pens[2], _Rects[index]);
        }

        public void LoseFocus(Control control)
        {
            int index = _Controls.FindIndex(c => c == control);
            _Indexes[index] = 0;
            _Graphics.DrawRectangle(_Pens[0], _Rects[index]);
        }

        public void Paint(Graphics graphics)
        {
            for (int i = 0; i < _Controls.Count; i++) {
                graphics.DrawRectangle(_Pens[_Indexes[i]], _Rects[i]);
            }
        }

    }

}
