#include<stdio.h>
#include<unistd.h>
int main()
{



 //execl("/usr/bin/ls" , "ls", "-l",NULL);
 //不会再输出printf了  如果execl执行成功 后面的不再执行 失败返回-1
 //int ret = execlp("/home/sxd/linux5/mygetenv/mygetenv","mygetenv","-l","-a","-b",NULL);
 // int ret = execlp("mygetenv","mygetenv","-l","-a","-b",NULL);
 // printf("ret : %d\n",ret );
 char* envp[3];
 envp[0] = "PATH=/HAHAHA";
 envp[1] = "MYENVP=myenvp";
 envp[2] = NULL;
 //execle("./mygetenv","mygetenv","-a","-b","-c",NULL,envp);
 char* argv[3];
 argv[0] = "mygetenv";
 argv[1] = "-a";
 argv[2] = NULL;
 //execv("./mygetenv",argv);
 //execvp("mygetenv",argv);
 execve("mygetenv",argv , envp);





 printf("linux-5 \n ");
 return 0;

}
