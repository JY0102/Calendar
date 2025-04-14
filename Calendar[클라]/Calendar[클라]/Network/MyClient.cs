//01_MyClient.cs (가변데이터 처리)
using System;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;


namespace Calendar.Network
{
    internal delegate void LogMessage(string message);
    internal delegate void PacketMessage(Socket sock, string message);
    internal class MyClient : IDisposable
    {
        // 통신 소켓
        private Socket client = null;
        public LogMessage LogCallBack { get; set; } = null;
        public PacketMessage PacketCallBack { get; set; } = null;


        #region 0. 싱글톤 패턴
        public static MyClient Singleton { get; } = null;

        static MyClient()
        {
            Singleton = new MyClient();
        }
        private MyClient() { }
        #endregion

        #region 1. Start 호출 시 소켓 생성 및 서버 연결, 수신thread 실행
        public bool Start(string ip , int port, LogMessage log, PacketMessage pack)
        {
            try
            {
                LogCallBack = log;
                PacketCallBack = pack;

                client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                client.Connect(new IPEndPoint(IPAddress.Parse(ip), port));

                Thread tr = new Thread(WorkThread);
                tr.IsBackground = true;
                tr.Start();
                return true;
            }
            catch (Exception ex)
            {
                LogCallBack(string.Format("[Start 오류] " + ex.Message));
                return false;
            }
        }
        private void WorkThread(object obj)
        {
            while (true)
            {
                try
                {
                    //1. 수신
                    byte[] data = null;
                    RecvData(client, ref data);

                    //2. 수신 정보 출력
                    string msg = Encoding.Default.GetString(data);
                    PacketCallBack(client, msg);
                }
                catch (Exception ex)
                {
                    LogCallBack(string.Format("[recv 오류] " + ex.Message));
                    break;
                }
            }
        }
        #endregion

        #region 2. thread 종료처리
        public void Dispose()
        {
            Close();
        }
        ~MyClient()     // Garbage Collection 삭제 , Close 실행
        {
            _Close();
            GC.SuppressFinalize(this);
        }
        public void Close()
        {
            LogCallBack(string.Format("[서버 종료] "));
            // 대기 소켓 사망
            client.Close();
        }
        public void _Close()
        {
            client.Close();
        }   // LogCallback 이 두 번 되서 한 번 할라고
        #endregion

        #region 3. 기능 메서드

        #endregion

        #region 4 . 데이터 송 수신
        private void RecvData(Socket socket, ref byte[] data)
        {
            try
            {
                // 헤더 값 수신
                byte[] head = new byte[4];
                int recv_data = socket.Receive(head, 0, head.Length, SocketFlags.None);
                int size = BitConverter.ToInt32(head, 0);       // 받아야 될 크기

                // 실제 데이터 수신
                int total = 0;      // 실제 받은 크기
                int left_data = size;   // 실제 남은 크기
                data = new byte[size];

                while (total < size)
                {
                    recv_data = socket.Receive(data, total, left_data, 0);
                    if (recv_data == 0)
                        throw new Exception("상대방 소켓이 종료");
                    total += recv_data;
                    left_data -= recv_data;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void SendData(string msg)
        {
            try
            {
                byte[] data = Encoding.Default.GetBytes(msg);
                SendData(this.client, data);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        private void SendData(Socket sock , byte[] data)
        {
            try
            {
                //1. [헤더 수신] 가변 데이터 크기
                byte[] head = new byte[4];
                int size = data.Length;
                head = BitConverter.GetBytes(size);
                int send_data = sock.Send(head);

                //2. [데이터 송신] 가변 데이터를 size의 크기만큼 송신
                int total = 0;
                int left_data = size;
                while (total < size)
                {
                    send_data = sock.Send(data, total, left_data, SocketFlags.None);
                    total += send_data;
                    left_data -= send_data;
                }
            }
            catch (Exception ex)
            {
                throw new Exception("전송 실패" + ex.Message);
            }
        }
        #endregion
    }
}