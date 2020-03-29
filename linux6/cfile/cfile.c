#include<stdio.h>
int main()
{
  FILE* fp = fopen("tmp.txt" , "w+");
  if(!fp)
  {
    perror("can not find");
    return 0;
  }
  const char* lp = "linux-6";
 int ret =   fwrite(lp , 1 ,7 ,fp);
  if( ret == 7 )
  {
  printf("write size [%d] \n ",ret );
  
  }


  fseek(fp , 0 ,SEEK_SET);
//将文件流指针放在起始位置
  char arr[1024] = {0};
  ret = fread(arr , 1 , sizeof(arr) , fp );
  if(ret == 7 )
  {
    printf("read size [%d]\n ", ret );

  }
  fclose(fp);
  return 0 ;

}
