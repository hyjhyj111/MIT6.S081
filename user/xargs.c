/*************************************************************************
	> File Name: xargs.c
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Jul 2025 07:28:35 PM CST
 ************************************************************************/

#include "kernel/types.h"
#include "user/user.h"

#define MAX_ARGS 32

int main(int argc, char **argv) {
    char *args[MAX_ARGS] = {};
    for (int i = 1;i < argc;i ++) {
        args[i - 1] = argv[i];
    }
    char ch;
    char buff[64] = {};
    char *p = buff;
    int cnt = argc - 1;
    while (read(0, &ch, sizeof (char)) > 0) {
        if (ch == '\n') {
            *p = '\0';
            args[cnt] = malloc(p - buff + 1);  // +1 for null terminator
            strcpy(args[cnt], buff);
            cnt++;
            p = buff;
        } else {
            *p ++ = ch;
            if (p - buff > 64) {
                fprintf(2, "args too long\n");
                exit(1);
            }
        }
    }
    if (fork() == 0) {
        exec(argv[1], args);
    } else {
        wait(0);
    }
    exit(0);
}
