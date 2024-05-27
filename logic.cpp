#include "logic.h"

void init(struct AppContext* context) {
    context->error = Error::None;
    context->rows = listInit(sizeof(struct List));
    context->points = listInit(sizeof(struct List));
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
        fclose(file);
    }
}

void calculatePoints(AppContext* context) {
    freePoints(context);

    Matrix matrix;
    identity(&matrix);
    Vector  rotator = {3.1415 / 6, 0, -3.1415 / 6, 1};
    rotate(&matrix, &rotator);
    Vector translation = {10, 0, 40, 1};
    translate(&matrix, &translation);
    Vector  factor = {16, 16, 16, 1};
    scale(&matrix, &factor);
    int y = 0;
    struct Node* dataRow = context->rows.first;
    while (dataRow) {
        int x = 0;
        struct List pointsRow = listInit(sizeof(struct Point));
        struct Node* dataCell = ((struct List*) dataRow->ptr)->first;
        while (dataCell) {
            struct Vector vector = {(double) x, (double) y, (double)(*(int*)dataCell->ptr), 1};
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
