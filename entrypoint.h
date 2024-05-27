#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "appcontext.h"

enum Operation {
    Init,
    LoadFile,
    Calculate,
    SetTranslation,
    SetRotation,
    SetScale,
    SetNormilize,
};

struct AppParams {
    const char* filename;
    struct {
        double x;
        double y;
        double z;
    } translation;
    struct {
        double x;
        double y;
        double z;
    } rotation;
    struct {
        double x;
        double y;
        double z;
    } scale;
    struct {
        NormilizeValue normilize;
        double min;
        double max;
    } range;
};

void doOperation(Operation operation, struct AppContext* context, struct AppParams* params);

#endif // ENTRYPOINT_H
