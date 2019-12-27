#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QElapsedTimer>
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
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);

private:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLTexture *m_texture;
    QElapsedTimer *timer;
    QVector3D camera_pos;
    QVector3D camera_direction;
    float aspectRatio;
    bool _isRotating;
    qint64 lastTimerValue;
    float degree;
};

#endif // GLWIDGET_H
