#include <stdio.h>

int main() {
    char buffer[4096];
    size_t n_rd, n_wr = 0;
    int rc = 0;
    char *last_char;

    for (;;) {
        last_char = 0;
        n_rd = fread(buffer, 1, sizeof(buffer), stdin);
        if (n_rd > 0) {
            last_char = buffer + n_rd - 1;
            n_wr = fwrite(buffer, 1, n_rd, stdout);
            if (n_wr != n_rd) {
                perror("fwrite");
                rc = 2;
            }
        }
        if (feof(stdin)) {
            break;
        } else if (ferror(stdin)) {
            perror("fread");
            break;
        }
    }
    if (last_char && *last_char != '\n') {
        int written = fputc('\n', stdout);
        if (written == EOF) {
            perror("fputc");
            rc = 3;
        }
    }
    return rc;
}
