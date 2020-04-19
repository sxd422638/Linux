#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define THREADCOUNT 100000
//0代表当前碗里没有面
//1代表碗里有面
int g_noodle = 0;
pthread_mutex_t lock;//定义一个互斥锁
pthread_cond_t consume_cond;
pthread_cond_t product_cond;
void*ConsumeStart(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);//阻塞加锁
    while(g_noodle == 0)
    {
      //阻塞等待
      //1.将该PCB放到PCB等待队列中去
      //2.解锁
      //3.等待被唤醒
      pthread_cond_wait(&consume_cond , &lock);
    }
    g_noodle--;
    printf("i am Consumer i Consum %d \n ",g_noodle);
    pthread_mutex_unlock(&lock);//解锁
    //通知厨子，有可能在唤醒之后，还是厨子拿到了互斥锁，判断了碗里还是有面的，所以厨子被放到了PCB等待队列当中去了，所以吃碗面的时候通知一下PCB等待队列当中的线程
    pthread_cond_signal(&product_cond);
  }

  return NULL;
}
void*ProductStart(void* arg)
{
  (void)arg;

while(1)
{
if(g_noodle == 1)
{
  pthread_cond_wait(&product_cond,&lock);
}
    pthread_mutex_lock(&lock);//阻塞加锁
  g_noodle++;

    printf("i am Producer i Product %d \n ",g_noodle);
    pthread_mutex_unlock(&lock);//解锁
    pthread_cond_signal(&consume_cond);
}




  return NULL;
}

int main()
{
  pthread_mutex_init(&lock , NULL);//互斥锁初始化
  pthread_cond_init(&consume_cond , NULL);
  pthread_cond_init(&product_cond , NULL);
  pthread_t Consume_tid[THREADCOUNT];
  pthread_t Product_tid[THREADCOUNT];
 // pthread_t tid[2];
 int i = 0 ;
 int ret = -1;
 for(; i < THREADCOUNT ; i++ )
 {

  int ret = pthread_create(&Consume_tid[i] , NULL , ConsumeStart,NULL);
  if(ret < 0 )
  {
    perror("pthread_create");
    return 0;
  }


 }
 for(i = 0 ; i <THREADCOUNT ; i++)
 {

   ret = pthread_create(&Product_tid[1] , NULL ,  ProductStart , NULL);  
  if(ret < 0 )
  {
    perror("pthread_create");
    return 0;
  }
 }
    
  for( i = 0 ; i <THREADCOUNT ; i ++ )
{
  pthread_join(Consume_tid[i] , NULL);

  pthread_join(Product_tid[i] , NULL);
}
  pthread_mutex_destroy(&lock);//互斥锁销毁
  pthread_cond_destroy(&consume_cond);
  pthread_cond_destroy(&product_cond);
  return 0;
}
