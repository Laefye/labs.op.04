#include "logic.h"

void init(struct AppContext* context) {
    context->error = Error::None;
    context->rows = listInit(sizeof(struct List));
    context->points = listInit(sizeof(struct List));
    context->translation = {0, 0, 0, 1};
    context->scale = {1, 1, 1, 1};
    context->rotation = {0, 0, 0, 1};
    context->range = {
        .normilize = NormilizeValue::Real,
        .min = 0,
        .max = 1,
    };
}

int readRow(char* inputLine, struct List* row) {
    char* line = inputLine;
    char number[MAX_STRING];
    int state = TRUE;
    for (; line < inputLine + strlen(inputLine);) {
        char* endNumber = strpbrk(line, ",");
        if (endNumber == NULL) {
            strcpy(number, line);
            line += strlen(line);
        } else {
            strncpy(number, line, endNumber - line);
            number[endNumber - line] = 0;
            line = endNumber + 1;
        }
        int output = 0;
        if (sscanf(number, "%d", &output) == 1) {
            listPush(row, &output);
        } else {
            state = FALSE;
            break;
        }
    }
    return state;
}

int checkRowsLength(AppContext* context, size_t count) {
    int result = TRUE;
    if (context->rows.count > 0 && ((struct List*)context->rows.first->ptr)->count != count) {
        result = FALSE;
    }
    return result;
}

Error readRows(AppContext* context, FILE* file) {
    Error error = Error::None;
    char line[MAX_STRING];
    while (!feof(file)) {
        struct List row = listInit(sizeof(int));
        if (fgets(line, MAX_STRING, file) && readRow(line, &row) == TRUE && checkRowsLength(context, row.count)) {
            listPush(&context->rows, &row);
        } else {
            listFree(&row);
        }
    }
    return error;
}

void freeRows(AppContext* context) {
    if (context->rows.count) {
        struct Node* node = context->rows.first;
        while (node) {
            listFree((struct List*)node->ptr);
            node = node->next;
        }
        listFree(&context->rows);
        context->rows = listInit(sizeof(struct List));
    }
}

void freePoints(AppContext* context) {
    if (context->points.count) {
        struct Node* node = context->points.first;
        while (node) {
            listFree((struct List*)node->ptr);
            node = node->next;
        }
        listFree(&context->points);
        context->points = listInit(sizeof(struct List));
    }
}

void loadFile(AppContext* context, const char* filename) {
    context->error = Error::None;
    FILE* file = fopen(filename, "r");
    if (!file) {
        context->error = Error::FileIsNotOpened;
    } else {
        freeRows(context);
        readRows(context, file);
        if (!context->rows.count) {
            context->error = Error::IncorrectFormat;
        }
        fclose(file);
    }
}

void getMetrics(AppContext* context, double* min, double* max)  {
    struct Node* dataRow = context->rows.first;
    if (!dataRow) {
        return;
    }
    *min = *(int*)(((List*)dataRow->ptr)->first->ptr);
    *max = *(int*)(((List*)dataRow->ptr)->first->ptr);
    while (dataRow) {
        struct Node* dataCell = ((struct List*) dataRow->ptr)->first;
        while (dataCell) {
            int current = *((int*)dataCell->ptr);
            if (current < *min) {
                *min = current;
            }
            if (current > *max) {
                *max = current;
            }
            dataCell = dataCell->next;
        }
        dataRow = dataRow->next;
    }
}

double getValue(AppContext* context, struct Node* dataCell) {
    double minValue = 0;
    double maxValue = 0;
    getMetrics(context, &minValue, &maxValue);
    double value = (double)(*(int*)dataCell->ptr);
    if (context->range.normilize && (maxValue - minValue) != 0) {
        value = context->range.min + (value-minValue)/(maxValue-minValue)*(context->range.max-context->range.min);
    }
    return value;
}

void calculatePoints(AppContext* context) {
    freePoints(context);
    Matrix matrix;
    identity(&matrix);
    rotate(&matrix, &context->rotation);
    translate(&matrix, &context->translation);
    scale(&matrix, &context->scale);
    int y = 0;
    struct Node* dataRow = context->rows.first;
    while (dataRow) {
        int x = 0;
        struct List pointsRow = listInit(sizeof(struct Point));
        struct Node* dataCell = ((struct List*) dataRow->ptr)->first;
        while (dataCell) {
            struct Vector vector = {(double) x, (double) y, getValue(context, dataCell), 1};
            multiplyVector(&matrix, &vector);
            struct Point point = {vector.x, vector.z};
            listPush(&pointsRow, &point);
            dataCell = dataCell->next;
            x++;
        }
        listPush(&context->points, &pointsRow);
        dataRow = dataRow->next;
        y++;
    }
}

void setTranslation(AppContext* context, double x, double y, double z) {
    context->translation = {x, y, z, 1};
}
void setRotation(AppContext* context, double x, double y, double z) {
    context->rotation = {x * DEG_TO_RAD, y * DEG_TO_RAD, z * DEG_TO_RAD, 1};
}
void setScale(AppContext* context, double x, double y, double z) {
    context->scale = {x, y, z, 1};
}

void setNormilize(AppContext* context, double min, double max, NormilizeValue normilize) {
    context->range.min = min;
    context->range.max = max;
    context->range.normilize = normilize;
}
