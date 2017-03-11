/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-18
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--安防监控界面
**************************************************/
#include "securitywidget.h"
#include "securitysetting.h"
#include <QVBoxLayout>

SecurityWidget::SecurityWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initForm();
}

SecurityWidget::~SecurityWidget()
{
    if (m_securitySetting != NULL){
        delete m_securitySetting;
        m_securitySetting = NULL;
    }
}

void SecurityWidget::initForm()
{
    m_securitySetting = new SecuritySetting(this);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_securitySetting);
    m_mainLayout->setContentsMargins(120,6,15,6);
    this->setLayout(m_mainLayout);
}
