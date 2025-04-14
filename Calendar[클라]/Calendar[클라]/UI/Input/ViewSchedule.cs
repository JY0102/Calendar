using Calendar.Client;
using Calendar.Library;
using Calendar.Made;
using System;
using System.Collections.Generic;


namespace Calendar.UI
{
    internal class ViewCalendar
    {
        public static void Invoke()
        {
            try
            {
                DateTime date = DateTime.Now;

                while (true)
                {
                    Console.Clear();
                    Console.WriteLine("\n    W A S D 로 이동합니다.");
                    WbCalendar.ShowCalendar(date.ToShortDateString());

                    switch (Console.ReadKey(true).Key)
                    {
                        case ConsoleKey.Escape: return;
                        case ConsoleKey.W: date = date.AddDays(-7); break;
                        case ConsoleKey.S: date = date.AddDays(7); break;
                        case ConsoleKey.A: date = date.AddDays(-1); break;
                        case ConsoleKey.D: date = date.AddDays(1); break;
                        default: break;
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }
    }
}
