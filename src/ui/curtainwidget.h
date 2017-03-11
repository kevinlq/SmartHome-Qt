/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-25
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居---窗帘功能的实现（打开、关闭、停止）
**************************************************/
#ifndef CURTAINWIDGET_H
#define CURTAINWIDGET_H

#include <QWidget>
#include "analysisdata.h"

namespace Ui {
class CurtainWidget;
}

class CurtainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CurtainWidget(QWidget *parent = 0);
    ~CurtainWidget();

signals:
    void signalControlCurtain(quint8 cmd);
    
private slots:
    void on_pbnOpenCurtain_clicked();

    void on_pbnCloseCurtain_clicked();

    void on_pbnStopCurtain_clicked();

    void slotUpdataCurtainStatus(quint8 cmd);//更新窗帘状态
    void slotSaveCurtainStatus();           //保存窗帘状态

private:
    Ui::CurtainWidget *ui;
};

#endif // CURTAINWIDGET_H
