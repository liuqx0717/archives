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

    class Program {


        static void Main(string[] args)
        {

            SqlConnection conn_remote;
            SqlConnection conn_local;
            SqlCommand cmd, cmd2;
            conn_remote = new SqlConnection("server=liuqx.cn; database=WENJUAN; user id=user; password=***********;MultipleActiveResultSets=true;");
            conn_local = new SqlConnection("server=(local); database=WENJUAN; user id=user; password=***********;MultipleActiveResultSets=true;");
            conn_remote.Open();
            conn_local.Open();

            cmd = new SqlCommand("select * from answers where dateend is not null;", conn_remote);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read()) {
                cmd2 = new SqlCommand(
                    "insert answers values(" +
                    Convert.ToString(reader[0]) +
                    ",'" +
                    Convert.ToString(reader[1]) +
                    "','" +
                    Convert.ToDateTime(reader[2]).ToString("yyyy-MM-dd hh:mm:ss.fffffff") +
                    "','" +
                    Convert.ToDateTime(reader[3]).ToString("yyyy-MM-dd hh:mm:ss.fffffff") +
                    "'," +
                    Convert.ToString(reader[4]) +
                    ",'" +
                    Convert.ToString(reader[5]) +
                    "','" +
                    Convert.ToString(reader[6]) +
                    "');",
                    conn_local
                );
                cmd2.ExecuteNonQuery();
            }

            cmd = new SqlCommand("select * from answers where dateend is null;", conn_remote);
            reader = cmd.ExecuteReader();
            while (reader.Read()) {
                cmd2 = new SqlCommand(
                    "insert answers values(" +
                    Convert.ToString(reader[0]) +
                    ",'" +
                    Convert.ToString(reader[1]) +
                    "','" +
                    Convert.ToDateTime(reader[2]).ToString("yyyy-MM-dd hh:mm:ss.fffffff") +
                    "'," +
                    "null" +
                    "," +
                    "null" +
                    "," +
                    "null" +
                    "," +
                    "null" +
                    ");",
                    conn_local
                );
                cmd2.ExecuteNonQuery();
            }

            cmd = new SqlCommand("select * from requests;", conn_remote);
            reader = cmd.ExecuteReader();
            while (reader.Read()) {
                cmd2 = new SqlCommand(
                    "insert requests values('" +
                    Convert.ToString(reader[0]) +
                    "','" +
                    Convert.ToString(reader[1]) +
                    "'," +
                    Convert.ToString(reader[2]) +
                    ",'" +
                    Convert.ToDateTime(reader[3]).ToString("yyyy-MM-dd hh:mm:ss.fffffff") +
                    "');",
                    conn_local
                );
                cmd2.ExecuteNonQuery();
            }

            conn_remote.Close();
            conn_local.Close();

        }


    }

}
