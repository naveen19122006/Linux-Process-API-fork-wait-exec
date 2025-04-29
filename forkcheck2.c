#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int status;
    pid_t pid;

    printf("Running ps with execl (without path)\n");
    pid = fork();
    if (pid == 0) {
        execl("ps", "ps", "ax", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            puts("Child did not exit successfully");
    }

    printf("Running ps with execl (with /bin/ps)\n");
    pid = fork();
    if (pid == 0) {
        execl("/bin/ps", "ps", "ax", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            puts("Child did not exit successfully");
    }

    printf("Done.\n");
    exit(0);
}

