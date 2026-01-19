/*
1 解析原生传入的命令行参数（命令和参数）
2 从标准输入中逐行读取
3 将读取的解析为参数
4 将读取的参数追加到命令参数后面
5 用fork和exec执行命令
6 父进程等待子进程完成
*/
#include "kernel/types.h"

#include "kernel/fs.h"
#include "kernel/param.h"

#include "user/user.h"
#define MAXSIZE 256

int main(int argc, char *argv[]) {

  if (argc < 2) {
    exit(1);
  }
  char *xagrv[MAXARG];
  int xagrc = 0;
  sleep(10);
  // 1
  for (int i = 1; i < argc; i++) {
    xagrv[xagrc++] = argv[i];
  }

  // 2
  char buf[MAXSIZE];
  read(0, buf, MAXSIZE);

  // 3
  char *p = buf;
  for (int i = 0; i < MAXSIZE; i++) {
    if (buf[i] == '\n') {

      int pid = fork();
      // 5
      if (pid > 0) {
        p=&buf[i+1];
        wait(0);
      } else {
        // 4
        buf[i] = 0;
        xagrv[xagrc] = p;
        xagrc++;
        xagrv[xagrc] = 0;
        exec(xagrv[0], xagrv);
        exit(1);
      }
    }
  }
  exit(0);
  return 0;
}