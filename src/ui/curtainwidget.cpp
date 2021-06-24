/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-25
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居---窗帘功能的实现（打开、关闭、停止）
**************************************************/
#include "curtainwidget.h"
#include "ui_curtainwidget.h"
#include "myapp.h"

#include <QDebug>
#include "control.h"

bool gIsOpenCurtain = false;

CurtainWidget::CurtainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurtainWidget)
{
    ui->setupUi(this);
}

CurtainWidget::~CurtainWidget()
{
    delete ui;
}

//打开窗帘
void CurtainWidget::on_pbnOpenCurtain_clicked()
{
    gIsOpenCurtain = true;
    gIsSendMessage = true;
    emit signalControlCurtain(CMD_CURTAIN_ON);
}

//关闭窗帘
void CurtainWidget::on_pbnCloseCurtain_clicked()
{
    gIsOpenCurtain = false;
    gIsSendMessage = true;
    emit signalControlCurtain(CMD_CURTAIN_OFF);
}

//窗帘停止
void CurtainWidget::on_pbnStopCurtain_clicked()
{
    gIsSendMessage = true;
    emit signalControlCurtain(CMD_CURTAIN_STOP);
}

void CurtainWidget::slotUpdataCurtainStatus(quint8 cmd)
{
    if (CMD_CURTAIN_ON == cmd)
    {
        qDebug()<<"curtain set on";
    }else if (CMD_CURTAIN_OFF == cmd)
    {
        qDebug()<<"curtain set off";
    }else
    {
        qDebug()<<"curtain set stop";
    }
}

//保存窗帘状态函数，用户系统重新开启后同步数据
void CurtainWidget::slotSaveCurtainStatus()
{
    Myapp::curtain_status = gIsOpenCurtain;
}
