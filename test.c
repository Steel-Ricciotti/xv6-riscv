#include <stdio.h>
#include <unistd.h>
int main() {
    int x = 5;
    int pid = fork();
    if (pid >0) {
        x += 5;
        printf("Parent: x = %d\n", x);
    } else {
        x -= 5;
        printf("Child: x = %d\n", x);
    }
    return 0;
}