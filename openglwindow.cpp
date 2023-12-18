#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>

#include "SutherlandCohen.h"
#include "SutherlandHodgman.h"
#include "HermiteCurve.h"
#include "BezierCurve.h"



OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) :
    mBackground(background),mClippingPolygon({})
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

    std::vector<Line> clipingPolygonLines = mClippingPolygon.getShape();
    for (int j = 0;j < clipingPolygonLines.size();j++) {
        vertices << clipingPolygonLines.at(j).p1().x() << clipingPolygonLines.at(j).p1().y();
        vertices << clipingPolygonLines.at(j).p2().x() << clipingPolygonLines.at(j).p2().y();
        colors << 1.0f << 1.0f << 0.0f;
        colors << 1.0f << 1.0f << 0.0f;
    }

    for (int i = 0;i < mPolygons.size();i++) {
        std::vector<Line> lines = mPolygons.at(i).getShape();
        for (int j = 0;j < lines.size();j++) {
            vertices << lines.at(j).p1().x() << lines.at(j).p1().y();
            vertices << lines.at(j).p2().x() << lines.at(j).p2().y();
            colors << 1.0f << 1.0f << 1.0f;
            colors << 1.0f << 1.0f << 1.0f;
        }
    }

    for (int j = 0;j < mLines.size();j++) {
        vertices << mLines.at(j).p1().x() << mLines.at(j).p1().y();
        vertices << mLines.at(j).p2().x() << mLines.at(j).p2().y();
        colors << 0.0f << 1.0f << 1.0f;
        colors << 0.0f << 1.0f << 1.0f;
    }
    
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::clipPolygons()
{
    for (int i = 0;i < mPolygons.size();i++) {
        SutherlandHodgman sh(mClippingPolygon, mPolygons.at(i));
        mPolygons.at(i) = sh.getClippedPolygon();
    }
    emit shapesUpdated();
}

void OpenGLWindow::clipLines()
{
    for (int i = 0;i < mLines.size();i++) {
        SutherlandCohen sc(mClippingPolygon, mLines[i]);

        mLines[i] = sc.getClippedLine();
    }
    emit shapesUpdated();
}

void OpenGLWindow::addClippingPolygon(Shape* s)
{
    mClippingPolygon=*s;
    emit shapesUpdated();
}
void OpenGLWindow::addPolygons(Shape* s)
{
    mPolygons.push_back(*s);
    emit shapesUpdated();
}
void OpenGLWindow::addLines(std::vector<Line> lines)
{
    for(Line l:lines)
    mLines.push_back(l);
    emit shapesUpdated();
}

void OpenGLWindow::addHermiteCurve(std::vector<Point3D> points)
{
    HermiteCurve bs(points);
    std::vector<Point3D> hermitePoints = bs.calculateHermite();

    // Ensure that there are at least two points in the B-spline curve
    if (hermitePoints.size() < 2) {
        // Handle the case where there are not enough points
        return;
    }

    // Create lines from the B-spline curve points
    for (int i = 0; i < hermitePoints.size() - 1; i++) {
        mLines.push_back(Line(hermitePoints[i], hermitePoints[i + 1]));
    }

    emit shapesUpdated();
}

void OpenGLWindow::addBezierCurve(std::vector<Point3D> points)
{
    BezierCurve bs(points);
    std::vector<Point3D> bezierPoints = bs.calculateBezier();

    // Ensure that there are at leabezierpoints in the B-spline curve
    if (bezierPoints.size() < 2) {
        // Handle the case where there are not enough points
        return;
    }

    // Create lines from the B-spline curve points
    for (int i = 0; i < bezierPoints.size() - 1; i++) {
        mLines.push_back(Line(bezierPoints[i], bezierPoints[i + 1]));
    }

    emit shapesUpdated();
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