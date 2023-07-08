#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

#include "cubemodel.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *partent);
    ~GLWidget();
    QVector3D getCameraPos() {
        return camera_pos;
    }
    QVector3D getCameraDirection() {
        return camera_direction;
    }

    bool isRotating(){
        return _isRotating;
    }
signals:
    void stateChanged();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    CubeModel *cube;
    QElapsedTimer *timer;
    QVector3D camera_pos;
    QVector3D camera_direction;
    float aspectRatio;
    bool _isRotating;
    qint64 lastTimerValue;
    float degree;
};

#endif // GLWIDGET_H
