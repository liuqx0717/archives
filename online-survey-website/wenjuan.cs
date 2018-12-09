using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Data;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters;
using System.Runtime.Serialization.Formatters.Binary;
//using System.Text.RegularExpressions;

namespace csc1
{

    class Program
    {
        public class _data {
            public int gender; //1:男生 2:女生
            public bool[] reason; //手机的用途
            public double shouji_score; //手机的依赖程度评分
            public double zhuyili_score;//注意力水平的评分
            public int cnt;  //小游戏完整尝试的次数
        }

        static void Main(string[] args)
        {
            const int max_o = 10;
            const int shouji_n = 14;
            const int total = 24;

            SqlConnection conn;
            SqlCommand cmd,cmd2;
            conn = new SqlConnection("server=liuqx.cn; database=WENJUAN; user id=user; password=**********;MultipleActiveResultSets=true;");
            conn.Open();
            cmd = new SqlCommand("select answer,addi_answer,token from answers where dateend is not null;", conn);

            //cmd2 = new SqlCommand("select token from answers where day(dateend)=26;", conn);
            //SqlDataReader reader = cmd2.ExecuteReader();
            //int n = 0;
            //while (reader.Read()) {
            //    if (n < 2) {
            //        n++;
            //    }
            //    else {
            //        n = 0;
            //        cmd2 = new SqlCommand("update answers set datestart=dateadd(d,-1,datestart), dateend=dateadd(d,-1,dateend) where token=" + Convert.ToInt32(reader[0]).ToString() + ";", conn);
            //        cmd2.ExecuteNonQuery();
            //    }
            //}

            List<_data> data = new List<_data>();
            _data item;
            int answer;
            bool[] options;
            string[] tmp, tmp2;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read()) {
                item = new _data();
                item.shouji_score = 10;
                item.zhuyili_score = 10;
                item.reason = new bool[6];
                tmp = Convert.ToString(reader[0]).Split(',');
                tmp2 = Convert.ToString(reader[1]).Split(',');
                for (int j = 1; j < total; j++) {
                    options = new bool[max_o + 1];
                    answer = Convert.ToInt32(tmp[j]);
                    for (int k = 1; k <= max_o; k++) {
                        if ((answer & (1 << k)) > 0) options[k] = true;
                        else options[k] = false;
                    }
                    if (j <= shouji_n) calc_shouji_score(item, j, options);
                    else calc_zhuyili_score(item, j, options, Convert.ToInt32(tmp2[1]));
                }
                item.cnt = Convert.ToInt32(tmp2[1]);
                calc_zhuyili_score(item, 24, Convert.ToInt32(tmp[24]), item.cnt);
                //if ((item.shouji_score == 92&&item.zhuyili_score==49.5) || (item.shouji_score == 84&&item.zhuyili_score==57.6)) {
                //    cmd2 = new SqlCommand("delete answers where token=" + Convert.ToInt32(reader[2]).ToString() + ";", conn);
                //    cmd2.ExecuteNonQuery();
                //    continue;
                //}
                data.Add(item);

            }



            //数据输出部分，输出想要的数据
            int[] reason_cnt = new int[6] { 0, 0, 0, 0, 0, 0 };
            double[] score1 = new double[6] { 0, 0, 0, 0, 0, 0 };
            double[] score2 = new double[6] { 0, 0, 0, 0, 0, 0 };
            
            foreach (var d in data) {
                //if (d.gender == 2)
                //    Console.WriteLine("{0},{1}", d.shouji_score, d.zhuyili_score);
                for(int i = 1; i <= 5; i++) {
                    if (d.reason[i]) {
                        reason_cnt[i]++;
                        score1[i] += d.shouji_score;
                        score2[i] += d.zhuyili_score;
                    }
                }
            }
            for (int i = 1; i <= 5; i++) {
                Console.WriteLine(
                    "{0}\t{1}\t{2,10}{3,10}", 
                    i,
                    reason_cnt[i], (score1[i]/reason_cnt[i]).ToString("#0.00"),
                    (score2[i]/reason_cnt[i]).ToString("#0.00")
                );
            }

            conn.Close();

        }

        private static void calc_shouji_score(_data item ,int i, bool[] o)
        {
            int j;
            switch (i) {
                case 1:
                    if (o[1]) item.gender = 1;
                    else item.gender = 2;
                    break;
                case 2:
                    if (o[1]) item.shouji_score += 0;
                    else if(o[2]) item.shouji_score += 4;
                    else if(o[3]) item.shouji_score += 8;
                    else if(o[4]) item.shouji_score += 12;
                    else if(o[5]) item.shouji_score += 16;
                    break;
                case 3:
                    for(j = 1; j <= 5; j++) {
                        if (o[j]) item.reason[j] = true;
                        else item.reason[j] = false;
                    }
                    break;
                case 4:
                    if (o[1]) item.shouji_score += 12;
                    else if (o[2]) item.shouji_score += 8;
                    else if (o[3]) item.shouji_score += 4;
                    else if (o[4]) item.shouji_score += 0;
                    break;
                case 5:
                    if (o[1]) item.shouji_score += 12;
                    else if (o[2]) item.shouji_score += 8;
                    else if (o[3]) item.shouji_score += 4;
                    else if (o[4]) item.shouji_score += 0;
                    break;
                case 6:
                    if (o[1]) item.shouji_score += 0;
                    else if (o[2]) item.shouji_score += 4;
                    else if (o[3]) item.shouji_score += 8;
                    else if (o[4]) item.shouji_score += 12;
                    break;
                case 7:
                    if (o[1]) item.shouji_score -= 6;
                    else if (o[2]) item.shouji_score -= 6;
                    else if (o[3]) item.shouji_score -= 5;
                    else if (o[4]) item.shouji_score -= 6;
                    else if (o[5]) item.shouji_score -= 5;
                    break;
                case 8:
                    if (o[1]) item.shouji_score += 0;
                    else if (o[2]) item.shouji_score += 4;
                    else if (o[3]) item.shouji_score += 8;
                    else if (o[4]) item.shouji_score += 12;
                    break;
                case 9:
                    if (o[1]) item.shouji_score += 12;
                    else if (o[2]) item.shouji_score += 8;
                    else if (o[3]) item.shouji_score += 4;
                    else if (o[4]) item.shouji_score += 0;
                    break;
                case 10:
                    if (o[1]) item.shouji_score += 0;
                    else if (o[2]) item.shouji_score += 4;
                    else if (o[3]) item.shouji_score += 8;
                    else if (o[4]) item.shouji_score += 12;
                    break;
                case 11:
                    if (o[1]) item.shouji_score += 12;
                    else if (o[2]) item.shouji_score += 8;
                    else if (o[3]) item.shouji_score += 4;
                    else if (o[4]) item.shouji_score += 0;
                    break;
                case 12:
                    if (o[1]) item.shouji_score += 0;
                    else if (o[2]) item.shouji_score += 4;
                    else if (o[3]) item.shouji_score += 8;
                    else if (o[4]) item.shouji_score += 12;
                    else if (o[5]) item.shouji_score += 16;
                    break;
                case 13:
                    if (o[1]) item.shouji_score -= 6;
                    else if (o[2]) item.shouji_score -= 5;
                    else if (o[3]) item.shouji_score -= 7;
                    else if (o[4]) item.shouji_score -= 5;
                    else if (o[5]) item.shouji_score -= 7;
                    break;
                case 14:
                    if (o[1]) item.shouji_score += 10;
                    else if (o[2]) item.shouji_score += 5;
                    else if (o[3]) item.shouji_score += 0;

                    break;
            }
        }
        private static void calc_zhuyili_score(_data item, int i, bool[] o,int n)
        {
            double ratio1;
            if (n <= 3) {
                ratio1 = 1 - 0.1 * n - 0.0;
            }
            else if (n <= 8) {
                ratio1 = 1 - 0.1 * n - 0.1;
            }
            else {
                ratio1 = 0.1;
            }
            
            switch (i) {
                case 15:
                    if (o[1]) item.zhuyili_score += 8 * ratio1;
                    else if (o[2]) item.zhuyili_score += 6 * ratio1;
                    else if (o[3]) item.zhuyili_score += 4 * ratio1;
                    else if (o[4]) item.zhuyili_score += 2 * ratio1;
                    break;
                case 16:
                    if (o[1]) item.zhuyili_score += 8 * ratio1;
                    else if (o[2]) item.zhuyili_score += 6 * ratio1;
                    else if (o[3]) item.zhuyili_score += 4 * ratio1;
                    else if (o[4]) item.zhuyili_score += 2 * ratio1;
                    break;
                case 17:
                    if (o[1]) item.zhuyili_score += 6 * ratio1;
                    else if (o[2]) item.zhuyili_score -= 6 * ratio1;
                    else if (o[3]) item.zhuyili_score -= 5 * ratio1;
                    else if (o[4]) item.zhuyili_score += 6 * ratio1;
                    break;
                case 18:
                    if (o[1]) item.zhuyili_score += 8 * ratio1;
                    else if (o[2]) item.zhuyili_score += 6 * ratio1;
                    else if (o[3]) item.zhuyili_score += 4 * ratio1;
                    else if (o[4]) item.zhuyili_score += 2 * ratio1;
                    break;
                case 19:
                    if (o[1]) item.zhuyili_score += 2 * ratio1;
                    else if (o[2]) item.zhuyili_score += 4 * ratio1;
                    else if (o[3]) item.zhuyili_score += 6 * ratio1;
                    else if (o[4]) item.zhuyili_score += 8 * ratio1;
                    break;
                case 20:
                    if (o[1]) item.zhuyili_score += 2 * ratio1;
                    else if (o[2]) item.zhuyili_score += 4 * ratio1;
                    else if (o[3]) item.zhuyili_score += 6 * ratio1;
                    else if (o[4]) item.zhuyili_score += 8 * ratio1;
                    break;
                case 21:
                    if (o[1]) item.zhuyili_score -= 5 * ratio1;
                    else if (o[2]) item.zhuyili_score -= 5 * ratio1;
                    else if (o[3]) item.zhuyili_score -= 5 * ratio1;
                    else if (o[4]) item.zhuyili_score -= 6 * ratio1;
                    else if (o[4]) item.zhuyili_score -= 6 * ratio1;
                    break;
                case 22:
                    if (o[1]) item.zhuyili_score += 2 * ratio1;
                    else if (o[2]) item.zhuyili_score += 4 * ratio1;
                    else if (o[3]) item.zhuyili_score += 6 * ratio1;
                    else if (o[4]) item.zhuyili_score += 8 * ratio1;
                    break;
                case 23:
                    if (o[1]) item.zhuyili_score -= 4 * ratio1;
                    else if (o[2]) item.zhuyili_score -= 4 * ratio1;
                    else if (o[3]) item.zhuyili_score -= 5 * ratio1;
                    else if (o[4]) item.zhuyili_score -= 4 * ratio1;
                    break;
            }
      
        }

        private static void calc_zhuyili_score(_data item, int i, int t, int n)
        {
            double ratio2;
            if (n <= 3) {
                ratio2 = 0.1 * n + 0.0;
            }
            if (n <= 8) {
                ratio2 = 0.1 * n + 0.1;
            }
            else {
                ratio2 = 0.9;
            }
            if (i == 24) {
                if (t < 24000) {
                    item.zhuyili_score += 60 * ratio2;
                    return;
                }
                else if (t < 28000) {
                    item.zhuyili_score += 55 * ratio2;
                    return;
                }
                else if (t < 32000) {
                    item.zhuyili_score += 50 * ratio2;
                    return;
                }
                else if (t < 36000) {
                    item.zhuyili_score += 45 * ratio2;
                    return;
                }
                else if (t < 40000) {
                    item.zhuyili_score += 40 * ratio2;
                    return;
                }
                else if (t < 45000) {
                    item.zhuyili_score += 35 * ratio2;
                    return;
                }
                else if (t < 50000) {
                    item.zhuyili_score += 27 * ratio2;
                    return;
                }
                else if (t < 55000) {
                    item.zhuyili_score += 22 * ratio2;
                    return;
                }
                else if (t < 60000) {
                    item.zhuyili_score += 14 * ratio2;
                    return;
                }
                else if (t < 65000) {
                    item.zhuyili_score += 6 * ratio2;
                    return;
                }
                else {
                    item.zhuyili_score += -2 * ratio2;
                    return;
                }
            }
        }

    }



}
