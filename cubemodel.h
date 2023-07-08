#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class CubeModel
{
private:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLTexture *m_texture;
    QOpenGLFunctions *f;

public:
    CubeModel(QOpenGLFunctions *f);

    // bind the OpenGL objects of this model to prepare for rendering
    void bindModel();
    // draw the model with the OpenGL and MVP, lighting parameters
    void draw(const QMatrix4x4 &modelMat,
              const QMatrix4x4 &viewMat,
              const QMatrix4x4 &projMat,
              const QVector3D& lightPos);
    // release OpenGL objects of this model from OpenGL context
    void releaseModel();
};

#endif // CUBEMODEL_H
