#include<stdio.h>
#include<unistd.h>
#include<signal.h>




void sigcallback(int signo)
{
  printf("recv signo is %d \n ");
}
int main()
{

  signal(SIGCHLD,sigcallback);
  pid_t ret  = fork();
  if(ret <0 )
  {
    perror("can not fork\n");
    return  0;

  }
  else if(ret == 0 )
  {
    //child 
    sleep(3);
    printf("i am child , now exit \n");
    _exit(0);
    
  }
  else
  {
    //father
    while(1)
    {
      printf("i am father \n");
      
    }
  }


  return 0;
}
