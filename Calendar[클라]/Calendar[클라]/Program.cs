using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calendar.Client
{
    internal class Program
    {
        static void Main(string[] args)
        {
            App app = App.Singleton;
            app.Start();
            app.Run();
            app.Exit();
        }
    }
}
