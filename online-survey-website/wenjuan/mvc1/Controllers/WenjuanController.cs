using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

namespace mvc1.Controllers
{
    public class WenjuanController : Controller,IDisposable { 

        private Random random;
        private SqlConnection conn;

        // GET: Wenjuan
        public ActionResult Index()
        {
            init();
            ViewBag.Title = "问卷调查";
            ViewBag.Token = gentoken(Request.UserHostAddress);
            return View();
        }

        [HttpPost]
        public ActionResult Submit(int token, string a, string a_addi)
        {
            init();
            try {
                SqlCommand cmd = new SqlCommand("execute submit " + token.ToString() + ", '" + a + "', '" + a_addi + "';",conn);
                cmd.ExecuteNonQuery();
                cmd.Dispose();
            }
            catch(Exception ex) {
                return Content("1", "text/plain");
            }

            return Content("0", "text/plain");
        }


        private void init()
        {
            if (random != null) return;
            random = new Random();
            conn = new SqlConnection("server=(local); database=WENJUAN; user id=user; password=970717;MultipleActiveResultSets=true;");
            conn.Open();
        }

        private int gentoken(string ip)
        {
            int n;
            SqlCommand cmd = new SqlCommand(";", conn);
gen:
            n=random.Next(0, 2147483647);
            try {
                cmd.CommandText="insert answers values(" + n.ToString() + ",'" + ip + "', SYSDATETIME(), null, 0, null, null);";
                cmd.ExecuteNonQuery();
            }
            catch(Exception ex) {
                goto gen;
            }
            cmd.Dispose();
            return n;
        }

        public new void Dispose()
        {
            conn.Close();
        }
    }


}