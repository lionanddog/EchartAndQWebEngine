#ifndef ECHARTDEMO_H
#define ECHARTDEMO_H

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QWidget>
#include "PieDemo.h"
#include "ui_echartdemo.h"

class EchartDemo : public QWidget
{
    Q_OBJECT

public:
    EchartDemo(QWidget *parent = 0);
    ~EchartDemo();

public slots:
    void refreshClick();
private:
    void initView();
    void generateData();

private:
    PieDemo* m_chart;
    QPushButton* m_button;
};

#endif // ECHARTDEMO_H
