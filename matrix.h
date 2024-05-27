#ifndef MATRIX_H
#define MATRIX_H
#include <string.h>
#include <math.h>
#define SIZE 4

typedef double Matrix[SIZE][SIZE];

struct Vector {
    double x;
    double y;
    double z;
    double w;
};

void identity(Matrix* matrix);
void translate(Matrix* matrix, Vector* translation);
void rotate(Matrix* matrix, Vector* rotator);
void scale(Matrix* matrix, Vector* factor);
void multiply(Matrix* matrix, Matrix* other);
void multiplyVector(Matrix* matrix, Vector* vector);

#endif // MATRIX_H
