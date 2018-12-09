using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace stumgr
{
    static class Program
    {
        public static string newpassword;
        public static string password;
        public static string subjectname;
        public static string[] subjects;
        public static float[] averages;
        public static float[] variances;
        public static int nSubject;
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            newpassword = "123456";
            DataFile.init();
            Application.Run(new MainWindow());
        }
    }
}
