#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
begin:
    //监控0号文件描述符的可读事件
    fd_set readfds;
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    //int ret = select(0 + 1, &readfds, NULL, NULL, NULL); //阻塞监控
    int ret = select(0 + 1, &readfds, NULL, NULL, &tv); //带有超时时间的监控
    if(ret < 0)
    {
        perror("select");
        return 0;
    }
    else if(ret == 0)
    {
        printf("select timeout\n");
        //TODO
        //循环监控 --》 返回的集合当中只返回就绪的文件描述符
        ret = FD_ISSET(0, &readfds);
        if(ret == 0)
        {
            //理论上正确的
            printf("0 fd is not in readfds\n");
            goto begin;
        }
        else if(ret != 0)
        {
            printf("0 fd is in readfds\n");
            return 0;
        }
    }

    printf("ret : %d\n", ret);
    if(FD_ISSET(0, &readfds) != 0)
    {
        char buf[1024] = {0};
        read(0, buf, sizeof(buf) - 1);
        printf("buf : %s\n", buf);
    }

    FD_CLR(0, &readfds);
    return 0;
}
