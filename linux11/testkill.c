#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
  printf("我要结束啦~~~~\n");
  alarm(3);
  while(1)
  {
    printf("如果打印到我啦，就说明程序有问题\n");
    sleep(1);

  }
  return 0;
}
