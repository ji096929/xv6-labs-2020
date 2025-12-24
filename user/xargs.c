#include "kernel/types.h"
#include "user/user.h"

void xargs(char *argv[])
{
  char buf[512];
  char *new_argv[10];
  int i = 0;
  while(argv[i] != 0)
  {
    new_argv[i] = argv[i];
    i++;
  }
  int num = i;
  int j = 0;
  char c;
  while(read(0,&c,1)>0)
  {
    if(c=='\n')
    {
      buf[i] = 0;
      
    }
    else
    {
        buf[i++]=c;
    }
  }
}

int main(int argc,char *argv[])
{
    if (argc < 2) {
        fprintf(2, "Usage: xargs <command>\n");
        exit(1);
    }
    else
    {
        xargs(argv+1);
    }
    exit(0);
}
