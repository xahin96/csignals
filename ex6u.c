#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>


void action(int signo) {
//    sleep(2);
    printf("Switching\n");
}

int main(int argc, char *argv[]) {
    pid_t pid;
    if ((pid = fork()) > 0) { //Parent
        signal(SIGUSR1, action);
        while (1) {
            printf("Parent is running\n");
            sleep(2);
            kill(pid, SIGUSR1);
            pause();
        }
    } else { //Child
        signal(SIGUSR1, action);
        while (1) {
            pause();
            printf("Child is running\n");
            sleep(2);
            kill(getppid(), SIGUSR1);
        }
    }
}

