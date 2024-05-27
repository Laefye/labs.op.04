#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadFile, &QPushButton::clicked, this, &MainWindow::loadFile);

    doOperation(Operation::Init, &context, 0);

    this->graph = new Graph(&context, this->centralWidget());
    QGridLayout* layout = (QGridLayout*) this->centralWidget()->layout();
    layout->addWidget(this->graph, 2, 0, 1, 2);
}

MainWindow::~MainWindow()
{
    delete this->graph;
    delete ui;
}

void MainWindow::loadFile() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("CSV (*.csv)");
    if (dialog.exec()) {
        QStringList selectedFiles = dialog.selectedFiles();
        std::string filename = selectedFiles.first().toStdString();
        AppParams params;
        params.filename = filename.c_str();
        doOperation(Operation::LoadFile, &context, &params);
        doOperation(Operation::Calculate, &context, 0);
    }
}
