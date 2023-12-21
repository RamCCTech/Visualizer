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

    void addLines(std::vector<Line> lines);
    void addPolygons(Shape* s);
    void addClippingPolygon(Shape* s);
    void clipPolygons();
    void clipLines();
    void addCurveLines(const std::vector<Point3D>& points);

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void setupMatrix();
    void addClippingPolygonVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void addPolygonsVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void addLinesVertices(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void addShapeVertices(Shape shape, QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float red, float green, float blue);
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
    QMetaObject::Connection mContextWatchConnection;

    Shape mClippingPolygon;
    std::vector<Shape> mPolygons;
    std::vector<Line> mLines;
};
