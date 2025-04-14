using Calendar.Data;
using System;
using System.Collections.Generic;

namespace Calendar.Made
{
    internal static class WbCalendar
    {
        public static List<Date> dates = new List<Date>();
        public static void MadeCalendar(string temp)
        {
            dates.Clear();
            DateTime now = DateTime.Parse(temp);
            DateTime date = DateTime.Parse(temp);

            while (true)    // 달력 가장 첫번째 일수 계산
            {
                if (date.Day > 1)
                {
                    date = date.AddDays(-1);
                }
                else
                {
                    date = date.AddDays(-(int)date.DayOfWeek);
                    dates.Add(new Date(date.ToShortDateString()));
                    dates[0].Color = ConsoleColor.DarkGray;
                    break;
                }
            }

            for (int i = 1; i < 42; i++) // 달력 채우기  = 일수 + 색깔
            {
                date = date.AddDays(1);
                dates.Add(new Date(date.ToShortDateString()));
                if (date.Month < now.Month || date.Month > now.Month)
                {
                    dates[i].Color = ConsoleColor.DarkGray;
                }
                else
                {
                    if (date.Month == now.Month && date.Day == now.Day)
                    {
                        dates[i].Color = ConsoleColor.Blue;
                    }
                    else
                    {
                        // 일정이 있는 날짜면 색깔 변경
                        foreach( Date schedule_date in Schedule.AllList())
                        {
                            if (dates[i].Day == schedule_date.Day)
                            {
                                dates[i] = schedule_date;
                            }
                        }
                        dates[i].Color = ConsoleColor.White;
                    }
                }
            }

        }
        public static void ShowCalendar(string temp)
        {
            MadeCalendar(temp);

            string[] sp = temp.Split('-');

            Console.SetCursorPosition(0, 2);
            Console.WriteLine($"    {sp[0]} 년 {sp[1]} 월 {sp[2]} 일");
            Console.WriteLine(" 일  월  화  수  목  금  토  ");

            int i = 0;
            foreach (var date in dates)
            {
                Console.ForegroundColor = date.Color;
                string[] sspp = date.Day.Split('-');
                Console.Write($" {sspp[2]} ");
                i++;
                if (i % 7 == 0) Console.WriteLine();
            }
            Console.ResetColor();
        }
    }

}
