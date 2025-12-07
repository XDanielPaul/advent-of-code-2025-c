#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

char *load_input(){
    char *input = NULL;
    size_t len = 0;
    __ssize_t read;

    read = getline(&input, &len, stdin);
    if (read == -1) {
        perror("getline");
        exit(EXIT_FAILURE);
    }
    return input;
}

int count_digits(uint64_t num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

bool is_id_invalid_part_two(uint64_t id) {
    int digits = count_digits(id);

    for (int k = 1; k <= digits/2; k++) {
        // k = number of digits in one repeated sequence
        // Try lengths that divide evenly into the total number of digits
        // e.g. digits = 6 -> possible k values are 1, 2, 3
        // 111111, 121212, 123123
        if (digits % k != 0) continue;

        uint64_t divisor = 1;
        for (int i = 0; i < k; i++) divisor *= 10;

        uint64_t chunk = id % divisor;
        uint64_t temp = id / divisor;
        bool valid = true;

        // Take temp % divisor -> Next chunk from the right -> Compare with chunk
        // If ANY chunks differ -> the k is invalid
        // If ALL chunks equal -> the ID is invalid
        //
        /* Example: id = 1212121212, k = 2, divisor = 100
        *
        * Step | temp      | temp % 100 | compare
        * -----|-----------|------------|-----------
        * 1    | 12121212  | 12         | 12 == 12 ✔
        * 2    | 121212    | 12         | 12 == 12 ✔
        * 3    | 1212      | 12         | 12 == 12 ✔
        * 4    | 12        | 12         | 12 == 12 ✔
        * done | 0         | —          | all chunks equal → invalid
        */
        while (temp > 0) {
            if (temp % divisor != chunk) {
                valid = false;
                break;
            }
            temp /= divisor;
        }

        if (valid) return true;
    }
    return false;
}

bool is_id_invalid_part_one(uint64_t id){
    int digits = count_digits(id);

    // Cannot split odd numbers evenly
    if (digits % 2 != 0) return false;

    uint64_t divisor = 1;
    for (int i = 0; i < digits / 2; i++)
        divisor *= 10;

    // Check if the left and right halves are equal
    return id / divisor == id % divisor;
}

int main() {
    char *input = load_input();

    uint64_t sum = 0;

    char *token = strtok(input, ",");
    while (token != NULL) {
        uint64_t start, end;
        if (sscanf(token, "%lu-%lu", &start, &end) == 2) {
            for (uint64_t i = start; i <= end; i++)
                if (is_id_invalid_part_two(i)) {
                    sum += i;
                }
        }
        token = strtok(NULL, ",");
    }

    printf("%lu\n", sum);

    free(input);
    return EXIT_SUCCESS;
}
