using Calendar.Client;
using Calendar.Data;
using Calendar.Library;
using System;
using System.Collections.Generic;


namespace Calendar.UI
{
    internal class AddSchedule
    {
        public static void Invoke()
        {
            try
            {
                var json = new Dictionary<Date, List<string>> ();

                string year  = WbLib.InputString("\n일정 추가할 날짜 년도 :");
                string month = WbLib.InputString("일정 추가할 날짜 월 :");
                string day   = WbLib.InputString("일정 추가할 날짜 일 :");

                Date date = new Date(string.Format($"{year}-{month}-{day}"));

                while (true)
                {
                    string temp = WbLib.InputString("일정 (추가 더 안할시 빈공간 enter)");
                    if (temp != null)
                        json[date].Add(temp);
                    else
                        break;
                }
                if (json.Count == 0) throw new Exception("일정을 안썻습니다.");


                date.Color = WbLib.InputColor("일정 표시할 색깔을 선택해주세요");

                MainControl.Singleton.ScheduleAdd(json);
            }
            catch (Exception ex)
            {
                throw new Exception("AddSchedule ERROR :" + ex.Message);
            }
        }
    }
}
