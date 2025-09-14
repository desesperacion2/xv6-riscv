#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid = getpid();
  int ppid = getppid();
  printf("Mi PID: %d, PID de mi padre: %d\n", pid, ppid);
  exit(0);
}
