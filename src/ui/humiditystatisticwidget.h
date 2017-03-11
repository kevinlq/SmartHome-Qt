/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--湿度浓度统计
**************************************************/
#ifndef HUMIDITYSTATISTICWIDGET_H
#define HUMIDITYSTATISTICWIDGET_H

#include <QWidget>


class QVBoxLayout;
class StatisticsSetting;

class HumidityStatisticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HumidityStatisticWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    void initForm();
    void initConnect();

private:
    StatisticsSetting *m_hum_statistic;
    QVBoxLayout *m_mainLayout;

    QStringList m_dataList;
};

#endif // HUMIDITYSTATISTICWIDGET_H
