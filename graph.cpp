#include "graph.h"

Graph::Graph(AppContext* context, QWidget* parent) : QWidget(parent) {
    this->context = context;
}

void Graph::drawHorisontal(QPainter& painter) {
    for (Node* row = this->context->points.first; row; row = row->next) {
        for (Node* pointNode = ((List*)row->ptr)->first->next; pointNode ; pointNode = pointNode->next) {
            Point* point = (Point*)pointNode->ptr;
            Point* leftPoint = (Point*)(pointNode->prev->ptr);
            painter.drawLine(width() / 2 + (int) point->x, height() / 2 - (int) point->y, width() / 2 + (int) leftPoint->x, height() / 2 - (int) leftPoint->y);
        }
    }
}

void Graph::drawVertical(QPainter& painter) {
    int rowIndex = 1;
    for (Node* row = this->context->points.first->next; row; row = row->next) {
        int coloumnIndex = 0;
        for (Node* pointNode = ((List*)row->ptr)->first; pointNode ; pointNode = pointNode->next) {
            Point* point = (Point*)pointNode->ptr;
            Point* bottomPoint = (Point*)listIndex((List*)listIndex(&this->context->points, rowIndex-1)->ptr, coloumnIndex)->ptr;
            painter.drawLine(width() / 2 + (int) point->x, height() / 2 - (int) point->y, width() / 2 + (int) bottomPoint->x, height() / 2 - (int) bottomPoint->y);
            coloumnIndex++;
        }
        rowIndex++;
    }
}

void Graph::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.setPen(Qt::white);
    if (this->context->points.count == 0) {
        return;
    }
    drawHorisontal(painter);
    drawVertical(painter);
}
