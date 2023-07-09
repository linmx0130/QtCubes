/*
 * mainwindow.cpp
 * Main window implementation.
 * 
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "mainwindow.h"
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), layout(nullptr)
{
    layout = new QVBoxLayout();
    glWidget = new GLWidget(this);
    glWidget->setMinimumHeight(100);
    logLabel = new QPlainTextEdit(this);
    layout->addWidget(glWidget);
    layout->addWidget(logLabel);
    logLabel->setReadOnly(true);
    logLabel->setMaximumHeight(75);
    this->setLayout(layout);
    connect(glWidget, SIGNAL(stateChanged()), this, SLOT(glWidgetStateChange()));
    glWidgetStateChange();
}

MainWindow::~MainWindow()
{

}

void MainWindow::glWidgetStateChange()
{
    QVector3D camera_pos = glWidget->getCameraPos();
    QString log;
    log = log.asprintf("Camera Pos = (%f, %f, %f).\n", camera_pos.x(), camera_pos.y(), camera_pos.z());
    QVector3D camera_dir = glWidget->getCameraDirection();
    log.append(log.asprintf("Camera Dir = (%f, %f, %f).\n", camera_dir.x(), camera_dir.y(), camera_dir.z()));
    if (glWidget->isRotating()) {
        log.append("Stop rotating by pressing Space.");
    } else {
        log.append("Resume rotating by pressing Space.");
    }
    logLabel->setPlainText(log);
}

