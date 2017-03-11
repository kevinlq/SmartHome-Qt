/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---厨房安防功能的实现，主要包括可燃性气体检测，灯光控制,
            发挥部分：添加冰箱的控制
**************************************************/
#ifndef KITCHENWIDGET_H
#define KITCHENWIDGET_H

#include <QWidget>
#include "analysisdata.h"

class QToolButton;

namespace Ui {
class KitchenWidget;
}

class KitchenWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit KitchenWidget(QWidget *parent = 0);
    ~KitchenWidget();

private slots:
    void on_pbn_light_main_clicked();

    void slotUpdataSmokeValue(QString); //更新烟雾浓度值
    //更新LED状态
    void slotUpdataLedStatus(quint8 device,quint8 cmd);

    void on_tbn_smoke_sub_clicked();

    void on_tbn_smoke_add_clicked();

    void slotSaveLedStatus();           //保存LED状态
    void slotChangeLedStatus(quint8 status);         //

signals:
    void signalLight(quint8 model);      //发送灯的状态命令(打开/关闭)

    //发送烟雾预设值
    void signalSendSmokeValue(quint8,const QString&);

public Q_SLOTS:
    void slotChangeSmokeSetValue(const int &);

private:
    void initForm();
    void init();
    void initConnect();

    void refreshSmokeValue();

    //设置灯的样式
    void setLightStyle(const QString &styleName);
    //设置按钮样式
    void setToolButtonStyle(QToolButton*tbn, const QString &text,
                            const QString iconName);

    void setLedTurnStatus(quint8 status);
    
private:
    Ui::KitchenWidget *ui;

    QString m_styleOn;                  //灯打开
    QString m_styleOff;                 //灯关闭
};

#endif // KITCHENWIDGET_H
