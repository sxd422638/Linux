//需要封装的几个接口
#pragma once 
#include<cstdio>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
class UdpSvr
{
  public:
  UdpSvr()
  {
    sock_ = -1;
  }
 
  ~UdpSvr()
  {

  }

  //1.Socket 创建套接字
  bool CreateSocket()
  {
   sock_ =  socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
    if(sock_ < 0)
    {
      perror("socket");
      return false;
    }
    return true;
  }
  //2.Bind 绑定地址信息
  bool Bind(std::string& ip , uint16_t port)
  {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    //inet_addr :
    //1.将点分十进制的ip转换为uint32
    //2.将主机字节序转换为网络字节序
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
   int ret =  bind(sock_ ,(struct sockaddr*)&addr , sizeof(addr));
   if(ret <0 )
   {
     perror("bind");
     return false;
   }
   return true;
  }
  //3.Send发送数据
  bool Send(std::string& data , struct sockaddr_in* destaddr)
  {
  int SendSize =   sendto(sock_,data.c_str(),data.size(),0 , (struct sockaddr*)destaddr,sizeof(struct sockaddr_in));
    if(SendSize < 0)
    {
      perror("sendto");
      return false;
    }
    return true;
  }
  
  //4.Recv 接收数据
  //buf : 出参 ，返回给调用者接受到了什么数据
  //srcaddr: 这条数据从哪里来的 ， 地址信息是数据源端主机的地址信息
  bool Recv(std::string* buf , struct sockaddr_in* srcaddr)
  {
    char tmp[1024] ;
    memset(tmp , '\0' ,sizeof(tmp) );
    socklen_t socklen = sizeof(struct sockaddr_in);
    //如果接受缓冲区中没有数据，且flags为0，则recvfrom会阻塞等待
   int  recvsize =  recvfrom(sock_ , tmp , sizeof(tmp) - 1 , 0 , (struct sockaddr*)srcaddr,&socklen );
    if(recvsize < 0 )
    {
      perror("recvform");
      return false;
    }
    (*buf).assign(tmp , recvsize);
    return true;
  }
  //5.Close 关闭套接字
  void Close()
  {
    close(sock_);
    sock_ = -1;
  }
  private:
    int sock_;


};
