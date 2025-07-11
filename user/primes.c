/*************************************************************************
	> File Name: primes.c
	> Author:
	> Mail:
	> Created Time: Thu 10 Jul 2025 11:26:57 PM CST
 ************************************************************************/

#include "kernel/types.h"
#include "user/user.h"

void primeproc(int read_fd) {
    int primer;
    if (read(read_fd, &primer, sizeof (int)) == 0) {
        close(read_fd);
        exit(0);
    }
    printf("prime %d\n", primer);

    int new_pipe[2];
    pipe(new_pipe);

    if (fork() == 0) {
        close(read_fd);
        close(new_pipe[1]);
        primeproc(new_pipe[0]);
        exit(0);
    } else {
        close(new_pipe[0]);
        int x;
        while (read(read_fd, &x, sizeof (int))) {
            if (x % primer == 0) continue;
            write(new_pipe[1], &x, sizeof (int));
        }
        close(read_fd);
        close(new_pipe[1]);
        wait(0);
        exit(0);
    }
}
int main() {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        primeproc(p[0]);
    } else {
        close(p[0]);
        for (int i = 2;i <= 35;i ++) {
            write(p[1], &i, sizeof (int));
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}
