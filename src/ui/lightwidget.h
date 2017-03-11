/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居---照明功能的实现
**************************************************/
#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class LightWidget;
}

class LightWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LightWidget(QWidget *parent = 0);
    ~LightWidget();
    
private:
    Ui::LightWidget *ui;
};

#endif // LIGHTWIDGET_H
