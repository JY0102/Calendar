//AccountControl.cs
using Calendar.Data;
using Calendar.Network;
using Calendar.NetworkPacket;
using System;
using System.Collections.Generic;


namespace Calendar.Client
{
    internal class MainControl
    {
        MyClient client = null;

        #region 0. 싱글톤 패턴
        public static MainControl Singleton { get; } = null;
        static MainControl() { Singleton = new MainControl(); }
        private MainControl()
        {
        }
        #endregion

        #region 1. 전송 메서드
        public void UserInsert(string id , string pw)
        {
            try
            {
                string packet = Packet.InsertUser(id,pw);
                client.SendData(packet);
            }
            catch (Exception ex)
            {
                throw ex; // 예외 재전송 -> 함수를 호출한 애한테 감
            }
        }
        public void UserLogin(string id, string pw)
        {
            try
            {
                string packet = Packet.LoginUser(id, pw);
                client.SendData(packet);
            }
            catch (Exception ex)
            {
                throw ex; // 예외 재전송 -> 함수를 호출한 애한테 감
            }
        }
        public void ScheduleAdd(Dictionary<Date, List<string>> temp_json)
        {
            try
            {
                string json = Schedule.ParsingJson(temp_json);

                string packet = Packet.AddSchedule(json);
                client.SendData(packet);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void ScheduleDel(Dictionary<Date, List<string>> temp_json)
        {
            try
            {
                string json = Schedule.ParsingJson(temp_json);

                string packet = Packet.DelSchedule(json);
                client.SendData(packet);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void UserDelete(string id , string pw)
        {
            try
            {
                string packet = Packet.DeleteUser(id , pw);
                client.SendData(packet);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion

        #region 2. 시작과 종료 메서드
        public void Init()
        {
            client = MyClient.Singleton;
        }
        public void Exit()
        {
            client.Dispose();
        }
        #endregion
    }
}