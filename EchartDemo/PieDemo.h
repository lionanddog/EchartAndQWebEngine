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
    QString position; // ��Ϊcenter left right��������ʾ��λ��
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
    QString type; //Ҫ��Ҫ���Է�ҳ scroll:���Գ��ֹ���
    QString orient; // ��������ʾ��veritical:����  horizontal:����
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

    //���ñ��⣺���������⣬�ӱ��⣬λ��
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
    QString m_ptype;//ͼ�����ﶼ��ͼpie
    QString m_pradius;//��ͼ�����Ȱٷֱ�
    QVector<QString> m_pcenter;//�������Ұٷֱȣ�ռ�ã�
};
#endif // PieDemo_H
