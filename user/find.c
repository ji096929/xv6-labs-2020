#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

void check(int fd[])
{
    close(fd[WRITE]);

    int num;
    if (read(fd[READ], &num, sizeof(int)) != sizeof(int))
    {
        close(fd[READ]);
        exit(0);
    }
    printf("prime %d\n", num);

    int fd_new[2];
    pipe(fd_new);
    if (fork() > 0)
    {
        close(fd_new[READ]);
        int next;
        while (read(fd[READ], &next, sizeof(int)) == sizeof(int))
        {
            if (next % num != 0)
            {
                write(fd_new[WRITE], &next, sizeof(int));
            }
        }
        close(fd[READ]);
        close(fd_new[WRITE]);
        wait(0);
    }
    else
    {
        close(fd_new[WRITE]);
        close(fd[READ]);
        check(fd_new);
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    int fd[2];

    // 从1写入，从0读出
    pipe(fd);

    int res = fork();
    if (res > 0)
    {
        // par
        close(fd[READ]);
        for (int i = 2; i <= 35; i++)
        {
            write(fd[WRITE], &i, sizeof(int));
        }
        close(fd[WRITE]);
        int state;
        wait(&state);
    }
    else
    {
        // chi
        check(fd);
    }
    exit(0);
}