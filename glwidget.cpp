#include "glwidget.h"
#include <QMatrix4x4>
#include <QKeyEvent>
static const GLfloat VERTEX_DATA[] = {
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
GLWidget::GLWidget(QWidget *nulltpr):
    QOpenGLWidget(nulltpr), m_vbo(nullptr), m_vao(nullptr), m_shader(nullptr), m_texture(nullptr), camera_pos(0.f, 0.f, 3.f), camera_direction(0.f, 0.f, 1.f),
    isRotating(true), lastTimerValue(0)
{
    timer = new QElapsedTimer();
    timer->start();
    setFocusPolicy(Qt::StrongFocus); // enable the widget to receive key press
}

GLWidget::~GLWidget() {

}
void GLWidget::initializeGL()
{
    // set aspect ration
    this->aspectRatio = (float)this->width() / this->height();
    QOpenGLFunctions *f = this->context()->functions();
    f->glEnable(GL_DEPTH_TEST);
    // loading shaders
    if (m_shader) delete m_shader;
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShader.shader");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShader.shader");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    // load texture
    if (m_texture) {
        delete m_texture;
    }
    m_texture = new QOpenGLTexture(QImage(":/imgs/container.jpg"));
    // build VAO
    if (m_vao) delete m_vao;
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();
    // build VBO
    if (m_vbo) delete m_vbo;
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();

    // store vertex to VBO
    m_vbo->allocate(VERTEX_DATA, 6 * 6 * 8 * sizeof(GLfloat));

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

void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w / h;
}

void GLWidget::paintGL()
{
    QVector3D translationPos[] = {QVector3D(0.0f, 2.0f, -6.0f),
                                  QVector3D(-4.0f, 2.0f, -9.0f),
                                  QVector3D(3.0f, -2.0f, -4.5f),
                                  QVector3D(0.0f, 0.0f, -3.0f)};

    float initialDegree[] = {12.0f, 130.0f, 72.0f, 0.0f};
    qint64 newTimeValue = timer->elapsed();
    if (isRotating) {
        degree += 30.0f * (newTimeValue - lastTimerValue) /1000.f;
    }
    lastTimerValue = newTimeValue;
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
    m_vao->bind();
    m_shader->bind();
    m_texture->bind();

    //build MVP matrix
    QMatrix4x4 projMat;
    projMat.perspective(45.0f, this->aspectRatio, 0.1f, 100.0f); // view: 45 degree
    QVector3D center = this->camera_pos - this->camera_direction * 5.0f;
    projMat.lookAt(this->camera_pos, center, QVector3D(0.f, 1.f, 0.f)); // look from (0,0,3) at (0,0,0), with (0, 1, 0) as the up direction


    for (int i=0;i<4;++i) {
        QMatrix4x4 viewMat;
        viewMat.translate(translationPos[i]);
        QMatrix4x4 modelMat;
        modelMat.rotate(degree + initialDegree[i], 0.5f, 1.0f, 0.0f);
        m_shader->setUniformValue(m_shader->uniformLocation("projectMat"), projMat);
        m_shader->setUniformValue(m_shader->uniformLocation("viewMat"), viewMat);
        m_shader->setUniformValue(m_shader->uniformLocation("modelMat"), modelMat);
        m_shader->setUniformValue(m_shader->uniformLocation("lightPos"), QVector3D(-4.0f, 0.0f, 3.0f));
        // draw object
        f->glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
    }
    // release
    m_shader->release();
    m_vao->release();
    m_texture->release();
    update(); // requrest to schedule an update
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    // 2 degree rotation
    const float SIN_2_DEG = 0.03489949670250097;
    const float COS_2_DEG = 0.9993908270190958;
    float old_x = camera_direction.x();
    float old_z = camera_direction.z();
    float new_x, new_z;
    switch(event->key()) {
        case Qt::Key::Key_Up:
            this->camera_pos = this->camera_pos - this->camera_direction * 0.2f;
            break;
        case Qt::Key::Key_Down:
            this->camera_pos = this->camera_pos + this->camera_direction * 0.2f;
            break;
        case Qt::Key::Key_Right:
            new_x = old_x * COS_2_DEG - old_z * SIN_2_DEG;
            new_z = old_x * SIN_2_DEG + old_z * COS_2_DEG;
            this->camera_direction.setX(new_x);
            this->camera_direction.setZ(new_z);
            break;
        case Qt::Key::Key_Left:
            new_x = old_x * COS_2_DEG + old_z * SIN_2_DEG;
            new_z = -old_x * SIN_2_DEG + old_z * COS_2_DEG;
            this->camera_direction.setX(new_x);
            this->camera_direction.setZ(new_z);
            break;
        case Qt::Key::Key_Space:
            this->isRotating = ! this->isRotating;
            break;
    }
    update();
}
