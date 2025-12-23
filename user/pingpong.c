#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipe1[2];
    int pipe2[2];
    int pid;
    char buf[2];

    // 从1写入，从0读出
    pipe(pipe1);
    pipe(pipe2);

    int res = fork();
    if (res > 0)
    {
        // par
        pid = getpid();
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], "b", 1);
        read(pipe2[0], buf, 1);
        printf("%d: received pong\n", pid);
        wait(0);
        exit(0);
    }
    else
    {
        // chi
        pid = getpid();
        close(pipe2[0]);
        close(pipe1[1]);
        read(pipe1[0], buf, 1);
        printf("%d: received ping\n", pid);
        write(pipe2[1], "b", 1);
        exit(0);
    }
}