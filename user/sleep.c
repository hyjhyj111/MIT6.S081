/*************************************************************************
	> File Name: sleep.c
	> Author: 
	> Mail: 
	> Created Time: Thu 10 Jul 2025 07:41:19 PM CST
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "%s must have a argument\n", argv[0]);
        exit(1);
    }
    int x = 0;
    for (int i = 0; argv[1][i];i ++) {
        char ch = argv[1][i];
        if (!(ch >= '0' && ch <= '9')) {
            fprintf(2, "invalid argument, please use integer\n");
        }
        x = x * 10 + ch - '0';
    }
    sleep(x);
    exit(0);
}
