#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

void action(int signo) {
}

int main(int argc, char *argv[]) {
    pid_t pid1, pid2, pid0;
    pid0 = getpid(); // Corrected from getppid()
    pid1 = fork();
    pid2 = fork();
    if (pid1 > 0 && pid2 > 0) { // Parent
        signal(SIGUSR2, action);
        while (1) {
            pause();
            printf("Main\n");
            sleep(2);
            kill(pid1, SIGUSR1); // Corrected from kill(0, SIGSTOP)
        }
    } else if (pid1 == 0 && pid2 > 0) { // Child 1
        signal(SIGUSR1, action);
        while (1) {
            pause();
            printf("Child 1\n");
            sleep(2);
            kill(pid2, SIGUSR2); // Corrected from kill(0, SIGUSR1)
        }
    } else if (pid1 > 0 && pid2 == 0) { // Child 2
        signal(SIGUSR2, action);
        while (1) {
            printf("Child 2\n");
            sleep(2);
            kill(pid0, SIGUSR2); // Corrected from kill(0, SIGUSR2)
            pause();
        }
    }
    return 0;
}
