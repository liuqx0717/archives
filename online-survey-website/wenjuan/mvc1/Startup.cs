using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(mvc1.Startup))]
namespace mvc1
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
