using Calendar.Client;
using Calendar.Library;
using System;


namespace Calendar.UI
{
    internal class DeleteUser
    {
        public static void Invoke()
        {
            try
            {
                string id = WbLib.InputString("\nID");
                string pw = WbLib.InputString("PW");

                MainControl.Singleton.UserDelete(id, pw);
            }
            catch (Exception ex)
            {
                throw new Exception("DeleteUser ERROR :" + ex.Message);
            }
        }
    }
}
