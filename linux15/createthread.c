#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

typedef struct thread_info
{
  int thread_num_;
  thread_info()
  {
   thread_num_ = -1;
  }
}THREADINFO;


void* thread_start(void* arg)
{
  THREADINFO* ti = (THREADINFO*)arg;
 
  while(1)
  {
   printf("i am new thread~~~~~:%d\n",ti->thread_num_);
   sleep(1);
  }
  //对于传递进来的堆上开辟的内存，
  //可以在线程入口函数结束的时候释放掉 不会导致程序有内存泄漏的风险
  delete ti;

  return NULL;
}
int main()
{
    pthread_t tid ;
    int ret ;

      THREADINFO* threadinfo = new thread_info();
    
      int i = 0;//i 是一个临时变脸
      for(;i <4 ; i++)
    {
      THREADINFO* threadinfo = new thread_info();
      threadinfo->thread_num_ = i ;

      ret =  pthread_create(&tid , NULL ,thread_start ,(void*)threadinfo );
    
    if(ret < 0 )
    {
      perror("pthread_create\n");

      return 0;
    }
  }
while(1)
{
  printf("i am main thread~~~~~~\n");
  sleep(1);
}
     


  return 0 ;

}
