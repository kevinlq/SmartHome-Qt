/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---娱乐功能的实现
**************************************************/
#ifndef ENTERTAINMENTWIDGET_H
#define ENTERTAINMENTWIDGET_H

#include <QWidget>

namespace Ui {
class EntertainmentWidget;
}

class EntertainmentWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntertainmentWidget(QWidget *parent = 0);
    ~EntertainmentWidget();
    
private slots:

private:
    Ui::EntertainmentWidget *ui;
};

#endif // ENTERTAINMENTWIDGET_H
