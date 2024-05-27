#ifndef GRAPH_H
#define GRAPH_H
#include <QWidget>
#include <QPainter>
#include "appcontext.h"

class Graph : public QWidget
{
private:
    AppContext* context;
public:
    Graph(AppContext* context, QWidget* parent = 0);

    void paintEvent(QPaintEvent *event) override;

    void drawHorisontal(QPainter& painter);
    void drawVertical(QPainter& painter);
};

#endif // GRAPH_H
