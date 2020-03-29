             #include<stdio.h>
 #include<unistd.h>         
 #include<sys/wait.h>
 #include<stdlib.h>
 #include<sys/types.h>
 
 
 int main()
{
    pid_t pid = fork();
       if(pid <0 )
     {
        perror("can not fork");
        return -1;
     }                
     else if( pid == 0 ) 
         {
          //child
          printf("i am a child \n");
          sleep(5);
          exit(0);

         } 

     else 
     {
       int ret ;
       do
       {
          ret = waitpid(pid, NULL,WNOHANG);
          if(ret ==0 )
          {
            printf("The Child process is running, can't be exited\n");
            sleep(1);//1秒后再次尝试
          } while(ret == 0);
          
          if(pid == ret )
          {
            printf("child exited \n");

          }
          else{
          printf("some worng ");

          }
            
       }
      
    

     }
return 0;
}
