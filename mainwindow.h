/*
 * mainwindow.h
 * Main window header file.
 * 
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include "glwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void glWidgetStateChange();
private:
    QLayout *layout;
    GLWidget *glWidget;
    QPlainTextEdit *logLabel;

};
#endif // MAINWINDOW_H
