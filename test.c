#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

void (*oldHandler1)(int);

void myhandler(int signo) {
    signal(SIGINT, oldHandler1);
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("yes ctrl c %d\n", i);
    }
}

int main() {
    oldHandler1 = signal(SIGINT, SIG_IGN);
    while (1) {
        signal(SIGINT, myhandler);
        printf("no ctrl c\n");
        sleep(1);
    }
}