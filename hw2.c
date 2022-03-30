#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE ((5000-300)+1)
#define MIN_PID 300
#define MAX_PID 5000

// int in_use[MAX_PID + 1];
char available_pids[SIZE];

int allocate_map(void) {
  // char available_pids[SIZE];
  int pid_num = 300;
  for (int i = 0; i < SIZE; i++) {
    available_pids[i] = 0;
    pid_num++;
  }
  return 1;
}

int allocate_pid(void) {
  for (int i = 0; i < SIZE; i++) {
    if (available_pids[i] == 0) {
      available_pids[i] = 1;
      return i + 300; // returns the index plus offset of 300 to correctly identify pid
    } 
  }
  return -1;
}

int release_pid(int pid) {
  available_pids[pid-300] = 0; // sets the pid offered to zero by subtracting offset of 300
  return 0;
}

int main (int argc, char *argv[])
{
  int i, count;
  srandom(100);

  allocate_map();

  for (i = 0; i < 1000; i++) {
    available_pids[i] = allocate_pid();
    printf("PID: %d\n", available_pids[i]);
    if (available_pids[i] == -1) {
      break;
    }
  }
  printf("*** -1 at %d ***\n", i);

  // release 500
  count = 0;
  i = 0;
  while (count < 500) {
    if (available_pids[i]) {
      release_pid(available_pids[i]);
      count++;
    }
    i++;
  }
  printf("*** DONE ***\n");
  return 0;
}
