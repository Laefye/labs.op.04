#ifndef LOGIC_H
#define LOGIC_H
#include "appcontext.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 100
#define TRUE 1
#define FALSE 0
#define DEG_TO_RAD (1.0/180.0*3.1415)

void init(AppContext* context);
void loadFile(AppContext* context, const char* filename);
void calculatePoints(AppContext* context);
void setTranslation(AppContext* context, double x, double y, double z);
void setRotation(AppContext* context, double x, double y, double z);
void setScale(AppContext* context, double x, double y, double z);
void setNormilize(AppContext* context, double min, double max, NormilizeValue normilize);

#endif // LOGIC_H
