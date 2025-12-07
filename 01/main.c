#include <stdio.h>
#include <stdlib.h>

char get_rotation(char* rotation) {
    return rotation[0];
}

int get_rotation_value(char* rotation) {
    return atol(rotation + 1);
}

int count_zero_clicks(int dial, char direction, int distance) {
    int clicks = 0;
    for (int i = 0; i < distance; i++) {
        dial = direction == 'R' ? (dial + 1) % 100 : (dial - 1 + 100) % 100;
        if (dial == 0) clicks++;
    }
    return clicks;
}

int main() {
    // Suboptimal I might not know the size of the rotation string
    char rotation[6];
    int dial = 50;
    int zero_clicks = 0;

    while (fgets(rotation, sizeof(rotation), stdin)) {
        char direction = get_rotation(rotation);
        int distance = get_rotation_value(rotation);

        // Count how many clicks of zero have occurred
        zero_clicks += count_zero_clicks(dial, direction, distance);
        // Actually rotate the dial
        dial = direction == 'R' ? (dial + distance) % 100 : (dial - distance + 100) % 100;
    }

    printf("Zero Clicks: %d\n", zero_clicks);

    return EXIT_SUCCESS;
}
