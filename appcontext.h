#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "error.h"
#include "list.h"
#include "matrix.h"

struct Point {
    double x;
    double y;
};

enum NormilizeValue {
    Real,
    Normilize,
};

struct AppContext {
    Error error;
    struct List rows;
    struct List points;
    Vector translation;
    Vector scale;
    Vector rotation;
    struct {
        NormilizeValue normilize;
        double min;
        double max;
    } range;
};

#endif // APPCONTEXT_H
