#include"tcpsvr.hpp"
//从命令行当中获取连接服务端的ip和port
int main(int argc ,char* argv[])
{

  if(argc != 3)
  {
    printf("Start Client: ./cli [server ip] [server port]\n" );
    return 0;
  }
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  TcpSvr ts;
  if(!ts.CreateSocket())
  {
    return 0;
  }
  if(!ts.Connect(ip, port))
  {
    return 0;
  }

  while(1)
  {
        printf("please enter msg to server: ");
       fflush(stdout);
       std::string buf;
        std::cin >> buf;
        ts.Send(buf);
        //服务端没有返回数据，意味着客户端TCPsocket套接字当中用的接收缓冲区当中并没有数据，没有数据可以接收，recv的flags为0的情况下，则recv接口阻塞等待
        ts.Recv(&buf);
        printf("Server say: %s\n", buf.c_str());
  }
  ts.Close();


  return 0;
}
