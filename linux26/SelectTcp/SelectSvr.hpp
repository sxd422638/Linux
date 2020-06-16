#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <vector>

#include "tcpsvr.hpp"

class SelectSvr
{
    public:
        SelectSvr()
        {
            max_fd_ = -1;
            FD_ZERO(&readfds_);
        }

        ~SelectSvr()
        {
        }

        void AddFd(int fd)
        {
            //1.添加
            FD_SET(fd, &readfds_);
            //2.更新最大文件描述符
            if(fd > max_fd_)
            {
                max_fd_ = fd;
            }
        }

        void DeleteFd(int fd)
        {
            //1.删除
            FD_CLR(fd, &readfds_);
            //2.更新最大文件描述符
            for(int i = max_fd_; i >= 0; i--)
            {
                if(FD_ISSET(i, &readfds_) == 0) // 不在
                    continue;
                max_fd_ = i;
                break;
            }
        }

        bool SelectWait(std::vector<TcpSvr>* vec)
        {
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 3000;

            fd_set tmp = readfds_;
            int ret = select(max_fd_ + 1, &tmp, NULL, NULL, &tv);
            if(ret < 0)
            {
                perror("select");
                return false;
            }
            else if(ret == 0)
            {
                printf("select timeout\n");
                return false;
            }

            //正常情况
            for(int i = 0; i < max_fd_; i++)
            {
                if(FD_ISSET(i, &tmp))
                {
                    //返回就绪的文件描述符 i 返回tcp类的对象
                    TcpSvr ts;
                    ts.SetFd(i);
                    vec->push_back(ts);
                }
            }
            return true;
        }
    private:
        int max_fd_;
        fd_set readfds_;
};
评论 ( 0 )
