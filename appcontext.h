#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "error.h"
#include "list.h"
#include "matrix.h"

struct Point {
    double x;
    double y;
};

struct AppContext {
    Error error;
    struct List rows;
    struct List points;
    Vector translation;
    Vector scale;
    Vector rotation;
};

#endif // APPCONTEXT_H
