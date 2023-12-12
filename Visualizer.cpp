#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
}

Visualizer::~Visualizer()
{}

void Visualizer::setupUi() 
{
    resize(600, 600);
    mMenuBar = new QMenuBar(this);
    mMenuBar->setObjectName("menuBar");
    setMenuBar(mMenuBar);
    mMainToolBar = new QToolBar(this);
    mMainToolBar->setObjectName("mainToolBar");
    addToolBar(mMainToolBar);
    mStatusBar = new QStatusBar(this);
    mStatusBar->setObjectName("statusBar");
    setStatusBar(mStatusBar);
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    setCentralWidget(mRenderer);

    setWindowTitle(QCoreApplication::translate("SutherlandCohenClass", "SutherlandCohen", nullptr));
}