#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, struct AppContext* context, struct AppParams* params) {
    switch (operation) {
    case Operation::Init:
        init(context);
        break;
    case Operation::LoadFile:
        loadFile(context, params->filename);
        break;
    case Operation::Calculate:
        calculatePoints(context);
        break;
    }
}
