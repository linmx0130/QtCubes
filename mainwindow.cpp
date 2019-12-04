#include "mainwindow.h"
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), layout(nullptr)
{
    layout = new QHBoxLayout();
    this->glWidget = new GLWidget(this);
    layout->addWidget(glWidget);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

