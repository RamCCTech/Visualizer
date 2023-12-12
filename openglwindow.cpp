#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>

#include "SutherlandCohen.h"
#include "SutherlandHodgman.h"



OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    QVector<GLfloat> vertices;

    QVector<GLfloat> colors;

    setRegion(-6, -6, 6, 6);
    drawRegion(vertices, colors);

    Point p1(-6.0f, -6.0f);
    Point p2(-6.0f, 6.0f);
    Point p3(6.0f, 6.0f);
    Point p4(6.0f, -6.0f);

    Line l1(p1, p2);
    Line l2(p2, p3);
    Line l3(p3, p4);
    Line l4(p4, p1);

    std::vector<Line> vl = { l1,l2,l3,l4 };

    Shape region(vl);

    Point p5(0.0f, 0.0f);
    Point p6(7.0f, 0.0f);
    Point p7(7.0f, -8.0f);
    Point p8(-5.0f, -8.0f);

    Line l5(p5, p6);
    Line l6(p6, p7);
    Line l7(p7, p8);
    Line l8(p8, p5);

    std::vector<Line> vp = { l5,l6,l7, l8};
    Shape polygon(vp);

    SutherlandHodgman sh(region, polygon);
    Shape clippedShape = sh.getClippedPolygon();

    drawPolygon(clippedShape, vertices, colors);

    /*Point p5(2, 5);
    Point p6(9, 3);
    Line l5(p5, p6);
    SutherlandCohen sc(region, l5);

    Line l6 = sc.getClippedLine();

    vertices << l6.p1().x() << l6.p1().y();
    vertices << l6.p2().x() << l6.p2().y();

    colors << 1.0f << 1.0f << 1.0f;
    colors << 1.0f << 1.0f << 1.0f;*/


    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::drawPolygon(Shape s, QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    for (int i = 0; i < s.getSize(); i++)
    {
        Line l = s.getShape().at(i);
        vertices << l.p1().x() << l.p1().y();
        vertices << l.p2().x() << l.p2().y();

        colors << 1.0f << 0.0f << 0.0f;//red
        colors << 1.0f << 0.0f << 0.0f;
    }
}

void OpenGLWindow::setRegion(double xMin, double yMin, double xMax, double yMax)
{
    x_min = xMin;
    x_max = xMax;
    y_min = yMin;
    y_max = yMax;
}
void OpenGLWindow::drawRegion(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    vertices << x_min << y_min;
    vertices << x_max << y_min;
    vertices << x_max << y_max;
    vertices << x_max << y_min;
    vertices << x_max << y_max;
    vertices << x_min << y_max;
    vertices << x_min << y_min;
    vertices << x_min << y_max;

    for (int i = 0;i < 8;i++)colors << 0.0f << 1.0f << 1.0f;
}


void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

}