//Packet.cs
using Calendar.Data;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;


namespace Calendar.NetworkPacket
{
    internal delegate void LogMessage(string message);
    internal static class Packet
    {
        private const int X_POS = 50;
        private const int Y_POS = 8;

        public static LogMessage LogCallBack { get; set; } = null;

        #region FLAG
        public const int PACKET_INSERTUSER = 1;
        public const int PACKET_INSERTUSER_ACK = 11;

        public const int PACKET_LOGINUSER = 2;
        public const int PACKET_LOGINUSER_ACK = 21;

        public const int PACKET_ADDSCHEDULE = 3;
        public const int PACKET_ADDSCHEDULE_ACK = 31;

        public const int PACKET_DELSCHEDULE = 4;
        public const int PACKET_DELSCHEDULE_ACK = 41;

        public const int PACKET_UPDATESCHEDULE = 5;
        public const int PACKET_UPDATESCHEDULE_ACK = 51;

        public const int PACKET_DELETEUSER = 6;
        public const int PACKET_DELETEUSER_ACK = 61;
        #endregion

        #region Client -> Server
        public static string InsertUser(string id , string pw)
        {
            string packet = PACKET_INSERTUSER + "@";

            packet += id + "#";
            packet += pw;

            return packet;
        }
        public static string LoginUser(string id , string pw)
        {
            string packet = PACKET_LOGINUSER + "@";

            packet += id + "#";
            packet += pw;

            return packet;
        }
        public static string AddSchedule(string json)
        {
            string packet = PACKET_ADDSCHEDULE + "@";

            packet += Schedule.Id +"#";
            packet += json;

            return packet;
        }
        public static string DelSchedule(string json)
        {
            string packet = PACKET_DELSCHEDULE + "@";

            packet += Schedule.Id + "#";
            packet += json;

            return packet;
        }
        public static string DeleteUser(string id , string pw)
        {
            string packet = PACKET_DELETEUSER + "@";

            packet += id + "#";
            packet += pw;

            return packet;
        }
        #endregion

        #region Server -> Client
        public static void InsertUserAck(string msg)
        {
            string[] sp = msg.Split('#');

            bool flag = bool.Parse(sp[0]);
            string info = sp[1];


            if (flag)
            {
                LogCallBack("회원가입이 성공했습니다");
            }
            else
            {
                LogCallBack($" 회원가입 ERROR : {info}");
            }
        }
        public static void LoginUserAck(string msg)
        {
            string[] sp = msg.Split('#');

            bool flag = bool.Parse(sp[0]);
            string info = sp[1];
            string id = sp[2];

            if (flag)
            {
                Schedule.Id = id;
                LogCallBack($"{id}로그인에 성공했습니다");
            }
            else
            {
                LogCallBack($" 로그인 ERROR : {info}");
            }
        }
        public static void AddScheduleAck(string msg)
        {
            string[] sp = msg.Split('#');

            bool flag = bool.Parse(sp[0]);
            string info = sp[1];

            if (flag)
            {
                LogCallBack($" 일정 추가에 성공했습니다");
            }
            else
            {
                LogCallBack($" 일정추가 ERROR : {info}");
            }
            return ;
        }
        public static void DelScheduleAck(string msg)
        {
            string[] sp = msg.Split('#');

            bool     flag    = bool.Parse(sp[0]);
            string   info    = sp[1];

            if (flag)
            {
                LogCallBack($" 일정 삭제에 성공했습니다");
            }
            else
            {
                LogCallBack($" 일정삭제 ERROR : {info}");
            }

            return;
        }
        public static void UpdateScheduleAck(string json)
        {
            Schedule.ScheduleData = JsonConvert.DeserializeObject<Dictionary<Date,List<string>>>(json);

            // 리스트 출력
        }
        public static void DeleteUserAck(string msg)
        {
            string[] sp = msg.Split('#');

            bool flag = bool.Parse(sp[0]);
            string info = sp[1];
            string id = sp[2];

            if (flag)
            {
                LogCallBack($"{id} : 회원삭제 성공했습니다");
            }
            else
            {
                LogCallBack($" 회원삭제 ERROR : {info}");
            }
        }
        #endregion


        #region Init
        public static void Init(LogMessage log)
        {
            LogCallBack = log;
        }
        #endregion
    }
}
