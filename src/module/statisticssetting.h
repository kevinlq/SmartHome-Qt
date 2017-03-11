/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--统计模块的实现
**************************************************/
#ifndef STATISTICSSETTING_H
#define STATISTICSSETTING_H

#include <QWidget>
#include "control.h"
#include "qcustomplot.h"

#define TextColor QColor(255,255,0)     //黄色
#define Plot_NoColor QColor(0,0,0,0)    //黑色

#define TextWidth 2
#define LineWidth 1
#define DotWidth  3

namespace Ui {
class StatisticsSetting;
}

class StatisticsSetting : public QWidget
{
    Q_OBJECT
    
public:
    StatisticsSetting(enum_statistic_title title,QWidget *parent = 0);
    ~StatisticsSetting();

    void setShowData(const QStringList &data);      //设置显示的数据

private slots:
    void LoadPlot();

    void slot_movePlot(int);
    void slot_addXGrid(int);
    void slot_addYGrid(int);
    void slot_startBackground(int);
    void slot_showLegend(int);

private:
    void initForm();
    void initPlotForm();
    void initConnect();
    
private:
    Ui::StatisticsSetting *ui;

    int xTickCount;
    int yTickCount;
    int currentCount;
    int currentColor;

    qint16 StrHexToShort(QString strHex);

    QStringList plot_data;                  //数据
    QVector<double> plot_keys;              //
    QVector<double> plot_values;            //

    QList<QColor> Plot_DotColor;
    QList<QColor> Plot_LineColor;
    QList<QColor> Plot_BGColor;

    enum_statistic_title m_title_name;
};

#endif // STATISTICSSETTING_H
