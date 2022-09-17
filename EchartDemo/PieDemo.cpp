#include "PieDemo.h"
#include <QVBoxLayout>
#include <QUrl>
#include <QtWebEngineWidgets/qwebenginepage.h>
PieDemo::PieDemo(QString html)
    :m_phtml(html),
    m_pview(nullptr),
    m_pchannel(nullptr),
    m_pTitle(new title()),
    m_legend(new legend()),
    m_ptype("pie"),
    m_pradius("50%")
{
    init();
    m_pcenter.append("50%");
    m_pcenter.append("60%");
    setFixedSize(500, 500);
}

PieDemo::~PieDemo()
{
    delete m_pTitle;
    delete m_legend;
    clearNodes();
    m_pview->deleteLater();
    m_pchannel->deregisterObject(this);
    delete m_pchannel;
    m_pchannel = nullptr;
}

void PieDemo::load()
{
    if (!m_pchannel)
        initWebChannel();

    refresh();
}

void PieDemo::refresh()
{
    QUrl url = QUrl::fromUserInput(m_phtml);
    m_pview->load(m_phtml);
}

void PieDemo::setTitle(QString mainTitle, QString subTitle, QString position)
{
    m_pTitle->mainTitle = mainTitle;
    m_pTitle->subTitle = subTitle;
    m_pTitle->position = position;
}

void PieDemo::setLegend(QString type, QString orient, double left, double bottom)
{
    m_legend->type = type;
    m_legend->orient = orient;
    m_legend->left = left;
    m_legend->bottom = bottom;
}

void PieDemo::setType(QString type)
{
    m_ptype = type;
}

void PieDemo::setRadius(QString radius)
{
    m_pradius = radius;
}

void PieDemo::setCenter(QString horizontal, QString veritical)
{
    m_pcenter.replace(0, horizontal);
    m_pcenter.replace(1, veritical);
}

void PieDemo::appendSeries(QString name, double value, QString color)
{
    node* newNode = new node();
    newNode->name = name;
    newNode->value = value;
    newNode->color = color;
    m_pNodes.append(newNode);
}

void PieDemo::init()
{
    m_pview = new QWebEngineView;
    QHBoxLayout* vLayout = new QHBoxLayout;
    vLayout->addWidget(m_pview);
    vLayout->setContentsMargins(20, 20, 20, 20);
    setLayout(vLayout);
    setContextMenuPolicy(Qt::NoContextMenu);
}

void PieDemo::initWebChannel()
{
    m_pchannel = new QWebChannel;
    m_pchannel->registerObject("pieDemo", this);
    m_pview->page()->setWebChannel(m_pchannel);
}

void PieDemo::clearNodes()
{
    m_pNodes.clear();
}

QJsonObject PieDemo::getTitle()
{
    QJsonObject titles;
    titles.insert("text", m_pTitle->mainTitle);
    titles.insert("subtext", m_pTitle->subTitle);
    titles.insert("left", m_pTitle->position);
    return titles;
}

QJsonObject PieDemo::getLegend()
{
    QJsonObject legends;
    legends.insert("type", m_legend->type);
    legends.insert("orient", m_legend->orient);
    legends.insert("left", m_legend->left);
    legends.insert("bottom", m_legend->bottom);
    legends.insert("top", 50);
    legends.insert("data", getLegendData());
    return legends;
}

QJsonArray PieDemo::getLegendData()
{
    QJsonArray data;
    for (int i = 0; i < m_pNodes.size(); i++)
    {
        data.push_back(m_pNodes[i]->name);
    }
    return data;
}

QJsonArray PieDemo::getColor()
{
    QJsonArray colors;
    for (int i = 0; i < m_pNodes.size(); i++)
    {
        colors.push_back(m_pNodes[i]->color);
    }
    return colors;
}

QJsonArray PieDemo::getData()
{
    QJsonArray data;

    for (int i = 0; i < m_pNodes.size(); i++)
    {
        QJsonObject attr;
        attr.insert("name", m_pNodes[i]->name);
        attr.insert("value", m_pNodes[i]->value);
        data.push_back(attr);
    }

    return data;
}

QString PieDemo::getSeries()
{
    QJsonObject root;
    root.insert("title", getTitle());
    root.insert("color", getColor());
    root.insert("legend", getLegend());

    QJsonArray series;
    QJsonObject attr;
    attr.insert("name", "Ò»¸ödemo");
    attr.insert("type", m_ptype);
    attr.insert("radius", m_pradius);

    QJsonArray center;
    center.push_back(m_pcenter.at(0));
    center.push_back(m_pcenter.at(1));
    attr.insert("center", center);

    attr.insert("data", getData());

    QJsonObject itemStyle;
    QJsonObject emphasis;
    emphasis.insert("shadowBlur", 10);
    emphasis.insert("shadowOffsetX", 0);
    emphasis.insert("shadowColor", "rgba(0, 0, 0, 0.5)");
    itemStyle.insert("emphasis", emphasis);
    attr.insert("itemStyle", itemStyle);
    series.push_back(attr);
    root.insert("series", series);
    return QJsonDocument(root).toJson();
}
