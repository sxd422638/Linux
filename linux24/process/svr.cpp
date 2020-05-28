#include"tcpsvr.hpp"
#include<signal.h>
#include<sys/wait.h>
void sigcb(int signo)
{
  (void)signo;
  while(1)
  {
    waitpid(-1 , NULL , WNOHANG);
  }
}
int main(int argc , char* argv[])  //获取要侦听的端口和地址信息 ip和port

{
    if(argc != 3 )
    {
      printf("start server: ./svr [ip] [port]");
      return 0;
    }
    signal(SIGCHLD,sigcb);
    std::string ip = argv[1]; //拿到ip
    uint16_t port = atoi(argv[2]); //拿到port
    TcpSvr ts;
    if(!ts.CreateSocket())
    {
      return 0;
    }
    if(!ts.Bind(ip,port))
    {
      return 0;
    }
    if(!ts.Listen())//表示告诉服务端可以接受新连接了
    {
      return 0;
    }
  while(1)
  {

    
    TcpSvr newts;//新创建出来的需要保存新创建套接字的对象
    struct sockaddr_in peeraddr;
    if(!ts.Accept(&peeraddr , &newts))//拿到新连接
    {
      continue;
    }
    printf("Have a new connection ip = %s , port = %d \n" , inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
    int pid = fork();
    if(pid < 0 )
    {
      perror("fork");
      exit(1);
    }
    else if (pid == 0 )
    {
      //child
      while(1)
      {
        std::string buf;
        newts.Recv(&buf);//拿到了newts中新创建出来的套接字 用Recv接受缓冲区拿到数据
        printf("client did  say: %s\n" ,buf.c_str());
        printf("please return msg to client");
        fflush(stdout);
        std::cin >> buf ;
        newts.Send(buf);
        newts.Close();
        exit(1);//如果不退出子进程 子进程会进入父进程的逻辑
      }

    }
    else
    {
        //father
        newts.Close();
        
    }
  }



  return 0;

}
