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


namespace stumgr
{
    public static class DataFile
    {
        public const int MAX_SUBJECT_WIDTH = 128;
        public const int MAX_ID_WIDTH = 64;
        public const int MAX_NAME_WIDTH = 64;
        public const int MAX_GENDER_WIDTH = 32;
        public const int MAX_STUDENTINFO_WIDTH = MAX_ID_WIDTH + MAX_NAME_WIDTH + MAX_GENDER_WIDTH;
        //@"C:\刘权兴\代码\stumgr_krnl\Debug\stumgr_krnl.dll"
        private const string dllpath = @"stumgr_krnl.dll";

        public enum ErrorType
        {
            SUCCEEDED,
            FILE_ERROR,
            INCORRECT_PASSWORD
        };

        [DllImport("kernel32.dll")]
        private extern static int LoadLibrary(string path);
        [DllImport("kernel32.dll", EntryPoint = "GetProcAddress")]
        private extern static _OpenDataFile GetOpenDataFile(int lib, string funcName);
        [DllImport("kernel32.dll", EntryPoint = "GetProcAddress")]
        private extern static _LoadDataFile GetLoadDataFile(int lib, string funcName);
        [DllImport("kernel32.dll", EntryPoint = "GetProcAddress")]
        private extern static _SaveDataFile GetSaveDataFile(int lib, string funcName);

        public delegate ErrorType _OpenDataFile(
            string filename,
            string password,
            ref int nSubject,
            ref int nStudent
        );
        public delegate ErrorType _LoadDataFile(
            byte[] SubjectNames,
            byte[] StudentInfos,
            float[] scores
        );
        public delegate ErrorType _SaveDataFile(
             string filename,
             int nSubject,
             int nStudent,
             string password,
             byte[] SubjectNames,
             byte[] StudentInfos,
             float[] scores
        );

        public static _OpenDataFile OpenDataFile;
        public static _LoadDataFile LoadDataFile;
        public static _SaveDataFile SaveDataFile;

        public static void init()
        {
            int hModule = LoadLibrary(dllpath);
            OpenDataFile = GetOpenDataFile(hModule, "_OpenDataFile@16");
            LoadDataFile = GetLoadDataFile(hModule, "_LoadDataFile@12");
            SaveDataFile = GetSaveDataFile(hModule, "_SaveDataFile@28");
        }



    }
}