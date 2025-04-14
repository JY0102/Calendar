using Newtonsoft.Json;
using System;
using System.Collections.Generic;


namespace Calendar.Data
{
    internal class Date : Schedule
    {
        public string Day { get; set; } = string.Empty;          // 날짜
        public ConsoleColor Color { get; set; }                 // 일정 색깔

        public Date(string day , ConsoleColor color = 0)
        {
            Day = day;
            Color = color;
        }
        public void GetColor()
        {
            try
            {
                List<Date> temp = AllList();
                foreach (Date date in temp)
                {
                    if (date.Day == Day)
                    {
                        Color = date.Color;
                    }
                }
                new Exception("없는 일정입니다.");
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
    internal class Schedule
    {
        #region 싱글톤
        public static Schedule Singleton { get; private set; } = null;
        static Schedule()
        {
            Singleton = new Schedule();
            ScheduleData = new Dictionary<Date, List<string>>();
        }
        #endregion

        public const int YEAR = 0;
        public const int MONTH = 1;
        public const int DAY = 2;

        public static string Id { get; set; } = null;
        public static Dictionary<Date, List<string>> ScheduleData { get; set; } = null;
        public Schedule() { }


        #region 기능

        /// <summary>
        /// Dictionary -> string 으로 파싱
        /// </summary>
        /// <returns>string 값으로 직렬화</returns>
        public static string ParsingJson(Dictionary<Date, List<string>> temp_json)
        {
            string json = JsonConvert.SerializeObject(temp_json);

            return json;
        }
        // Json에 있는 Data 파일을 과거부터 -> 현재 -> 미래 까지의 일정을 List에 순서대로저장
        public static List<Date> AllList()
        {
            List<Date> temp = new List<Date>();

            foreach (var data in ScheduleData)
            {
                temp.Add(data.Key);
            }
            temp.Sort((a, b) => DateTime.Parse(a.Day).CompareTo(DateTime.Parse(b.Day)));

            return temp;
        }
        // Json에 있는 Data 파일을 현재 -> 미래 까지에 저장된 일정을 List 순서대로 저장
        public static List<Date> CurrentList()
        {
            List<Date> temp = new List<Date>();

            foreach (var data in ScheduleData)
            {
                if (DateTime.Now.ToShortDateString().CompareTo(DateTime.Parse(data.Key.Day)) < 0)
                    temp.Add(data.Key);
            }
            temp.Sort((a, b) => DateTime.Parse(a.Day).CompareTo(DateTime.Parse(b.Day)));

            return temp;
        }
        #endregion
    }
}
