#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <QMatrix4x4>

class AbstractModel
{
public:
    // bind the OpenGL objects of this model to prepare for rendering
    virtual void bindModel() = 0;
    // draw the model with the OpenGL and MVP, lighting parameters
    virtual void draw(const QMatrix4x4 &modelMat,
              const QMatrix4x4 &viewMat,
              const QMatrix4x4 &projMat,
              const QVector3D& lightPos) = 0;
    // release OpenGL objects of this model from OpenGL context
    virtual void releaseModel() = 0;
    virtual ~AbstractModel() {}
};

#endif // ABSTRACTMODEL_H
