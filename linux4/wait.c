#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>


int main()
{
  pid_t pid = fork();
  if(pid <0 )
  {
    perror("can not fork");
    return -1;
  }
  else if(pid == 0 )
  {
    //child 
    printf("i am a child \n");
    printf("my PID is : %d \n ",getpid());
    sleep(5);
    exit(0);

  }
  else 
  {
  //father
  pid = wait(NULL);
  printf("i am a father\n");
  printf("chail pid %d is over \n", pid );

  }
  return 0;
  
}
