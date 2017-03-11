/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--温度的统计
**************************************************/
#include "tempstatisticwidget.h"
#include "statisticssetting.h"
#include "control.h"
#include <QVBoxLayout>


TempStatisticWidget::TempStatisticWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initForm();
    this->initConnect();
}

TempStatisticWidget::~TempStatisticWidget()
{
}

void TempStatisticWidget::initForm()
{
    m_temp_statistic = new StatisticsSetting(ENUM_TEMPTURE,this);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_temp_statistic);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);

    m_dataList = QString("DB 03 0F 3A A3 63 03 8B 03 50 65 04").split(" ");

    m_temp_statistic->setShowData(m_dataList);
}

void TempStatisticWidget::initConnect()
{
}
