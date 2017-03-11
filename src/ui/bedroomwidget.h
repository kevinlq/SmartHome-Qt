/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-06
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--卧室界面的实现，包括卧室床头的灯
**************************************************/
#ifndef BEDROOMWIDGET_H
#define BEDROOMWIDGET_H

#include <QWidget>
#include "analysisdata.h"

class QToolButton;

namespace Ui {
class BedRoomWidget;
}

class BedRoomWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit BedRoomWidget(QWidget *parent = 0);
    ~BedRoomWidget();

private:
    void initForm();
    void init();
    void initConnect();

    //设置灯的样式
    void setLightStyle(const QString styleName);
    void setLedTurnStatus(quint8 status);

private slots:
    void slotLightLeft();
    void slotLightRight();

    void slotUpdataTemp(QString);
    void slotUpdataLedStatus(quint8 device,quint8 cmd);

    void slotSaveLedStatus();
    void slotChangeLedStatus(quint8 status);     //用来改变LED的状态


signals:
    void signalLightLeft(quint8 model);
    void signalLightRight(quint8 model);
    
private:
    Ui::BedRoomWidget *ui;

    QString m_styleOn;                  //灯打开
    QString m_styleOff;                 //灯关闭

};

#endif // BEDROOMWIDGET_H
