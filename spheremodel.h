#ifndef SPHEREMODEL_H
#define SPHEREMODEL_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class SphereModel
{
public:
    SphereModel(QOpenGLFunctions *f);
    // bind the OpenGL objects of this model to prepare for rendering
    void bindModel();
    // draw the model with the OpenGL and MVP, lighting parameters
    void draw(const QMatrix4x4 &modelMat,
              const QMatrix4x4 &viewMat,
              const QMatrix4x4 &projMat,
              const QVector3D& lightPos);
    // release OpenGL objects of this model from OpenGL context
    void releaseModel();

private:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLFunctions *f;

    std::vector<GLfloat> vertices;

    std::vector<std::vector<std::pair<GLfloat, GLfloat>>> generateSphereAngelCoordinates(
        uint32_t stackCount,
        uint32_t sectionCount
    );

    std::vector<GLfloat> getCartesianCoordFromAngelCoord(std::pair<GLfloat, GLfloat> angel);

    void addSquareToVertices(
        const std::vector<GLfloat>& tl,
        const std::vector<GLfloat>& dl,
        const std::vector<GLfloat>& tr,
        const std::vector<GLfloat>& dr
    );

    void addVertexToVertices(const std::vector<GLfloat>& v);

    void initVertices(const std::vector<std::vector<std::pair<GLfloat, GLfloat>>>& coords);
};

#endif // SPHEREMODEL_H
