#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QListWidget>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "Shape.h"

class OpenGLWindow;

class Visualizer : public QMainWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();
    void connectSignalsSlots();
    Shape* createShapeFromPoints();
    std::vector<Line> createLinesFromPoints();
    void clearListAndPoints();

private slots:
    void addPoints();
    void addRegion();
    void addLine();
    void addHermite();
    void addBezier();
    void addBSpline();
    void addPolygon();
    void clipPolygon();
    void clipLine();

private:
    QWidget* mCentralWidget;
    QWidget* mGridLayoutWidget;
    QGridLayout* mGridLayout;
    QHBoxLayout* mHorizontalLayout7;
    QHBoxLayout* mHorizontalLayout8;
    QHBoxLayout* mHorizontalLayout9;
    QHBoxLayout* mHorizontalLayout10;
    QVBoxLayout* mVerticalLayout3;
    QVBoxLayout* mVerticalLayout5;
    QHBoxLayout* mHorizontalLayout5;

    // Buttons
    QPushButton* mPushButton4;
    QPushButton* mPushButton3;
    QPushButton* mPushButton5;
    QPushButton* mPushButton6;
    QPushButton* mPushButton7;
    QPushButton* mPushButton8;
    QPushButton* mPushButton9;
    QPushButton* mPushButton10;

    // DoubleSpinBoxes
    QDoubleSpinBox* mDoubleSpinBox5;
    QDoubleSpinBox* mDoubleSpinBox6;

    // Other widgets
    QPushButton* mPushButton2;
    QListWidget* mListWidget3;
    OpenGLWindow* mOpenGLWidget;

    // Data
    std::vector<Point3D> mPoints;
};

