using Calendar.UI;
using System;
using System.Collections.Generic;
using System.Threading;

namespace Calendar.Library
{
    internal static class WbLib
    {
        public static List<string> msgs = new List<string>();

        private static List<int> Colors = new List<int>();

        private static ConsoleKey Ready = 0;

        #region 1. 로고, 메뉴, 종료출력 메시지

        public static void Pause()
        {
            Ready = Console.ReadKey(true).Key;
        }
        public static void Logo(string message)
        {
            Ready = 0;

            Console.SetCursorPosition(0, 6);
            Console.WriteLine($"\t\t{message}");

            Thread th = new Thread(RandomThread);
            th.IsBackground = true;
            th.Start();

            th = new Thread(RainbowThread);
            th.IsBackground = true;
            th.Start();

            Pause();
        }
        public static ConsoleKey First_Screen()
        {
            Console.WriteLine("**************************");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("[F1] 회원가입 ");
            Console.WriteLine("[F2] 로그인");
            Console.WriteLine("[F3] 회원 탈퇴");
            Console.WriteLine("**************************");

            return Console.ReadKey().Key;
        }
        public static ConsoleKey Second_Screen()
        {
            Console.WriteLine("**************************");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("[F1]  일정 추가");
            Console.WriteLine("[F2]  일정 삭제");
            Console.WriteLine("[F3]  일정 보기");
            Console.WriteLine("**************************");

            return Console.ReadKey().Key;
        }
        public static ConsoleKey Third_Screen()
        {
            Console.WriteLine("**************************");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("[F1] 일정 추가");
            Console.WriteLine("[F2] 일정 삭제");
            Console.WriteLine("[F3] 일정 보기");
            Console.WriteLine("**************************");

            return Console.ReadKey().Key;
        }
        #endregion

        #region 2. 입력
        public static int InputInteger(string msg)
        {
            Console.Write(msg + " : ");
            return int.Parse(Console.ReadLine());
        }
        public static float InputFloat(string msg)
        {
            Console.Write(msg + " : ");
            return float.Parse(Console.ReadLine());
        }
        public static bool InputBool(string msg)
        {
            Console.WriteLine(msg + ":");
            return TrueOrFalse();
        }
        public static char InputChar(string msg)
        {
            Console.Write(msg + " : ");
            return char.Parse(Console.ReadLine());
        }
        public static string InputString(string msg)
        {
            Console.Write(msg + " : ");
            return Console.ReadLine();
        }
        public static ConsoleColor InputColor(string msg)
        {
            Console.WriteLine("\n");
            Console.WriteLine(msg);
            Console.WriteLine("[F1] :  Red");
            Console.WriteLine("[F2] :  DarkRed");
            Console.WriteLine("[F3] :  Yellow");
            Console.WriteLine("[F4] :  DarkYellow");
            Console.WriteLine("[F5] :  Blue");
            Console.WriteLine("[F6] :  DarkBlue");
            Console.WriteLine("[F7] :  Cyan");
            Console.WriteLine("[F8] :  DarkCyan");
            Console.WriteLine("[F9] :  Green");
            Console.WriteLine("[F10] : DarkGreen");
            Console.WriteLine("[F11] : Magenta");
            Console.WriteLine("[F12] : DarkMagenta");

            while (true)
            {
                switch (Console.ReadKey().Key)
                {
                    case ConsoleKey.F1:  return ConsoleColor.Red;
                    case ConsoleKey.F2:  return ConsoleColor.DarkRed;
                    case ConsoleKey.F3:  return ConsoleColor.Yellow;
                    case ConsoleKey.F4:  return ConsoleColor.DarkYellow;
                    case ConsoleKey.F5:  return ConsoleColor.Blue;
                    case ConsoleKey.F6:  return ConsoleColor.DarkBlue;
                    case ConsoleKey.F7:  return ConsoleColor.Cyan;
                    case ConsoleKey.F8:  return ConsoleColor.DarkCyan;
                    case ConsoleKey.F9:  return ConsoleColor.Green;
                    case ConsoleKey.F10: return ConsoleColor.DarkGreen;
                    case ConsoleKey.F11: return ConsoleColor.Magenta;
                    case ConsoleKey.F12: return ConsoleColor.DarkMagenta;
                    default: throw new Exception("잘못 입력하셨습니다.");
                }
            }
        }



        private static bool TrueOrFalse()
        {
            ConsoleKeyInfo flag = new ConsoleKeyInfo();
            while (true)
            {
                Console.WriteLine("\n\n");
                Console.WriteLine("[F9] 예 ");
                Console.WriteLine("[F10] 아니요");
                flag = Console.ReadKey();
                if (flag.Key == ConsoleKey.F9 || flag.Key == ConsoleKey.F10) break;
            }
            return flag.Key == ConsoleKey.F9;
        }
        #endregion


        #region 쓰레드
        private const int STAR_COUNT = 30;      // 별 개수
        private const int STAR_X_POS = 10;      // 별 X좌표
        private const int STAR_Y_POS = 5;       // 별 Y좌표
        public static void RainbowThread()
        {
            Thread.Sleep(500);

            while (Ready == 0)
            {
                for (int i = 0; i <= STAR_COUNT; i++)
                {
                    Console.SetCursorPosition(STAR_X_POS + i, STAR_Y_POS);
                    Console.ForegroundColor = (ConsoleColor)Colors[i];
                    Console.Write("\u2605");
                    Console.SetCursorPosition(STAR_X_POS + i, STAR_Y_POS + 2);
                    Console.Write("\u2605");

                    Console.ResetColor();
                }
                Console.WriteLine("");
                Thread.Sleep(1000);
            }
        }
        public static void RandomThread()
        {
            Random rnd = new Random();

            List<int> temp = new List<int>();

            bool flag = true;
            int idx;

            while (Ready == 0)
            {
                temp.Clear();
                for (int i = 0; i <= STAR_COUNT; i++)
                {
                    temp.Add(rnd.Next(1, 16));
                }

                flag = true;
                while (flag)
                {
                    if (Ready != 0) break;
                    idx = 0;

                    Thread.Sleep(10);
                    while (true)
                    {
                        if (Ready != 0) break;
                        else if (idx == STAR_COUNT)
                        {
                            flag = false;
                            break;
                        }
                        else if (idx == 0)
                        {
                            if (temp[idx] == temp[idx + 1])
                            {
                                temp[idx + 1] = rnd.Next(1, 16);
                                break;
                            }

                        }
                        else if(idx == STAR_COUNT -1)
                        {
                            if(temp[idx] == temp[idx + 1])
                            {
                                temp[idx] = rnd.Next(1, 16);
                                break;
                            }
                        }
                        else if (temp[idx - 1] == temp[idx] || temp[idx] == temp[idx + 1])
                        {
                            temp[idx] = rnd.Next(1, 16);
                            break;
                        }

                        idx++;
                    }
                }
                Colors = temp;
            }
        }
        #endregion

    }
}
