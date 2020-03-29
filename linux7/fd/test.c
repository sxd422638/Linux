#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main()


{
  close(0);
  //关闭标准输入
  
  int fd = open ("./tmp.txt", O_RDWR | O_CREAT,0777);
  if(fd < 0 )
  {
  perror(" can not open file ");
  return 0;
  }

  printf("fd [%d] \n",fd);
  while(1)
  {
    sleep(1);

  }
return 0 ;

}
