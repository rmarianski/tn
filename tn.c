#include <unistd.h>

int main(int argc, char *argv[]) {

    int has_last_char = 0;
    char last_char = 0;
    char buffer[4096];
    size_t n_rd, n_wr;
    char char_to_write;
    int remove_newline = 0;

    if (argc == 2) {
        char *option = argv[1];
        if (option[0] == '-' && option[1] == 'n') {
            remove_newline = 1;
        }
    }

    for (;;) {
        n_rd = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (n_rd == 0) {
            break;
        }
        if (remove_newline && has_last_char) {
            n_wr = write(STDOUT_FILENO, &last_char, 1);
            if (n_wr != 1) {
                return 1;
            }
        }
        has_last_char = 1;
        last_char = buffer[n_rd - 1];
        if (remove_newline) {
            if (n_rd > 1) {
                n_wr = write(STDOUT_FILENO, buffer, n_rd - 1);
                if (n_wr != n_rd - 1) {
                    return 2;
                }
            }
        } else {
            n_wr = write(STDOUT_FILENO, buffer, n_rd);
            if (n_wr != n_rd) {
                return 3;
            }
        }
    }

    if (has_last_char && last_char != '\n') {
        char_to_write = remove_newline ? last_char : '\n';
        n_wr = write(STDOUT_FILENO, &char_to_write, 1);
        if (n_wr != 1) {
            return 4;
        }
    }

    return 0;
}
