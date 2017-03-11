/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-04
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--客厅界面的实现，包括客厅的灯，温湿度
**************************************************/
#ifndef PARLOURWIDGET_H
#define PARLOURWIDGET_H

#include <QWidget>

class QHBoxLayout;
class LightSettings;            //灯光模块
class TemptureSetting;          //温度模块

class ReadSerialPortData;

namespace Ui{
class Parlourwidget;
}
class Parlourwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Parlourwidget(QWidget *parent = 0);
    ~Parlourwidget();
    
signals:
    
public slots:

    void slotUpdataTemp(QString temp);

private:
    void initModule();
    void initConnect();

private:
    Ui::Parlourwidget *ui;

    LightSettings *m_moduleLight;
    TemptureSetting *m_moduleTemp;

    QHBoxLayout *m_mainLayout;

    ReadSerialPortData *m_tem;
    
};

#endif // PARLOURWIDGET_H
