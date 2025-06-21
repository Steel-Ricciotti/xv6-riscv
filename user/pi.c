#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
       if (fork() == 0) { // Child
           while(1); //Run forever
        }exit(0); // Parent exits
    }
    
