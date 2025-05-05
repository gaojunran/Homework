#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipe1[2];
int pipe2[2];

void functionD(int sig) {
    printf("pong quitting\n");
    exit(0);
}

void functionC() {
    struct sigaction sa;
    sa.sa_handler = functionD;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }
    int value;
    while (1) {
        read(pipe1[0], &value, sizeof(value));
        printf("pong - %d\n", value);
        value++;
        write(pipe2[1], &value, sizeof(value));
    }
}

void functionB() {
    int value = 0;
    while (1) {
        printf("ping - %d\n", value);
        value++;
        write(pipe1[1], &value, sizeof(value));
        read(pipe2[0], &value, sizeof(value));
        if (value >= 100) {
            exit(0);
        }
    }
}

int main() {
    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pidB = fork();
    if (pidB < 0) {
        perror("fork B");
        exit(1);
    } else if (pidB == 0) {
        functionB();
        exit(0);
    }

    pid_t pidC = fork();
    if (pidC < 0) {
        perror("fork C");
        exit(1);
    } else if (pidC == 0) {
        functionC();
        exit(0);
    }

    // Wait for B to finish
    int status;
    waitpid(pidB, &status, 0);

    // Send signal to C
    if (kill(pidC, SIGUSR1) < 0) {
        perror("kill");
        exit(1);
    }

    exit(0);
}
