/*************************************************************************
	> File Name: find.c
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Jul 2025 10:32:51 AM CST
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char *prefix, char *target) {
    char buff[128] = {};
    strcpy(buff, prefix);

    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(prefix, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", prefix);
        return ;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", prefix);
        close(fd);
        return;
    }
    if (st.type != T_DIR) return ;

    char *p = buff + strlen(buff);
    if (*(p - 1) != '/') {
        *p++ = '/';
    }
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) continue;
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = '\0';

        if (stat(buff, &st) < 0) {
            fprintf(2, "find: cannot stat %s\n", buff);
            continue;
        }

        if (st.type == T_FILE) {
            if (strcmp(de.name, target) == 0) {
                printf("%s\n", buff);
            }
        } else if (st.type == T_DIR) {
            find(buff, target); 
        }
    }

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "Usage: %s <path> <target>\n", argv[0]);
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}
