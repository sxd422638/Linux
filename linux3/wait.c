#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0 )
  {
    return -1 ;

  
  }
  else if(pid == 0 )
  {

    //child
    printf("i am a child\n ");
  }
  else 
  {
  wait(NULL);
    //father
    while(1)
    {
      printf("hello\n");
      sleep(1);    
    }
  }
  return 0 ;

}


