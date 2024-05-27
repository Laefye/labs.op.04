#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadFile, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->translationX, SIGNAL(valueChanged(double)), SLOT(setTranslation()));
    connect(ui->translationY, SIGNAL(valueChanged(double)), SLOT(setTranslation()));
    connect(ui->translationZ, SIGNAL(valueChanged(double)), SLOT(setTranslation()));
    connect(ui->rotationX, SIGNAL(valueChanged(double)), SLOT(setRotation()));
    connect(ui->rotationY, SIGNAL(valueChanged(double)), SLOT(setRotation()));
    connect(ui->rotationZ, SIGNAL(valueChanged(double)), SLOT(setRotation()));
    connect(ui->scaleX, SIGNAL(valueChanged(double)), SLOT(setScale()));
    connect(ui->scaleY, SIGNAL(valueChanged(double)), SLOT(setScale()));
    connect(ui->scaleZ, SIGNAL(valueChanged(double)), SLOT(setScale()));
    connect(ui->normalizeValue, SIGNAL(stateChanged(int)), SLOT(setNormilize()));
    connect(ui->minValue, SIGNAL(valueChanged(double)), SLOT(setNormilize()));
    connect(ui->maxValue, SIGNAL(valueChanged(double)), SLOT(setNormilize()));

    doOperation(Operation::Init, &context, 0);

    this->graph = new Graph(&context, this->centralWidget());
    QGridLayout* layout = (QGridLayout*) this->centralWidget()->layout();
    layout->addWidget(this->graph, 1, 0, 2, 1);
}

MainWindow::~MainWindow()
{
    delete this->graph;
    delete ui;
}

QString getErrorString(Error error) {
    QString err;
    switch (error) {
    case Error::FileIsNotOpened:
        err = "File is not opened";
        break;
    case Error::IncorrectFormat:
        err = "Incorrect format";
        break;
    default:
        err = "None";
        break;
    }
    return err;
}

void MainWindow::loadFile() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("CSV (*.csv)");
    if (dialog.exec()) {
        QStringList selectedFiles = dialog.selectedFiles();
        QByteArray filename = selectedFiles.first().toLocal8Bit();
        AppParams params;
        params.filename = filename.data();
        doOperation(Operation::LoadFile, &context, &params);
    }
    if (context.error == Error::None) {
        redrawGraph();
    } else {
        QMessageBox box(this);
        box.setText(getErrorString(context.error));
        box.exec();
    }
}

void MainWindow::setTranslation() {
    AppParams params;
    params.translation = {
        ui->translationX->value(),
        ui->translationY->value(),
        ui->translationZ->value(),
    };
    doOperation(Operation::SetTranslation, &context, &params);
    redrawGraph();
}

void MainWindow::setRotation() {
    AppParams params;
    params.rotation = {
        ui->rotationX->value(),
        ui->rotationY->value(),
        ui->rotationZ->value(),
    };
    doOperation(Operation::SetRotation, &context, &params);
    redrawGraph();
}

void MainWindow::redrawGraph()  {
    doOperation(Operation::Calculate, &context, 0);
    graph->repaint();
}

void MainWindow::setScale() {
    AppParams params;
    params.scale = {
        ui->scaleX->value(),
        ui->scaleY->value(),
        ui->scaleZ->value(),
    };
    doOperation(Operation::SetScale, &context, &params);
    redrawGraph();
}

void MainWindow::setNormilize() {
    AppParams params;
    params.range = {
        .normilize = ui->normalizeValue->isChecked() ? NormilizeValue::Normilize : NormilizeValue::Real,
        .min = ui->minValue->value(),
        .max = ui->maxValue->value(),
    };
    doOperation(Operation::SetNormilize, &context, &params);
    redrawGraph();
}
