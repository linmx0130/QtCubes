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
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLTexture *m_texture;
    QElapsedTimer *timer;
    float aspectRatio;
};

#endif // GLWIDGET_H