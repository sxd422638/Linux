#include<pthread.h>
#include<unistd.h>
#include<queue>
#include<cstdio>
#include<iostream>
#define CAPACITY 10
#define THREADCOUNT 1
//线程安全的队列
class BlockQueue
{
  
  public:
    BlockQueue(size_t Capacity)
    {
      Capacity_ = Capacity;
      pthread_mutex_init(&Mutex_, NULL);
      pthread_cond_init(&ConsumeCond_ , NULL);
      pthread_cond_init(&ProductCond_ , NULL);
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&Mutex_);
      pthread_cond_destroy(&ConsumeCond_);
      pthread_cond_destroy(&ProductCond_);
    }
    void Push(int& Data)
    {
      pthread_mutex_lock(&Mutex_);
      while(IsFull())
      {
        pthread_cond_wait(&ProductCond_ , &Mutex_ );
      }
      Queue_.push(Data);
      pthread_mutex_unlock(&Mutex_);
      pthread_cond_signal(&ConsumeCond_);//唤醒消费者进行消费


    }
    void Pop(int* Data)
    {

      pthread_mutex_lock(&Mutex_);
      while(Queue_.empty())
      {
        pthread_cond_wait(&ConsumeCond_,&Mutex_);
      }
      *Data =  Queue_.front();
      Queue_.pop();
      pthread_mutex_unlock(&Mutex_);
      pthread_cond_signal(&ProductCond_);//唤醒生产者生产
    }
  private:
    bool IsFull()
    {
      if(Queue_.size() == Capacity_)
      {
        return true;
      }
      return false;
    }
  private:
    std::queue<int> Queue_;
    
    size_t Capacity_;//定义队列的最大容量
    pthread_mutex_t Mutex_;//互斥
    pthread_cond_t ConsumeCond_;//同步
    pthread_cond_t ProductCond_;
};

void* ConsumeStart(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;
  while(1)
  {
    int Data;
    bq->Pop(&Data);
    printf("ConsumeStart[%p][%d]\n",pthread_self(),Data);
  }
  return NULL;
}
void* ProductStart(void* arg)
{
  
  BlockQueue* bq = (BlockQueue*)arg;
  int  i = 0 ;
  while(1)
  {
    bq->Push(i);
    printf("ProductStart[%p][%d]\n"  ,pthread_self(), i  );

    i++;
  }




  return NULL;

}



int main()
{
  BlockQueue* bq = new BlockQueue(1);

  pthread_t com_tid[THREADCOUNT] , pro_tid[THREADCOUNT];
  int i = 0 ;
  for(; i < THREADCOUNT ; i++ )
  {
   int ret =  pthread_create(&com_tid[i] , NULL , ConsumeStart , (void* )bq);
   if(ret < 0 )
   {
     printf("create thread failed\n");
     return 0 ; 
   }
    ret =  pthread_create(&com_tid[i] , NULL , ProductStart , (void*)bq);
   if(ret < 0 )
   {
     printf("create thread failed\n");
     return 0 ; 
   }
  }
  for(i = 0 ; i <THREADCOUNT ; i++ )
  {
    pthread_join(com_tid[i] , NULL);
    pthread_join(pro_tid[i] , NULL);
    
      
  }
  delete bq;
  bq = NULL;
  
  
  return 0;
}
