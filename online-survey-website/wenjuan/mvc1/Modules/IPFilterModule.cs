using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

namespace mvc1.Modules {
    public class IPFilterModule : IHttpModule,IDisposable {
        private SqlConnection conn;
        public void Dispose()
        {
            conn.Close();
        }
        public void Init(HttpApplication context)
        {
            context.LogRequest += new EventHandler(OnLogRequest);
            context.BeginRequest += BeginRequest;
            context.PreRequestHandlerExecute += PreRequestHandlerExecute;
            conn = new SqlConnection("server=(local); database=WENJUAN; user id=user; password=970717;MultipleActiveResultSets=true;");
            conn.Open();

        }
        private void BeginRequest(object sender, EventArgs e)
        {

        }

        private void PreRequestHandlerExecute(object sender, EventArgs e)
        {
            bool denied = false;
            HttpApplication app = sender as HttpApplication;
            HttpRequest req = app.Context.Request;
            SqlCommand cmd = new SqlCommand("select denied from requests where ip='" + req.UserHostAddress + "';", conn);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read()) {
                if (Convert.ToByte(reader[0]) == 1) denied = true;
            }
            cmd.Dispose();
            if (denied) {
                throw new HttpException(403, "IP address denied");
            }

            cmd = new SqlCommand("execute addreq '" + req.UserHostAddress + "';", conn);
            cmd.ExecuteNonQuery();
            cmd.Dispose();
        }
        public void OnLogRequest(Object source, EventArgs e)
        {
            //custom logging logic can go here
        }
    }
}