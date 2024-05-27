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
    case Operation::SetTranslation:
        setTranslation(context, params->translation.x, params->translation.y, params->translation.z);
        break;
    case Operation::SetRotation:
        setRotation(context, params->rotation.x, params->rotation.y, params->rotation.z);
        break;
    case Operation::SetScale:
        setScale(context, params->scale.x, params->scale.y, params->scale.z);
        break;
    case Operation::SetNormilize:
        setNormilize(context, params->range.min, params->range.max, params->range.normilize);
        break;
    }
}
