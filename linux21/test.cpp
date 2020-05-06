#include<iostream>
#include<stdio.h>
int main()
{
  union Data
  {
    int a;
    char b;

  }data;
  //0x00000001
  data.a=1;
  if(data.b == 1)
  {
    printf("小端\n");

  }
  else{
    printf("大端\n");

  }
  return 0;
}
