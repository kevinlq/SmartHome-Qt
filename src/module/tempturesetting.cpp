/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-04
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--温度控制模块
**************************************************/
#include "tempturesetting.h"
#include "ui_tempturesetting.h"

#include <QToolButton>
#include <QDebug>

TemptureSetting::TemptureSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemptureSetting)
{
    ui->setupUi(this);

    this->initForm();
}

TemptureSetting::~TemptureSetting()
{
    delete ui;
}

void TemptureSetting::initForm()
{
    this->setToolButtonStyle(ui->tbn_temp_add,tr("temp_add"),
                             ":/images/module/temp_add.png");
    this->setToolButtonStyle(ui->tbn_temp_sub,tr("temp_sub"),
                             ":/images/module/temp_sub.png");
    this->setToolButtonStyle(ui->tbn_hum_add,tr("hum_add"),
                             ":/images/module/temp_add.png");
    this->setToolButtonStyle(ui->tbn_hum_sub,tr("hum_sub"),
                             ":/images/module/temp_add.png");
    m_tempture = 20;
    m_humidity = 50;
    this->refreshData();
}

//初始化信号和槽的连接
void TemptureSetting::initConnect()
{
}

void TemptureSetting::setToolButtonStyle(QToolButton *tbn,const QString &text,
                                         const QString iconName)
{
    //设置显示的文本
    tbn->setText(text);
    //tbn->setFont(QFont("文泉驿雅黑",10,QFont::Normal));

    tbn->setAutoRaise(true);
    //设置按钮图标
    tbn->setIcon(QPixmap(QString("%1").arg(iconName)));
    tbn->setIconSize(QSize(40,40));
    //设置文本在图标下边
    tbn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void TemptureSetting::refreshData()
{
    ui->label_set_temp->setText(QString::number(m_tempture,10)+"℃");
    ui->label_set_hum->setText(QString::number(m_humidity,10)+"%");
}

//增加温度值
void TemptureSetting::on_tbn_temp_add_clicked()
{
    m_tempture++;
    this->refreshData();
}

void TemptureSetting::on_tbn_temp_sub_clicked()
{
    m_tempture--;
    this->refreshData();
}

//湿度操作
void TemptureSetting::on_tbn_hum_add_clicked()
{
    m_humidity++;
    this->refreshData();
}

void TemptureSetting::on_tbn_hum_sub_clicked()
{
    m_humidity--;
    this->refreshData();
}
