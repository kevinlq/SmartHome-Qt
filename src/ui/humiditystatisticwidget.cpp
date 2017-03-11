/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--湿度浓度统计
**************************************************/
#include "humiditystatisticwidget.h"

#include "statisticssetting.h"
#include "control.h"
#include <QVBoxLayout>

HumidityStatisticWidget::HumidityStatisticWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initForm();
}

void HumidityStatisticWidget::initForm()
{
    m_hum_statistic = new StatisticsSetting(ENUM_HUMIDITY_DENSITY,this);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_hum_statistic);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);

    m_dataList = QString("D0 30 0F 8 A3 69 03 8B 40 A0 65 10").split(" ");

    m_hum_statistic->setShowData(m_dataList);
}
