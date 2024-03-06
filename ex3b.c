#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

void myAlarmHandler(int signum) {
    printf("I got a signal %d, I took care of it\n", signum);
    alarm(1);
}

int main(int argc, char *argv[]) {
    signal(SIGALRM, myAlarmHandler);//install handler
    alarm(2);    // for first time
    while (1) {
        printf("I am working\n");
        sleep(1);
    }
}
