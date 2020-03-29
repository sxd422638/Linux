#include<stdio.h>
#include<unistd.h>
int main()
{


  
printf("printf  ");
fwrite("fwrite", 1, 6 ,stdout); //进入读写缓冲区
fprintf(stdout , "%s %s" , "fprintf", "66");//进入读写缓冲区
write(1,"write" , 5);//可以读取立即写入的操作
sleep(1);
return 0 ;

  
  

}
