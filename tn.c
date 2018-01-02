#include <stdio.h>

int main(int argc, char *argv[]) {

    int has_last_char = 0;
    char last_char = 0;
    char buffer[4096];
    size_t n_rd, n_wr;
    int char_written;
    char char_to_write;
    int remove_newline = 0;

    if (argc == 2) {
        char *option = argv[1];
        if (option[0] == '-' && option[1] == 'n') {
            remove_newline = 1;
        }
    }

    for (;;) {
        n_rd = fread(buffer, 1, sizeof(buffer), stdin);
        if (n_rd > 0) {
            if (remove_newline && has_last_char) {
                char_written = fputc(last_char, stdout);
                if (char_written == EOF) {
                    perror("fputc");
                    return 1;
                }
            }
            has_last_char = 1;
            last_char = buffer[n_rd - 1];
            if (remove_newline) {
                if (n_rd > 1) {
                    n_wr = fwrite(buffer, 1, n_rd - 1, stdout);
                    if (n_wr != n_rd - 1) {
                        perror("fwrite");
                        return 2;
                    }
                }
            } else {
                n_wr = fwrite(buffer, 1, n_rd, stdout);
                if (n_wr != n_rd) {
                    perror("fwrite");
                    return 3;
                }
            }
        }
        if (feof(stdin)) {
            break;
        } else if (ferror(stdin)) {
            perror("fread");
            break;
        }
    }

    if (has_last_char && last_char != '\n') {
        char_to_write = remove_newline ? last_char : '\n';
        char_written = fputc(char_to_write, stdout);
        if (char_written == EOF) {
            perror("fputc");
            return 4;
        }
    }

    return 0;
}
