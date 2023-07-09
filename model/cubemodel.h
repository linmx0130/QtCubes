/* cubemodel.h
 * Header file of the cude model.
 *  
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */
#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

#include "abstractmodel.h"

class CubeModel: public AbstractModel
{
private:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;
    QOpenGLTexture *m_texture;
    QOpenGLFunctions *f;

public:
    CubeModel(QOpenGLFunctions *f);
    ~CubeModel();

    // bind the OpenGL objects of this model to prepare for rendering
    virtual void bindModel() override;
    // draw the model with the OpenGL and MVP, lighting parameters
    virtual void draw(const QMatrix4x4 &modelMat,
              const QMatrix4x4 &viewMat,
              const QMatrix4x4 &projMat,
              const QVector3D& lightPos) override;
    // release OpenGL objects of this model from OpenGL context
    virtual void releaseModel() override;
};

#endif // CUBEMODEL_H
