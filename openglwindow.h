#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QList>
#include <QVector3D>

#include "Shape.h"
#include "point.h"

class QOpenGLShader;
class QOpenGLShaderProgram;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

signals:
    void shapesUpdated();

public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();
    void updateShape(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void mouseMoveEvent(QMouseEvent* event);

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void setupMatrix();
    void drawVertices(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors);


private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    QColor mBackground;
    QQuaternion rotationAngle;
    QPoint lastPos;
    QMetaObject::Connection mContextWatchConnection;

    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
};
