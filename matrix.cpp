#include "matrix.h"

void identity(Matrix* matrix) {
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            (*matrix)[i][j] = i == j;
        }
    }
}

void multiply(Matrix* matrix, Matrix* other) {
    Matrix result;  // Create a temporary result matrix
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            result[i][j] = 0;  // Initialize result element to zero
            for (size_t k = 0; k < SIZE; k++) {
                result[i][j] += (*matrix)[i][k] * (*other)[k][j];
            }
        }
    }
    memcpy(matrix, &result, sizeof(result));
}

void multiplyVector(Matrix* matrix, Vector* vector) {
    double result[SIZE] = {0};

    for (size_t i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (size_t j = 0; j < SIZE; j++) {
            result[i] += (*matrix)[i][j] * ((double*)vector)[j];
        }
    }

    vector->x = result[0];
    vector->y = result[1];
    vector->z = result[2];
}

void translate(Matrix* matrix, Vector* translation) {
    (*matrix)[0][SIZE-1] += translation->x;
    (*matrix)[1][SIZE-1] += translation->y;
    (*matrix)[2][SIZE-1] += translation->z;
}

void rotate(Matrix* matrix, Vector* rotator) {
    Matrix X = {
        {1, 0, 0, 0},
        {0, cos(rotator->x), -sin(rotator->x), 0},
        {0, sin(rotator->x), cos(rotator->x), 0},
        {0, 0, 0, 1},
    };
    Matrix Y = {
        {cos(rotator->y), 0, sin(rotator->y), 0},
        {0, 1, 0, 0},
        {-sin(rotator->y), 0, cos(rotator->y), 0},
        {0, 0, 0, 1},
    };
    Matrix Z = {
        {cos(rotator->z), -sin(rotator->z),  0, 0},
        {sin(rotator->z), cos(rotator->z), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    multiply(matrix, &X);
    multiply(matrix, &Y);
    multiply(matrix, &Z);
}

void scale(Matrix* matrix, Vector* factor) {
    Matrix k = {
        {factor->x, 0, 0, 0},
        {0, factor->y, 0, 0},
        {0, 0, factor->z, 0},
        {0, 0, 0, factor->w},
    };
    multiply(matrix, &k);
}
