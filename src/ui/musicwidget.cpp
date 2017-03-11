/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-01-21
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:ÖÇÄÜ¼Ò¾Ó---ÒôÀÖ²¥·Å
**************************************************/
#include "musicwidget.h"
#include "ui_musicwidget.h"

MusicWidget::MusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicWidget)
{
    ui->setupUi(this);
}

MusicWidget::~MusicWidget()
{
    delete ui;
}

void MusicWidget::initForm()
{
}
