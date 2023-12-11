#pragma once

#include <QtWidgets/QMainWindow>
class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();


public slots:
    void changeText();
    void changeColor();

private:
    Ui::VisualizerClass ui;
    QVector<QPointF> polygonVertices;
};
