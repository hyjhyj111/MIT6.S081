/*************************************************************************
	> File Name: pingpong.c
	> Author: 
	> Mail: 
	> Created Time: Thu 10 Jul 2025 10:30:15 PM CST
 ************************************************************************/

#include <kernel/types.h>
#include <user/user.h>

int main() {
    int p1[2], p2[2];
    pipe(p1), pipe(p2);

    char byte = 'x';
    if (fork() == 0) {
        // son
        close(p1[1]);
        close(p2[0]);

        read(p1[0], &byte, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], &byte, 1);

        close(p1[0]);
        close(p2[1]);
    } else {
        // father
        close(p1[0]);
        close(p2[1]);

        write(p1[1], &byte, 1);
        read(p2[0], &byte, 1);
        printf("%d: received pong\n", getpid());

        close(p1[1]);
        close(p2[0]);
    }
    exit(0);
}
