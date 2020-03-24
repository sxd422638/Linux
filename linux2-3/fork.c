#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{

 printf("linux66\n");

 pid_t ret = fork();
 if(ret < 0)
{
  perror("失败");
  return 0;

}
else if(ret == 0  )
{
  //child
  printf("i am child :[%d] - [%d] \n", getpid(),getppid());
}
else
{

  printf("i am father :[%d] - [%d] \n", getpid(),getppid());


}
return 0 ;
}
