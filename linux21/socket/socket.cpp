#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
 int socketfd =  socket(AF_INET , SOCK_DGRAM,IPPROTO_UDP);
  printf("socketfd = %d\n" , socketfd);
  while(1)
  {
    sleep(3);
  }


  return 0;
}
