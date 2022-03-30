#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE ((5000-300)+1)
#define MIN_PID 300
#define MAX_PID 5000

/* a header file would not work for this homework assignment.
 * However, if it did, my pid_1.h file would include the following functions:
 * allocate_map(void)
 * allocate_pid(void)
 * release_pid(int pid) 
 */


char available_pids[SIZE];

// Initiallizes an array of zeros, with zero representing an available pid for use 
int allocate_map(void) {
  for (int i = 0; i < SIZE; i++) {
    available_pids[i] = 0;
  }
  return 1;
}

// Checks for the first available pid in the array and marks it as unavailable.
// It then returns the index plus the offset of 300 as the allocated pid
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
  int mypid;
  
  allocate_map();

  for (i = 0; i < 1000; i++) {
    mypid = allocate_pid(); // use function to allocate a pid to mypid variable
    printf("PID: %d\n", mypid); // print out said pid
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
      release_pid(count+300); //release the pid at the offset
      printf("PID: %d was released\n", count+300);
      printf("status at index: %d\n", available_pids[count]);
      count++;
    }
    i++;
  }
  printf("*** DONE ***\n");
  return 0;
}
