#include "tcpsvr.hpp"
#include <string.h>
#include <sstream>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Start Server: ./svr [ip] [port]\n");
        return 0;
    }

    std::string ip  = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSvr ts;
    if(!ts.CreateSocket())
    {
        return 0;
    }

    if(!ts.Bind(ip, port))
    {
        return 0;
    }

    if(!ts.Listen())
    {
        return 0;
    }

    //为accept函数接收回来的新创建的socket准备的
    TcpSvr ser_ts;

    while(1)
    {
        struct sockaddr_in clientaddr;
        if(!ts.Accept(&clientaddr, &ser_ts))
        {
            return 0;
        }

        std::string buf;
        ser_ts.Recv(&buf);
        printf("chrome say: %s\n", buf.c_str());

        //正文信息
        //std::string body = "<html><h1>linux-66</h1></html>";
        //C风格的格式化字符串
        //char buffer[10240] = {0};
        ////响应首行\r\n
        ////响应头部
        ////  Content-Length: \r\n
        ////  Content-Type: \r\n
        ////\r\n
        ////正文
        //snprintf(buffer, sizeof(buffer) - 1, "%s %s %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n", "HTTP/1.1", "200", "OK", body.size(), "text/html");
        //printf("buffer:%s\n", buffer);
        //std::string header;
        //header.assign(buffer, strlen(buffer));

        //C++风格
        //std::string body = "<html><h1>linux-66</h1></html>";
        //std::stringstream ss;
        //ss << "HTTP/1.1 200 OK\r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "\r\n";
        //std::string header = ss.str();

        //302
        //std::string body = "<html><h1>linux-66</h1></html>";
        //std::stringstream ss;
        //ss << "HTTP/1.1 302 Found\r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "Location: https://www.baidu.com\r\n";
        //ss << "\r\n";
        //std::string header = ss.str();
        
        //404
        //std::string body = "<html><h1>linux-66</h1></html>";
        //std::stringstream ss;
        //ss << "HTTP/1.1 404 Page Not Found\r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "\r\n";
        //std::string header = ss.str();

        //502
        std::string body = "<html><h1>linux-66</h1></html>";
        std::stringstream ss;
        ss << "HTTP/1.1 502 Bad Gateway\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() << "\r\n";
        ss << "\r\n";
        std::string header = ss.str();

        ser_ts.Send(header);
        ser_ts.Send(body);
    }
    ser_ts.Close();//关闭新创建出来的套接字
    ts.Close();//关闭掉了侦听套接字
    return 0;
}
