using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Threading;
using System.IO;
using System.Text;
using System.Windows.Forms;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using InTheHand.Net;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.Runtime.Serialization.Formatters.Binary;


// 收到原始信息，分离字符串与CRC32：ProcessCharRead()   ->   
// 校验CRC32、显示字符串：MainWindow.OnGetMessage()    ->
// 处理命令：MainWindow.ProcessSingleCommand()

//生成单条命令字符串：GetCmdStr()   ->
//获得将要发送的数据及其CRC32：FormatBluetoothMessage()   ->
//发送：sendBluetoothMessage()



namespace pinghengxiaoche {
    static class Program {

        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        /// 
        //private static BluetoothEndPoint RemoteEndPoint;

        public const int MaxSend = 4 * 1024;
        public const int MaxReceive = 4 * 1024;

        public static bool IsSending = false;


        private static BluetoothClient Client;
        private static Stream BluetoothStream;
        private static char[] ReceiveMessageBuffer = new char[MaxReceive];
        private static byte[] SendMessageBuffer = new byte[MaxSend];
        private static int SendMessageBufferLen;
        private static int _ReceiveMessageBufferPos;
        private static Form form;



        private static int ReceiveMessageBufferPos
        {
            get {
                return _ReceiveMessageBufferPos;
            }
            set {
                _ReceiveMessageBufferPos = (value > MaxReceive - 1) ? 0 : value;
 
            }
        }


        private static Action GetMessageCallBack;            //CRC32是否正确，需要这个回调函数自己算。



        public static Tuple<string, UInt32> CurrentMessage = null;
        public static BluetoothDeviceInfo DeviceInfo;


        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainWindow());
        }


        //CRC32是否正确，需要GetMessage这个回调函数自己算。
        public static void OpenBluetoothSerialPort(Form FormInstance, Action GetMessage, Action Close)
        {
            if (BluetoothRadio.PrimaryRadio == null)
                throw new Exception("没有找到本机蓝牙设备。");

            GetMessageCallBack = GetMessage;
            form = FormInstance;
            
            
            BluetoothEndPoint RemoteEndPoint = new BluetoothEndPoint(ProgramData.Address, BluetoothService.SerialPort);
            ReceiveMessageBufferPos = 0;

            DeviceInfo = new BluetoothDeviceInfo(ProgramData.Address);

            Client = new BluetoothClient();
            Client.Connect(RemoteEndPoint);
            BluetoothStream = Client.GetStream();
            //BluetoothStream.ReadTimeout = 1000;

            Task.Run(() =>
            {
                char c;
                for (;;) {
                    try {
                        c = (char)BluetoothStream.ReadByte();

                    }
                    catch(Exception ex) {
                        FormInstance.Invoke(Close);
                        break;
                    }

                    ProcessCharRead(c);
                }
                
            });
            

        }

        private static void ProcessCharRead(char c)        //命令格式： abc:p1,p2,...\0<长度为8位的CRC32字符串>\0\0
        {
            ReceiveMessageBuffer[ReceiveMessageBufferPos] = c;

            if (c != '\0') {
                ReceiveMessageBufferPos++;
            }
            else {
                if (ReceiveMessageBufferPos == 0) return;                     //刚开始就收到'\0'，则忽略

                if (ReceiveMessageBuffer[ReceiveMessageBufferPos - 1] == '\0') {     //收到连续的两个'\0'，则结束
                    if(ReceiveMessageBufferPos<11) {             //最短的消息加上crc32校验的长度为11
                        ReceiveMessageBufferPos = 0;
                        return;
                    }
                    
                    try {
                        string Msg = new string(ReceiveMessageBuffer, 0, ReceiveMessageBufferPos - 10);
                        string crc32Str = new string(ReceiveMessageBuffer, ReceiveMessageBufferPos - 9, 8);

                        UInt32 crc32 = uint.Parse(crc32Str, System.Globalization.NumberStyles.HexNumber);

                        CurrentMessage = new Tuple<string, uint>(Msg, crc32);
                        form.Invoke(GetMessageCallBack);    //CRC32是否正确，需要这个回调函数自己算。
                       
                    }
                    catch(Exception ex) {
                        ReceiveMessageBufferPos = 0;
                        return;
                    }

                    ReceiveMessageBufferPos = 0;
                    return;
                }

                ReceiveMessageBufferPos++;
            }
        }



        //先调用FormatBluetoothMessage，再调用这个函数
        public static bool sendBluetoothMessage()
        {
            while (IsSending) Thread.Sleep(50);
            IsSending = true;
            try {
                for (int i = 0; i < SendMessageBufferLen; i++) {
                    BluetoothStream.WriteByte(SendMessageBuffer[i]);
                }
            }
            catch(Exception ex) {
                IsSending = false;
                return false;
            }
            IsSending = false;
            return true;
        }



        //除去不必要的字符，并获取CRC32
        public static UInt32 FormatBluetoothMessage(string msg)          
        {
            byte[] encoded = Encoding.ASCII.GetBytes(msg);           //转为ascii码（中文会变成问号）
            int i = 0;
            foreach(byte c in encoded) {
                if ( c == (byte)'\r' || c == (byte)'\n' || c == (byte)'\0')
                    continue;

                SendMessageBuffer[i] = c;
                i++;
            }

            //此时 i 指向最后一个非'\0'字符的下一个字符的位置
            SendMessageBuffer[i] = 0;
            i++;

            if (i + 11 > MaxSend)
                throw new Exception("发送数据超出长度限制 (" + MaxSend.ToString() + "个字符)");

            //CRC校验的时候，字符串最后一个字符'\0'也计算在内
            UInt32 crc32 = CRC32.GetSTM32CRC32(SendMessageBuffer, i);

            string crc32Str = string.Format("{0:X8}", crc32);

            //将8个字符的CRC32写入
            for(int j = 0; j < 8; j++) {
                SendMessageBuffer[i] = (byte)crc32Str[j];
                i++;
            }

            //写入最后两个'\0'
            SendMessageBuffer[i] = 0;
            i++;
            SendMessageBuffer[i] = 0;
            i++;

            SendMessageBufferLen = i;



            return crc32;
            
        }


        //生成单条命令字符串
        public static string GetCmdStr(params string[] Parts)
        {
            int i;
            StringBuilder sb = new StringBuilder(256);

            if (Parts.Length == 0) return "";
            if (Parts.Length == 1) return Parts[0] + ";";

            sb.Append(Parts[0] + ":");

            for (i = 1; i < Parts.Length - 1; i++) {
                sb.Append(Parts[i] + ",");
            }

            sb.Append(Parts[i] + ";");

            return sb.ToString();
        }


        public static void CloseBluetoothSerialPort()
        {
            Client.Close();
        }

        
        public static void ShowErrorMessage(string Msg)
        {
            MessageBox.Show(Msg, "平衡小车", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static void ShowInfoMessage(string Msg)
        {
            MessageBox.Show(Msg, "平衡小车", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }


    }


    [Serializable]
    public static class ProgramData {
        public static BluetoothAddress Address;
        public static string Name;

    }
}
