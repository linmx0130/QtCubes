#include "spheremodel.h"
#include <vector>
#include <utility>
#include <cmath>

const uint32_t STACK_COUNT = 40;
const uint32_t SECTION_COUNT = 40;
const GLfloat _PI = 3.1415926f;

std::vector<std::vector<std::pair<GLfloat, GLfloat>>> SphereModel::generateSphereAngelCoordinates(uint32_t stackCount, uint32_t sectionCount) {
    std::vector<std::vector<std::pair<GLfloat, GLfloat>>> value;
    for (uint32_t i = 0; i <= stackCount; ++i) {
        std::vector<std::pair<GLfloat, GLfloat>> row(sectionCount);
        GLfloat phi = _PI / 2.0f - _PI * i / stackCount;
        for (uint32_t j=0; j <sectionCount; ++j) {
            GLfloat theta = _PI * 2.0f * j / sectionCount;
            row[j] = std::make_pair(phi, theta);
        }
        value.push_back(row);
    }
    return value;
}

SphereModel::SphereModel(QOpenGLFunctions *f): f(f)
{
    std::vector<std::vector<std::pair<GLfloat, GLfloat>>> coordinates = generateSphereAngelCoordinates(STACK_COUNT, SECTION_COUNT);
    initVertices(coordinates);
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/sphereVertexShader.vsh");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/sphereFragmentShader.fsh");
    if (m_shader->link()) {
        qDebug("Sphere shaders link success.");
    } else {
        qDebug("Sphere shaders link failed!");
    }

    // build VAO
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();
    // build VBO
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    // store vertex to VBO
    m_vbo->allocate(this->vertices.data(), this->vertices.size() * sizeof(GLfloat));
    // apply data to vertex shader
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    // release objects
    m_vbo->release();
    m_vao->release();
}

void SphereModel::bindModel() {
    m_vao->bind();
    m_shader->bind();
}

void SphereModel::releaseModel() {
    m_shader->release();
    m_vao->release();
}

void SphereModel::draw(
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
    uint32_t count = this->vertices.size() / 3;
    f->glDrawArrays(GL_TRIANGLES, 0, count);
}


std::vector<GLfloat> SphereModel::getCartesianCoordFromAngelCoord(std::pair<GLfloat, GLfloat> angel) {
    GLfloat phi = angel.first;
    GLfloat theta = angel.second;
    GLfloat cosPhi = cosf(phi);
    GLfloat sinPhi = sinf(phi);
    GLfloat cosTheta = cosf(theta);
    GLfloat sinTheta = sinf(theta);
    return std::vector<GLfloat>{cosPhi * cosTheta, cosPhi * sinTheta, sinPhi};
}

void SphereModel::initVertices(const std::vector<std::vector<std::pair<GLfloat, GLfloat>>> &coords){
    const uint32_t N = coords.size();
    const uint32_t M = coords[0].size();
    vertices.clear();
    vertices.reserve(18 * N * M);
    for (uint32_t i = 0; i < N - 1; ++i) {
        for (uint32_t j = 0;j <M-1; ++j) {
            auto cij = getCartesianCoordFromAngelCoord(coords[i][j]);
            auto ci1j = getCartesianCoordFromAngelCoord(coords[i+1][j]);
            auto cij1 = getCartesianCoordFromAngelCoord(coords[i][j+1]);
            auto ci1j1 = getCartesianCoordFromAngelCoord(coords[i+1][j+1]);
            addSquareToVertices(cij, ci1j, cij1, ci1j1);
        }

        auto cij = getCartesianCoordFromAngelCoord(coords[i][M-1]);
        auto ci1j = getCartesianCoordFromAngelCoord(coords[i+1][M-1]);
        auto cij1 = getCartesianCoordFromAngelCoord(coords[i][0]);
        auto ci1j1 = getCartesianCoordFromAngelCoord(coords[i+1][0]);
        addSquareToVertices(cij, ci1j, cij1, ci1j1);
    }
}
void SphereModel::addVertexToVertices(const std::vector<GLfloat>& v) {
    vertices.push_back(v[0]);
    vertices.push_back(v[1]);
    vertices.push_back(v[2]);
}

void SphereModel::addSquareToVertices(
    const std::vector<GLfloat>& tl,
    const std::vector<GLfloat>& dl,
    const std::vector<GLfloat>& tr,
    const std::vector<GLfloat>& dr
    ) {
    // left-up triangle
    addVertexToVertices(tl);
    addVertexToVertices(dl);
    addVertexToVertices(tr);
    // right-down triangle
    addVertexToVertices(tr);
    addVertexToVertices(dl);
    addVertexToVertices(dr);
}
