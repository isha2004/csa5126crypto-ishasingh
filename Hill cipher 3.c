#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 10

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to calculate the determinant of a 2x2 matrix
int determinant2x2(int mat[2][2]) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

// Function to calculate the determinant of a 3x3 matrix
int determinant3x3(int mat[3][3]) {
    int det = 0;
    for (int i = 0; i < 3; i++) {
        int term = mat[0][i] * determinant2x2(
                (int[2][2]){{mat[1][(i + 1) % 3], mat[1][(i + 2) % 3]},
                            {mat[2][(i + 1) % 3], mat[2][(i + 2) % 3]}}
        );
        if (i % 2 == 0) {
            det += term;
        } else {
            det -= term;
        }
    }
    return det;
}

// Function to calculate the determinant of a square matrix
int determinant(int size, int mat[MAX_SIZE][MAX_SIZE]) {
    if (size == 2) {
        return determinant2x2((int[2][2]){{mat[0][0], mat[0][1]}, {mat[1][0], mat[1][1]}});
    } else if (size == 3) {
        return determinant3x3((int[3][3]){{mat[0][0], mat[0][1], mat[0][2]},
                                            {mat[1][0], mat[1][1], mat[1][2]},
                                            {mat[2][0], mat[2][1], mat[2][2]}});
    } else {
        // This program handles only 2x2 and 3x3 matrices
        printf("Unsupported matrix size for determinant calculation.\n");
        exit(EXIT_FAILURE);
    }
}

// Function to find the inverse of a 2x2 matrix
void inverse2x2(int mat[2][2], int inverse[2][2]) {
    int det = determinant2x2(mat);
    int detInverse = modInverse(det, 26);
    inverse[0][0] = (mat[1][1] * detInverse) % 26;
    inverse[0][1] = ((-mat[0][1]) * detInverse) % 26;
    inverse[1][0] = ((-mat[1][0]) * detInverse) % 26;
    inverse[1][1] = (mat[0][0] * detInverse) % 26;

    // Ensure positive values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = (inverse[i][j] + 26) % 26;
        }
    }
}

// Function to find the inverse of a 3x3 matrix
void inverse3x3(int mat[3][3], int inverse[3][3]) {
    int det = determinant3x3(mat);
    int detInverse = modInverse(det, 26);

    int cofactors[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            cofactors[j][i] = (sign * determinant2x2(
                    (int[2][2]){{mat[(i + 1) % 3][(j + 1) % 3], mat[(i + 1) % 3][(j + 2) % 3]},
                                {mat[(i + 2) % 3][(j + 1) % 3], mat[(i + 2) % 3][(j + 2) % 3]}}
            )) % 26;

            cofactors[j][i] = (cofactors[j][i] + 26) % 26; // Ensure positive values
            cofactors[j][i] = (cofactors[j][i] * detInverse) % 26;
        }
    }

    // Transpose the cofactor matrix to get the adjugate matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = cofactors[i][j];
        }
    }
}

// Function to find the inverse of a square matrix
void inverse(int size, int mat[MAX_SIZE][MAX_SIZE], int inverse[MAX_SIZE][MAX_SIZE]) {
    if (size == 2) {
        inverse2x2((int[2][2]){{mat[0][0], mat[0][1]}, {mat[1][0], mat[1][1]}}, inverse);
    } else if (size == 3) {
        inverse3x3((int[3][3]){{mat[0][0], mat[0][1], mat[0][2]},
                                {mat[1][0], mat[1][1], mat[1][2]},
                                {mat[2][0], mat[2][1], mat[2][2]}}, inverse);
    } else {
        // This program handles only 2x2 and 3x3 matrices

