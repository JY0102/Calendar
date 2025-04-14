using Calendar.Client;
using Calendar.Library;
using System;


namespace Calendar.UI
{
    internal class InsertUser
    {
        public static void Invoke()
        {
            try
            {
                string id = WbLib.InputString("\nID");
                string pw = WbLib.InputString("PW");

                MainControl.Singleton.UserInsert(id, pw);
            }
            catch (Exception ex)
            {
                throw new Exception("InsertUser ERROR :" + ex.Message);
            }
        }
    }
}
