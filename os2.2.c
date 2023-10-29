#include <stdio.h>
#include <unistd.h>

int main() {
  fork();
  printf("HI!\n");
  fork();
  printf("HI!\n");
  return 0;
}