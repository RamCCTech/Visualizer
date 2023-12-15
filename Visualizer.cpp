#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Geometry.h"

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mOpenGLWidget, SIGNAL(shapesUpdated()), mOpenGLWidget, SLOT(update()));
    Geometry geometry;

    geometry.print();
}

Visualizer::~Visualizer()
{}

void Visualizer::setupUi()
{
    resize(867, 702);
    mCentralWidget = new QWidget(this);
    mGridLayoutWidget = new QWidget(mCentralWidget);
    mGridLayoutWidget->setGeometry(QRect(0, 0, 861, 621));
    mGridLayout = new QGridLayout(mGridLayoutWidget);
    mGridLayout->setSpacing(6);
    mGridLayout->setContentsMargins(11, 11, 11, 11);
    mGridLayout->setContentsMargins(0, 0, 0, 0);

    // First, show mHorizontalLayout9
    QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);

    mOpenGLWidget = new OpenGLWindow(QColor(0,0,0), mCentralWidget);
    sizePolicy2.setHeightForWidth(mOpenGLWidget->sizePolicy().hasHeightForWidth());
    mOpenGLWidget->setSizePolicy(sizePolicy2);

    mGridLayout->addWidget(mOpenGLWidget, 1, 0, 1, 1);

    // Second, show mHorizontalLayout7
    mHorizontalLayout7 = new QHBoxLayout();
    mHorizontalLayout7->setSpacing(6);
    mPushButton4 = new QPushButton("ADD Region", mGridLayoutWidget);

    mHorizontalLayout7->addWidget(mPushButton4);

    mPushButton3 = new QPushButton("ADD Polygon", mGridLayoutWidget);

    mHorizontalLayout7->addWidget(mPushButton3);

    mPushButton5 = new QPushButton("ADD Line", mGridLayoutWidget);

    mHorizontalLayout7->addWidget(mPushButton5);
    mGridLayout->addLayout(mHorizontalLayout7, 2, 0, 1, 1);


    // Third, show mHorizontalLayout10
    mHorizontalLayout10 = new QHBoxLayout();
    mHorizontalLayout10->setSpacing(6);

    // Rest of your existing code for mHorizontalLayout10 continues here

    mVerticalLayout5 = new QVBoxLayout();
    mVerticalLayout5->setSpacing(6);
    mHorizontalLayout5 = new QHBoxLayout();
    mHorizontalLayout5->setSpacing(6);
    QLabel* label_4 = new QLabel("POLYGON POINTS", mGridLayoutWidget);

    mHorizontalLayout5->addWidget(label_4);

    QLabel* label_7 = new QLabel("X", mGridLayoutWidget);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy);
    label_7->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    mHorizontalLayout5->addWidget(label_7);

    mDoubleSpinBox5 = new QDoubleSpinBox(mGridLayoutWidget);
    mDoubleSpinBox5->setMinimum(-100.000000000000000);
    mDoubleSpinBox5->setMaximum(100.000000000000000);
    mHorizontalLayout5->addWidget(mDoubleSpinBox5);

    QLabel* label_8 = new QLabel("Y", mGridLayoutWidget);
    sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
    label_8->setSizePolicy(sizePolicy);
    label_8->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    mHorizontalLayout5->addWidget(label_8);

    mDoubleSpinBox6 = new QDoubleSpinBox(mGridLayoutWidget);
    mDoubleSpinBox6->setMinimum(-100.000000000000000);
    mDoubleSpinBox6->setMaximum(100.000000000000000);
    mHorizontalLayout5->addWidget(mDoubleSpinBox6);

    mPushButton2 = new QPushButton("ADD", mGridLayoutWidget);

    mHorizontalLayout5->addWidget(mPushButton2);

    mVerticalLayout5->addLayout(mHorizontalLayout5);

    mListWidget3 = new QListWidget(mGridLayoutWidget);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(mListWidget3->sizePolicy().hasHeightForWidth());
    mListWidget3->setSizePolicy(sizePolicy1);

    mVerticalLayout5->addWidget(mListWidget3);

    mHorizontalLayout10->addLayout(mVerticalLayout5);

    mGridLayout->addLayout(mHorizontalLayout10, 3, 0, 1, 1);


    mHorizontalLayout8 = new QHBoxLayout();
    mPushButton6 = new QPushButton("Clip Lines", mGridLayoutWidget);
    mHorizontalLayout8->addWidget(mPushButton6);
    mPushButton7 = new QPushButton("Clip Polygons", mGridLayoutWidget);
    mHorizontalLayout8->addWidget(mPushButton7);
    mGridLayout->addLayout(mHorizontalLayout8, 4, 0, 1, 1);

    QLabel* label = new QLabel("Clipper", mGridLayoutWidget);
    label->setAlignment(Qt::AlignLeading | Qt::AlignHCenter | Qt::AlignVCenter);

    mGridLayout->addWidget(label, 0, 0, 1, 1);
    connect(mPushButton2, &QPushButton::clicked, this, &Visualizer::addPoints);
    connect(mPushButton4, &QPushButton::clicked, this, &Visualizer::addRegion);
    connect(mPushButton3, &QPushButton::clicked, this, &Visualizer::addPolygon);
    connect(mPushButton5, &QPushButton::clicked, this, &Visualizer::addLine);
    connect(mPushButton7, &QPushButton::clicked, this, &Visualizer::clipPolygon);
    connect(mPushButton6, &QPushButton::clicked, this, &Visualizer::clipLine);
    setCentralWidget(mCentralWidget);
}

void Visualizer::addPoints()
{
    double xValue = mDoubleSpinBox5->value();
    double yValue = mDoubleSpinBox6->value();

    // Create a string representation of the values
    QString itemText = QString("X: %1, Y: %2").arg(xValue).arg(yValue);
    Point3D p(xValue, yValue);
    mPoints.push_back(p);

    // Add the item to the QListWidget
    QListWidgetItem* newItem = new QListWidgetItem(itemText);
    mListWidget3->addItem(newItem);
}

void Visualizer::addRegion()
{
    if (mPoints.size() < 3) {
        // At least three points are needed to create a polygon
        QMessageBox::warning(this, "Error", "At least three points are needed to create a Region.");
        return;
    }
    Shape* s;
    std::vector<Line> lines;
    int size = mPoints.size();
    for (int i = 0;i < size;i++) {
        lines.push_back(Line(mPoints.at(i), mPoints.at((i + 1) % size)));
    }
    s = new Shape(lines);
    mOpenGLWidget->addClippingPolygon(s);

    mListWidget3->clear();
    mPoints.clear();
}
void Visualizer::addLine()
{
    if (mPoints.size() < 2) {
        // At least two points are needed to create a line
        QMessageBox::warning(this, "Error", "At least two points are needed to create a line.");
        return;
    }

    std::vector<Line> lines;
    int size = mPoints.size();
    for (int i = 0;i < size-1;i+=2) {
        lines.push_back(Line(mPoints.at(i), mPoints.at(i+1)));
    }
    mOpenGLWidget->addLines(lines);

    mListWidget3->clear();
    mPoints.clear();
}

void Visualizer::addPolygon()
{
    if (mPoints.size() < 3) {
        // At least three points are needed to create a polygon
        QMessageBox::warning(this, "Error", "At least three points are needed to create a polygon.");
        return;
    }

    std::vector<Line> lines;
    int size = mPoints.size();
    for (int i = 0; i < size; i++) {
        lines.push_back(Line(mPoints.at(i), mPoints.at((i + 1) % size)));
    }

    Shape* polygon = new Shape(lines);
    mOpenGLWidget->addPolygons(polygon);

    mListWidget3->clear();
    mPoints.clear();
}

void Visualizer::clipPolygon()
{
    mOpenGLWidget->clipPolygons();
}
void Visualizer::clipLine()
{
    mOpenGLWidget->clipLines();
}