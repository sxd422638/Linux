#include<stdio.h>
#include<sys/shm.h>
#define shm_key 0x12345678//共享内存标识符
int main()
{


  int shmid = shmget(shm_key,1024,IPC_CREAT | 0664);///创建共享内存
    if(shmid <0 )
    {
      perror("shmget");
      return 0;

    }
    void* lp = shmat(shmid ,NULL , 0);//附加
    if(!lp)
    {
      perror("shmat");
      return 0;

    }

    sprintf((char*)lp , "%s-%d" , "linux",10);
    while(1)
    {

    }
    //shamdt(lp);
    //shmctl(shmid,IPC_RMID,NULL);

  return 0 ;

}
