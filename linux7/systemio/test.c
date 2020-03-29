#include<stdio.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{



  int fd = open("./tmp.txt" , O_RDWR | O_CREAT | O_APPEND , 0664);
  if(fd < 0 )
  {
    perror("can not open");
  return 0 ;

  }
  int ret = write(fd , "linux-7" ,7);
  if (ret <0 )
  {
    perror("can not write \n");
    return 0 ;

  
  }


  lseek (fd , 5 ,SEEK_SET);




  char buf[1024] = {0};
  ret = read(fd ,buf , sizeof(buf)-1 );
  if(ret <0 )
  {
    perror("read failure");
    return 0;

  }
  else if (ret == 0 )
  {
    printf("read size [%d]\n", ret );

  }
  printf("%s \n ",buf);



  close (fd );

  return 0;

}
