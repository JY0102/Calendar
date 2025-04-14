using Calendar.Client;
using Calendar.Data;
using Calendar.Library;
using System;
using System.Collections.Generic;


namespace Calendar.UI
{
    internal class DelSchedule
    {
        public static void Invoke()
        {
            try
            {
                Dictionary<Date , List<string>> json = new Dictionary<Date, List<string>> ();

                string year  = WbLib.InputString("\n일정 제거할 년도 :");
                string month = WbLib.InputString("일정 제거할 월 :");
                string day   = WbLib.InputString("일정 제거할 일 :");

                Date date = new Date(string.Format($"{year}-{month}-{day}"));
                date.GetColor();

                while(true)
                {
                    string temp = WbLib.InputString("일정 (제거 더 안할시 빈공간 enter)");
                    if (temp != null)
                        json[date].Add(temp);
                    else
                        break;
                }
                if (json.Count == 0) throw new Exception("일정을 안썻습니다.");

                MainControl.Singleton.ScheduleDel(json);
            }
            catch (Exception ex)
            {
                throw new Exception("DelSchedule ERROR :" + ex.Message);
            }
        }
    }
}
