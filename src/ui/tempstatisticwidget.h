/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--温度的统计
**************************************************/
#ifndef TEMPSTATISTICWIDGET_H
#define TEMPSTATISTICWIDGET_H

#include <QWidget>

class QVBoxLayout;
class StatisticsSetting;

class TempStatisticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TempStatisticWidget(QWidget *parent = 0);
    ~TempStatisticWidget();
    
signals:
    
public slots:

private:
    void initForm();
    void initConnect();

private:
    StatisticsSetting *m_temp_statistic;
    QVBoxLayout *m_mainLayout;

    QStringList m_dataList;
    
};

#endif // TEMPSTATISTICWIDGET_H
