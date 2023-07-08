#include "glwidget.h"
#include <QMatrix4x4>
#include <QKeyEvent>

GLWidget::GLWidget(QWidget *nulltpr):
    QOpenGLWidget(nulltpr), cube(nullptr), camera_pos(0.f, 0.f, 3.f), camera_direction(0.f, 0.f, 1.f),
    _isRotating(true), lastTimerValue(0)
{
    timer = new QElapsedTimer();
    timer->start();
    setFocusPolicy(Qt::StrongFocus); // enable the widget to receive key press
}

GLWidget::~GLWidget() {
    if (cube!=nullptr) {
        delete cube;
    }
}

void GLWidget::initializeGL()
{
    // set aspect ration
    this->aspectRatio = (float)this->width() / this->height();
    QOpenGLFunctions *f = this->context()->functions();
    f->glEnable(GL_DEPTH_TEST);

    // init cube
    if (cube != nullptr) {
        delete cube;
    }
    cube = new CubeModel(f);

    emit stateChanged();
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
                                  QVector3D(-5.0f, -4.5f, -12.4f),
                                  QVector3D(0.0f, 0.0f, -3.0f)};

    float initialDegree[] = {12.0f, 130.0f, 72.0f, 145.0f, 0.0f};
    qint64 newTimeValue = timer->elapsed();
    if (isRotating()) {
        degree += 30.0f * (newTimeValue - lastTimerValue) /1000.f;
    }
    lastTimerValue = newTimeValue;
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);

    cube->bindModel();

    //build MVP matrix
    QMatrix4x4 projMat;
    projMat.perspective(45.0f, this->aspectRatio, 0.1f, 100.0f); // view: 45 degree
    QVector3D center = this->camera_pos - this->camera_direction * 5.0f;
    projMat.lookAt(this->camera_pos, center, QVector3D(0.f, 1.f, 0.f)); // look from (0,0,3) at (0,0,0), with (0, 1, 0) as the up direction
    QVector3D lightPos(-4.0f, 0.0f, 3.0f);
    for (int i=0;i<5;++i) {
        QMatrix4x4 viewMat;
        viewMat.translate(translationPos[i]);
        QMatrix4x4 modelMat;
        modelMat.rotate(degree + initialDegree[i], 0.5f, 1.0f, 0.0f);
        cube->draw(modelMat, viewMat, projMat, lightPos);
    }
    cube->releaseModel();
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
            this->_isRotating = ! this->_isRotating;
            break;
    }
    emit stateChanged();
    update();
}
