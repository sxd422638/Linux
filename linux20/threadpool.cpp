#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<iostream>
#include<queue>
#define THREADCOUNT 4
//线程池 = 线程安全队列 + 一大堆线程
//线程安全队列
//元素 = 数据 + 处理数据的函数地址


typedef void* (*Handler_t)(int);
class ThreadTask
{
  public:
      ThreadTask(int data , Handler_t , handler)
      {
        data_ = data;//数据
        handler_ = handler;//函数地址

      }
      ~ThreadTask()
      {
        
      }
      //使用函数处理数据
      void Run()
      {
        handler_(data_);
      }
    private:
      int data_;
      Handler_t handler_;//返回值为void* 参数为int
};




class ThreadPool
{
  public:
    ThreadPool()
    {
      capacity_ = 10;
      thread_capacity_ = THREADCOUNT;
      pthread_mutex_init(&lock_ , NULL);
      pthread_cond_init(&cond_,NULL);
      //创建线程
      bool is_create = ThreadCreate();
        if(!is_create)
        {
          printf("Threadpool Create thread failed\n");
          exit(1);
        }
    }
    ~ThreadPool()
    {

    }
    bool Push(ThreadTask* tt ) //生产者去调用
    {
      pthread_mutex_lock(&lock_);

      que_.push(tt);
      pthread_mutex_unlock(&lock_);
      //当插入数据之后 通知线程池当中的消费线程（消费者）
      pthread_cond_signal(&cond_);
      return true;

    }
    bool Pop(ThreadTask ** tt )//线程池调用
    {
      *tt = que_.front();
      que_.pop();
      return true;
    }
    void ThreadJoin()
    {
      for(int i = 0 ; i <THREADCOUNT ; i++)
      {
        pthread_join(tid_[i] , NULL);
      }
    }
  private:
    //定义线程入口函数
    static void* ThreadStart(void* arg)
    {
      ThreadPool* tp = (ThreadPool*)arg;
      while(1)
      {
        //从队列当中获取数据进行消费 ， 对于不同的线程而言，在获取数据的时候是互斥的
        pthread_mutex_lock(&tp->lock_);
        ThreadTask* tt;
        while(tp->que_.empty())
        {
          //调用条件变量等待接口
          pthread_cond_wait(&tp->cond_ , &tp->lock_  );

        }
        tp->Pop(&tt);
        pthread_mutex_unlock(&tp->lock_);
        //调用队列当中元素提供的函数，去处理数据 对于不同的线程 走到该位置的时候就可以并行处理了
        tt->Run();
        delete tt;//防止内存泄漏
      }
    }
    bool ThreadCreate()
    {
      for(int i = 0 ; i < THREADCOUNT ; i++ )
      {
       int ret =  pthread_create(&tid_[i] , NULL , ThreadStart , (void*)this);
       if(ret != 0 )
       {
         perror("pthread_create");
         return false;
       }
      }
      return true;
    }
  private:
    std::queue<ThreadTask*> que_;
    size_t Capacity_;
    pthread_mutex_t lock_;//互斥
    pthread_cond_t cond_;//同步 消费线程的条件变量 并没有生产线程的条件变量
    //由于客户端的请求行为是无法控制的。所以不需要通知生产者进行生产，当生产线程有了数
//    据，就直接往线程池当中抛入就可以了，再通知消费线程来进行消费

    //线程池当中的线程初始化的时候线程数量
    size_t thread_capacity_;
    //保存线程池当中的线程表示符
    pthread_t tid_ [THREADCOUNT];  
};

void* DealData(int data)
{
  printf("%d\n",data);
  return NULL;
}
int main()
{
  ThreadPool * tp = new ThreadPool();
  for(int  i = 1 ; i <= 50 ; i++ )
  {
    ThreadTask* tt = new ThreadTask(i ,DealData ));
    tp->Push(tt);
  }
  //等待线程池当中的线程退出
  tp->ThreadJoin();
  delete tp ;
  

  return 0; 
}
