#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define THREADCOUNT 4
int g_tickets = 100 ;
void* ThreadStart(void* arg)
{
  (void)arg;
  while(1)
  {
    if(g_tickets > 0 )
    {

      g_tickets--;
      //100-1=99
      usleep(100000);
      printf("i am thread [%p] , i have ticket number is [%d] \n",pthread_self(),g_tickets + 1);
    }
    else
    {
      break;
    }
  }
  return NULL;

}
int main()
{  
  pthread_t tid[THREADCOUNT];
  int i = 0;
  for(i=0; i<THREADCOUNT;i++)
    {
       int ret =  pthread_create(&tid[i],NULL, ThreadStart ,NULL);
        if(ret < 0 )
       {
       perror("error");
       return 0;
       }
    }
    for(i = 0 ;i<THREADCOUNT;i++)
    {
      pthread_join(tid[i], NULL);
    }




  return 0;

}
