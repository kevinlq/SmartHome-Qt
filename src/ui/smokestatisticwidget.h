/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--烟雾浓度的统计
**************************************************/
#ifndef SMOKESTATISTICWIDGET_H
#define SMOKESTATISTICWIDGET_H

#include <QWidget>

class StatisticsSetting;
class QVBoxLayout;

class SmokeStatisticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SmokeStatisticWidget(QWidget *parent = 0);
    ~SmokeStatisticWidget();
    
signals:
    
public slots:

private:
    void initForm();

private:
    StatisticsSetting *m_statistic;
    QVBoxLayout *m_mainLayout;

    QStringList m_dataList;
    
};

#endif // SMOKESTATISTICWIDGET_H
