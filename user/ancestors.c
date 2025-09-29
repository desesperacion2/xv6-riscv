#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("PID actual: %d\n", getpid());
  printf("Ancestro 0: %d\n", getancestor(0));
  printf("Ancestro 1: %d\n", getancestor(1));
  printf("Ancestro 2: %d\n", getancestor(2));
  printf("Ancestro 10: %d\n", getancestor(10));
  exit(0);
}
