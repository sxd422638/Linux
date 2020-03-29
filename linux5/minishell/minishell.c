#include<stdio.h>
#include<unistd.h>
#include<string.h>

char  g_Command[1024];


int GetCommand()
{

//比如输入一个ls -l 要把输入的这一串东西保存到数组里面去
  memset(g_Command, '\0',sizeof(g_Command));
//一定要预留一个/0的位置
  if(fgets(g_Command , sizeof(g_Command) - 1, stdin ) == NULL)
    {
      printf("fgets error \n");
      return -1 ;
    }
  printf("g_Command : %s \n",g_Command);
  return 0;
}
int DealCommand(char* command)
{
  if(!command && command == '\0')
  {
     printf("command error \n");
     return -1 ;

  }
  //ls -al 区分哪一部分是命令，哪一部分是命令行参数
  int argc = 0;

  char* argv[1024] = {0};
  //argv[0] = 可执行程序的名称 保存命令
  //argv[1] = 保存命令行参数的值
  //argv[x] = NULL;
  while(*command)
  {
    while(!isspace(*command) && *command != '\0')
    {
      argv[argc] = command;
      argc++;
      //去找下一个空格了
      
      while(isspace(*command) && *command != '\0')
      {
        command++;

      }
      *command = '\0';
      
    }
    command++;
  }
  argv[argc] = NULL;
  int i;
  for(i = 0 ;i<argc ; i++)
  {
    printf("%d:%s \n ", argc , argv[i]);
  }
  return 0 ;
}
int main()
{
//用户输入 希望循环输入
  while(1)
    {
      if(GetCommand() == -1)
       {
          continue;
       }
  //处理字符串
      DealCommand(g_Command);
    }



return 0 ;

}
