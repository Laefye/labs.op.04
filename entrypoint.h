#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "appcontext.h"

enum Operation {
    Init,
    LoadFile,
    Calculate,
};

struct AppParams {
    const char* filename;
};

void doOperation(Operation operation, struct AppContext* context, struct AppParams* params);

#endif // ENTRYPOINT_H
