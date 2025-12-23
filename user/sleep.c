#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *agrv[])
{
    char *warn = "you should pass an argument";
    int num = 0;
    if (argc == 1)
    {
        write(1, warn, strlen(warn));
        exit(0);
    }
    else
    {
        num = atoi(agrv[1]);
        sleep(num);
    }
    exit(0);
}