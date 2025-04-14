using Calendar.Client;
using Calendar.Library;
using System;


namespace Calendar.UI
{
    internal class LoginUser
    {
        public static void Invoke()
        {
            try
            {
                string id = WbLib.InputString("\nID");
                string pw = WbLib.InputString("PW");

                MainControl.Singleton.UserLogin(id, pw);
            }
            catch (Exception ex)
            {
                throw new Exception("LoginUser ERROR :" + ex.Message);
            }
        }
    }
}
