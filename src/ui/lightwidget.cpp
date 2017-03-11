/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居---照明功能的实现
**************************************************/
#include "lightwidget.h"
#include "ui_lightwidget.h"

LightWidget::LightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightWidget)
{
    ui->setupUi(this);
}

LightWidget::~LightWidget()
{
    delete ui;
}
