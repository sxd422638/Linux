#include<stdio.h>
#include<unistd.h>
#include<signal.h>




void sigcallback(int signo)
{
  printf("signo is %d\n",signo);
}
int main()
{
  signal(2 ,sigcallback);

  sigset_t set , oldset;

  sigemptyset(&set);
  sigemptyset(&oldset);
  sigfillset(&set);

  sigprocmask(SIG_BLOCK,&set,&oldset);
  getchar();

  sigprocmask(SIG_UNBLOCK,&set,NULL);
  while(1)
  {
    sleep(1);
  }
  return 0;
}
