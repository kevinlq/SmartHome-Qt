/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-04
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--客厅界面的实现，包括客厅的灯，温湿度
**************************************************/
#include "parlourwidget.h"
#include "ui_Parlourwidget.h"
#include "lightsettings.h"
#include "tempturesetting.h"
#include "control.h"
#include <QHBoxLayout>
#include <QDebug>

#include "readserialportdata.h"

Parlourwidget::Parlourwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Parlourwidget)
{
    ui->setupUi(this);

    //this->initModule();

    m_tem = new ReadSerialPortData;

    connect(m_tem,SIGNAL(signalDs18b20Temp(QString)),
            this,SLOT(slotUpdataTemp(QString)));
}

Parlourwidget::~Parlourwidget()
{
    delete ui;
//    delete m_moduleLight;
//    delete m_moduleTemp;
//    delete m_mainLayout;
}

void Parlourwidget::slotUpdataTemp(QString temp)
{
    qDebug()<<"客厅："<<temp;
}

void Parlourwidget::initModule()
{
    m_moduleLight = new LightSettings(E_PARLOUR,ENUM_THREE,this);   //卧室
    m_moduleTemp = new TemptureSetting(this);

    m_moduleLight->setMaximumSize(300,240);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_moduleLight);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addWidget(m_moduleTemp);
    m_mainLayout->setContentsMargins(15,10,15,10);
    this->setLayout(m_mainLayout);
}
