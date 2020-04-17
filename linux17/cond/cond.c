#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
//0代表当前碗里没有面
//1代表碗里有面
int g_noodle = 0;
pthread_mutex_t lock;//定义一个互斥锁
pthread_cond_t cond;
void*ConsumeStart(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);//阻塞加锁
    if(g_noodle == 0)
    {
      //阻塞等待
      //1.将该PCB放到PCB等待队列中去
      //2.解锁
      //3.等待被唤醒
      pthread_cond_wait(&cond , &lock);
    }
    g_noodle--;
    printf("i am Consumer i Consum %d \n ",g_noodle);
    pthread_mutex_unlock(&lock);//解锁
    //通知厨子，有可能在唤醒之后，还是厨子拿到了互斥锁，判断了碗里还是有面的，所以厨子被放到了PCB等待队列当中去了，所以吃碗面的时候通知一下PCB等待队列当中的线程
    pthread_cond_signal(&cond);
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
  pthread_cond_wait(&cond,&lock);
}
    pthread_mutex_lock(&lock);//阻塞加锁
  g_noodle++;

    printf("i am Producer i Product %d \n ",g_noodle);
    pthread_mutex_unlock(&lock);//解锁
    pthread_cond_signal(&cond);
}




  return NULL;
}

int main()
{
  pthread_mutex_init(&lock , NULL);//互斥锁初始化
  pthread_cond_init(&cond , NULL);
  pthread_t tid[2];
  int ret = pthread_create(&tid[0] , NULL , ConsumeStart,NULL);
  
  if(ret < 0 )
  {
    perror("pthread_create");
    return 0;
  }
   ret = pthread_create(&tid[1] , NULL ,  ProductStart , NULL);
  
  if(ret < 0 )
  {
    perror("pthread_create");
    return 0;

  }
  int i  ; 
for( i = 0 ; i <2 ; i ++ )
{
  pthread_join(tid[i] , NULL);

}
pthread_mutex_destroy(&lock);//互斥锁销毁
pthread_cond_destroy(&cond);
  return 0;
}
