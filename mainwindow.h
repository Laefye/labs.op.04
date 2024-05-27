#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "entrypoint.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graph* graph;

    void loadFile();
    void redrawGraph();

    AppContext context;
private slots:
    void setTranslation();
    void setRotation();
    void setScale();
    void setNormilize();
};
#endif // MAINWINDOW_H
