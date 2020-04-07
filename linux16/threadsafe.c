#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define THREADCOUNT 4






void* ThreadStart(void* arg)
{
  (void)arg;
  while(1)
  {

  }
  return NULL;

}
int main()
{  
  pthread_t pid[THREADCOUNT];
  int i = 0;

    for(; i<THREADCOUNT;i++)
    {
       int ret =  pthread_create(&tid[i],UNLL,ThreadStart,NULL);
        if(ret < 0 )
       {
       perror("error");
       return 0;

  
  
       }
    }
    for(i= 0 ;i<THREADCOUNT;i++)
    {
    
    }




  return 0;

}
