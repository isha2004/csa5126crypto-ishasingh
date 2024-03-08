#include <stdio.h>

long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int size = 25;

    // Calculate the number of possible keys without considering identical encryption results
    long long possibleKeys = factorial(size);

    // Calculate the corrected number of effectively unique keys
    long long uniqueKeys = possibleKeys / (1 << (size - 1));

    printf("Number of possible keys: %lld\n", possibleKeys);
    printf("Number of effectively unique keys: %lld\n", uniqueKeys);

    return 0;
}

