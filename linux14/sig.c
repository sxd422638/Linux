#include<stdio.h>
#include<signal.h>
#include<unistd.h>



void sigcallback(int signo)
{
  printf("i recv ig no is [%d] \n",signo);
}
int main()
{
  signal(2,sigcallback);
  while(1)
  {
  printf("i am mian thread \n ");
  sleep(1);
  }

  return 0;

}
