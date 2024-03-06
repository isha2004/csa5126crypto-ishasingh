#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int isCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

int main() {
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    // Check if 'a' and 'b' are coprime with 26
    if (isCoprime(a, 26)) {
        printf("The values of a and b are valid for the affine Caesar cipher.\n");
    } else {
        printf("The values of a and b are not valid for the affine Caesar cipher.\n");
    }

    return 0;
}

