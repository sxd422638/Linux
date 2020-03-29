#include<stdio.h>

int main()
{
  FILE* fp = fopen ("tmp.txt","r+");
  if(!fp )
  {

  
    perror("can not find \n");
  
  return 0;
  }


  char arr[1024] = {0};
  int ret = fread(arr , 1 ,sizeof(arr) - 1 , fp );
  if(ret ==  7) 
  {
    printf("read size [%d]\n", ret );

  
  }
  fclose(fp);
  return 0 ;
}
