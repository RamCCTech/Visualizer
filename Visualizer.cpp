// Visualizer.cpp

#include "stdafx.h"
#include "Visualizer.h"
#include <QPainter>
#include <QMessageBox>  // Include for QMessageBox


Visualizer::Visualizer(QWidget* parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);

    //connect(ui.pushButton, &QPushButton::clicked, this, &Visualizer::changeText);
    //connect(ui.pushButton, &QPushButton::clicked, this, &Visualizer::changeColor);
}

Visualizer::~Visualizer()
{}

void Visualizer::changeText()
{
    //ui.pushButton->setText("CCTech");
}

void Visualizer::changeColor()
{
    //ui.pushButton->setStyleSheet("background-color: blue;color: white");
}