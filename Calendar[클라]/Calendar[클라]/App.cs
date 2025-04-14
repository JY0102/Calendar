//App.cs
using System;
using System.Net.Sockets;
using System.Threading;
using Calendar.Data;
using Calendar.Library;
using Calendar.Made;
using Calendar.Network;
using Calendar.NetworkPacket;
using Calendar.UI;




namespace Calendar.Client
{
    internal class App
    {
        private const string SERVER_IP = "192.168.35.88";
        //private const string SERVER_IP = "220.90.180.96";
        private const int SERVER_PORT   = 7000;

        #region 0. 싱글톤 패턴
        public static App Singleton { get; } = null;
        static App() { Singleton = new App(); }
        private App() {}
        #endregion

        #region 1. CallBack Message
        private const int X_POS = 50;
        private const int Y_POS = 8;
        public static void LogMessage(string msg)
        {
            Console.ForegroundColor = ConsoleColor.Red;

            Console.SetCursorPosition(0, 0);
            Console.WriteLine($" >> [Log] {msg}");

            Console.ResetColor();
        }
        public static void PacketMessage(Socket sock, string message)
        {
            //2. 패킷 파싱(분석)
            string[] sp = message.Split('@');

            //3. 분석 분할 처리
            switch (int.Parse(sp[0]))
            {
                case Packet.PACKET_INSERTUSER_ACK:     Packet.InsertUserAck(sp[1]);     break;
                case Packet.PACKET_LOGINUSER_ACK:      Packet.LoginUserAck(sp[1]);      break;
                case Packet.PACKET_ADDSCHEDULE_ACK:    Packet.AddScheduleAck(sp[1]);    break;
                case Packet.PACKET_DELSCHEDULE_ACK:    Packet.DelScheduleAck(sp[1]);    break;
                case Packet.PACKET_UPDATESCHEDULE_ACK: Packet.UpdateScheduleAck(sp[1]); break;
                case Packet.PACKET_DELETEUSER_ACK:     Packet.DeleteUserAck(sp[1]);     break;
                default: LogMessage(" PACKET ERROR : 없는 flag 입니다");    break;
            }
        }
        #endregion

        #region 2. 시작 , 실행 , 종료
        public void Start()
        {
            Packet.Init(LogMessage);
            MyClient.Singleton.Start(SERVER_IP , SERVER_PORT , LogMessage , PacketMessage);
            MainControl.Singleton.Init();

            WbLib.Logo("일정 관리 프로그램");
        }

        public void Run()
        {
            First();

            Second();
        }
        public void First()
        {
            //while (Schedule.Id == null)
            while(true)
            {
                try
                {
                    Console.Clear();
                    switch (WbLib.First_Screen())
                    {
                        case ConsoleKey.Escape: LogMessage("프로그램 종료"); return;
                        case ConsoleKey.F1: InsertUser.Invoke(); break; // 회원가입
                        case ConsoleKey.F2: LoginUser.Invoke(); break;  // 로그인
                        case ConsoleKey.F3: DeleteUser.Invoke(); break; // 회원탈퇴
                        default: throw new Exception("잘못 입력하셨습니다.");
                    }
                    WbLib.Pause();
                }
                catch (Exception ex)
                {
                    LogMessage(ex.Message);
                }
            }
        }
        public void Second()
        {
            //while (Schedule.Id != null)
            while(true)
            {
                try
                {
                    Console.Clear();
                    switch (WbLib.Second_Screen())
                    {
                        case ConsoleKey.Escape: LogMessage("프로그램 종료"); Schedule.Id = null; return;
                        case ConsoleKey.F1: AddSchedule.Invoke();   break; // 일정추가
                        case ConsoleKey.F2: DelSchedule.Invoke();   break; // 일정 삭제
                        case ConsoleKey.F3: ViewCalendar.Invoke();  break; // 일정보기
                        default: throw new Exception("잘못 입력하셨습니다.");
                    }
                    WbLib.Pause();
                }
                catch (Exception ex)
                {
                    LogMessage(ex.Message);
                }
            }
        }

        public void Exit()
        {
            MainControl.Singleton.Exit();
            Console.Clear();
            WbLib.Logo("프로그램 종료 ");
        }
        #endregion
    }
}
