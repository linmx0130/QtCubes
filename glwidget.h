/*
 * glwidget.h
 * Header file of the canvas widget.
 * 
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

#include "model/cubemodel.h"
#include "model/spheremodel.h"

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
    SphereModel *sphere;
    QElapsedTimer *timer;
    QVector3D camera_pos;
    QVector3D camera_direction;
    float aspectRatio;
    bool _isRotating;
    qint64 lastTimerValue;
    float degree;
};

#endif // GLWIDGET_H
