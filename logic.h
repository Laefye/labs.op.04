#ifndef LOGIC_H
#define LOGIC_H
#include "appcontext.h"
#include "list.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 100
#define TRUE 1
#define FALSE 0

void init(AppContext* context);
void loadFile(AppContext* context, const char* filename);
void calculatePoints(AppContext* context);

#endif // LOGIC_H
