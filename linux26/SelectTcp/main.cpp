#include "SelectSvr.hpp"

#define CHECK_RET(p) if(p != true){return -1;}

int main()
{
    TcpSvr listen_ts;
    CHECK_RET(listen_ts.CreateSocket());
    CHECK_RET(listen_ts.Bind("0.0.0.0", 19997));
    CHECK_RET(listen_ts.Listen());

    SelectSvr ss;
    ss.AddFd(listen_ts.Getfd());

    while(1)
    {
        //1.监控
        std::vector<TcpSvr> vec;
        if(!ss.SelectWait(&vec))
        {
            continue;
        }

        for(size_t i = 0; i < vec.size(); i++)
        {
            //2.接收新的连接
            if(listen_ts.Getfd() == vec[i].Getfd())
            {
                struct sockaddr_in peeraddr;
                TcpSvr peerts;
                listen_ts.Accept(&peeraddr, &peerts);
                printf("Have a new connection : [ip] : %s [port] : %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

                //将新创建出来的套接字添加到select的事件集合当中去
                ss.AddFd(peerts.Getfd());
            }
            //3.连接上有数据
            else
            {
                std::string data;
                bool ret = vec[i].Recv(&data);
                if(!ret)
                {
                    ss.DeleteFd(vec[i].Getfd());
                    vec[i].Close();
                }
                printf("client send data is [%s]\n", data.c_str());
            }
        }
    }
    return 0;
}
