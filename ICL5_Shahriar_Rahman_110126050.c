#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void (*oldHandler1)(int);

int ctrl_c_counter = 0;

void myhandler(int signo) {
    //checking signal type
    if (signo == SIGINT) {
        ctrl_c_counter++;
        if (ctrl_c_counter == 1) {
            // First Ctrl+C:
            printf("Press CTR-C within 6 seconds to kill the process\n");
            // Setting alarm to 6 seconds
            alarm(6);
        } else if (ctrl_c_counter == 2) {
            // Second Ctrl+C: Treat as Ctrl+Z (SIGSTOP)
            // Sending SIGSTOP to itself
            kill(getpid(), SIGSTOP);
        }
    } else if (signo == SIGALRM) {
        // Alarm signal: Reset the handler and count
        signal(SIGINT, myhandler);
        ctrl_c_counter = 0;
    }
}

int main() {
    oldHandler1 = signal(SIGINT, myhandler);
    // Registering alarm signal handler
    signal(SIGALRM, myhandler);
    while (1) {
        printf("Only one CTR-C does not work on this program\n");
        sleep(1);
    }
}
