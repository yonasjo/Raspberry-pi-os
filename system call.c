#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/stat.h>

#define PIVOT_ROOT 155

int main(int c, char **v) {
    struct stat s;
    if (c != 3 || stat(v[1], &s) || !S_ISDIR(s.st_mode) || stat(v[2], &s) || !S_ISDIR(s.st_mode)) {
        return fprintf(stderr, "Usage: %s new_root put_old\n", v[0]), 1;
    }
    if (syscall(PIVOT_ROOT, v[1], v[2]) || chdir("/")) {
        perror("pivot_root");
        return 1;
    }
    printf("pivoted to %s, old root -> %s\n", v[1], v[2]);
    return 0;
}
