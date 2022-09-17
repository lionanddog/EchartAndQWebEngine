#ifndef PieDemo_H
#define PieDemo_H
#include <QWidget.h>
#include <QString.h>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebChannel/QtWebChannel>
#include <QVector>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>

typedef struct title
{
    QString mainTitle;
    QString subTitle;
    QString position; // 分为center left right，标题显示的位置
    title() :mainTitle(""), subTitle(""), position("center") {};
} title;

typedef struct node
{
    QString name;
    double value;
    QString color;
    node() :name(""), value(0), color("#23BC8D") {};
} node;

typedef struct legend
{
    QString type; //要不要可以分页 scroll:可以出现滚动
    QString orient; // 横竖项显示，veritical:竖向  horizontal:横向
    double left;
    double bottom;
    legend() :type(""), left(10), orient("vertical"), bottom(10){};
} legend;

class PieDemo : public QWidget
{
    Q_OBJECT
public:
    PieDemo(QString html);
    ~PieDemo();

    void load();
    void refresh();

    void clearNodes();

    //设置标题：包括主标题，子标题，位置
    void setTitle(QString mainTitle, QString subTitle = "", QString position = "center");
    void setLegend(QString type, QString orient = "vertical", double left = 10, double bottom = 10);
    void setType(QString type);
    void setRadius(QString radius);
    void setCenter(QString horizontal, QString veritical);
    void appendSeries(QString name, double value, QString color);
public slots:
    QString getSeries();
protected:
    void init();
    void initWebChannel();
    QJsonObject getTitle();
    QJsonObject getLegend();
    QJsonArray getLegendData();
    QJsonArray getColor();
    QJsonArray getData();
private:
    QString m_phtml;
    QWebEngineView* m_pview;
    QWebChannel* m_pchannel;

    title* m_pTitle;
    QVector<node*> m_pNodes;
    legend* m_legend;
    QString m_ptype;//图形这里都饼图pie
    QString m_pradius;//饼图弯曲度百分比
    QVector<QString> m_pcenter;//上下左右百分比（占用）
};
#endif // PieDemo_H
