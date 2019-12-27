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
