/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---娱乐功能的实现
**************************************************/
#include "entertainmentwidget.h"
#include "ui_entertainmentwidget.h"

EntertainmentWidget::EntertainmentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntertainmentWidget)
{
    ui->setupUi(this);
}

EntertainmentWidget::~EntertainmentWidget()
{
    delete ui;
}

