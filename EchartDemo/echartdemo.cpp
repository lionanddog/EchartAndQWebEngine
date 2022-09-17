#include "echartdemo.h"
#include <QVBoxLayout>
#include <math.h>

static const QList<QString> colors(
    QList<QString>() <<
    "#23BC8D" << "#3986FA" << "#FFC506" << "#DF4952" << "#8354FA" <<
    "#25A34E" << "#35C5F7" << "#FF8E33" << "#004988" << "#FF5CA2");

static const QList<QString> nameList(
    QList<QString>() << "h" << "y" << "g" << "g" << "f" << "p" << "w" << "s" << "e" << "f" << "b" << "a");


EchartDemo::EchartDemo(QWidget *parent)
    : QWidget(parent),
    m_chart(nullptr),
    m_button(nullptr)
{
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9223");
    initView();
    connect(m_button, SIGNAL(clicked()), this, SLOT(refreshClick()));
}

EchartDemo::~EchartDemo()
{

}

void EchartDemo::refreshClick()
{
    generateData();
    m_chart->refresh();
}

void EchartDemo::initView()
{
    m_chart = new PieDemo("D:/Echarts/EchartDemo/x64/Debug/piedemo.html");
    m_chart->setTitle("demo", "subDemo", "left");
    m_chart->setLegend("scroll");
    m_button = new QPushButton;
    m_button->setText("Refresh");
    m_button->setFixedSize(80, 80);
    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(m_chart);
    vlayout->addSpacing(12);
    vlayout->addWidget(m_button);
    setLayout(vlayout);
    generateData();
    QWebEngineView *m_webView = new QWebEngineView(this);
    vlayout->addWidget(m_webView);
    m_webView->load(QUrl("http://localhost:9223"));
    m_chart->load();
}

void EchartDemo::generateData()
{
    m_chart->clearNodes();
    for (int i = 0; i < 10; i++)
    {
        double rad = floor(rand() % 12);
        QString name = nameList[rad];
        rad = floor(rand() % 10);
        QString color = colors[rad];
        double value = rand() % 100;
        m_chart->appendSeries(name, value, color);
    }
}
