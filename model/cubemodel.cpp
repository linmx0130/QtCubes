/* cubemodel.cpp
 * Implementation of the cude model.
 *  
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "cubemodel.h"

static const GLfloat _CUBE_MODEL_VERTEX_DATA[] = {
    //face 1 : z= 0.5f
    0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //face 2: y=0.5f
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    //face 3: x = 0.5f
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //face 4: z=-0.5
    0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    //face 5: y=-0.5f
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    //face 6: x=-0.5f
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
};

CubeModel::CubeModel(QOpenGLFunctions* f): AbstractModel(), f(f)
{
    // load shader
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cubeVertexShader.vsh");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cubeFragmentShader.fsh");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    // load texture
    m_texture = new QOpenGLTexture(QImage(":/imgs/container.jpg"));

    // build VAO
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();
    // build VBO
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();

    // store vertex to VBO
    m_vbo->allocate(_CUBE_MODEL_VERTEX_DATA, 6 * 6 * 8 * sizeof(GLfloat));

    // apply data to vertex shader
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    // release objects
    m_vbo->release();
    m_vao->release();
}

void CubeModel::bindModel() {
    m_vao->bind();
    m_shader->bind();
    m_texture->bind();
}

void CubeModel::releaseModel() {
    m_texture->release();
    m_shader->release();
    m_vao->release();
}

void CubeModel::draw(
    const QMatrix4x4 &modelMat,
    const QMatrix4x4 &viewMat,
    const QMatrix4x4 &projMat,
    const QVector3D &lightPos
) {
    m_shader->setUniformValue(m_shader->uniformLocation("projectMat"), projMat);
    m_shader->setUniformValue(m_shader->uniformLocation("viewMat"), viewMat);
    m_shader->setUniformValue(m_shader->uniformLocation("modelMat"), modelMat);
    m_shader->setUniformValue(m_shader->uniformLocation("lightPos"), lightPos);
    // draw object
    f->glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
}

CubeModel::~CubeModel() {
    delete m_vao;
    delete m_vbo;
    delete m_shader;
    delete m_texture;
}
