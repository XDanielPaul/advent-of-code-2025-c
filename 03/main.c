#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *load_input(){
    char *input = NULL;
    size_t len = 0;
    __ssize_t read;

    read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        return NULL;
    }
    return input;
}

int get_jolts(char *line){
    int max_jolts = 0;
    int best_first_digit = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        // ASCII "arithmetic"
        if (line[i] < '0' || line[i] > '9')
            continue;

        int digit = line[i] - '0';
        if (best_first_digit != -1) {
            // Create a number with the best previous first digit
            int jolts = best_first_digit * 10 + digit;

            if (jolts > max_jolts)
                max_jolts = jolts;

        }
        // Update best_first_digit if current digit is greater
        if (digit > best_first_digit)
            best_first_digit = digit;
    }

    return max_jolts;
}

int main() {
    char *input = NULL;
    int total_jolts = 0;
    while ((input = load_input()) != NULL) {
        total_jolts += get_jolts(input);
        free(input);
    }
    printf("Total Jolts: %d\n", total_jolts);
    return EXIT_SUCCESS;
}
