#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QLayout>
#include <QPushButton>
#include "glwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QLayout *layout;
    GLWidget *glWidget;
};
#endif // MAINWINDOW_H
