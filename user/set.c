#include "kernel/types.h"
#include "user/user.h"
// #include "kernel/pstate.h"

int main(int argc, char *argv[]) {
    //parse command line arguments
    int pid = atoi(argv[1]);       // First argument is PID
    int priority = atoi(argv[2]);  // Second argument is priori
    
    printf("Setting priority for pid %d to %d\n", pid, priority);
    set(pid, priority);
    // printf("Process state test\n");
    exit(0);
}