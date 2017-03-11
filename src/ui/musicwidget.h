/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-01-21
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:÷«ƒ‹º“æ”---“Ù¿÷≤•∑≈
**************************************************/
#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>

namespace Ui {
class MusicWidget;
}

class MusicWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MusicWidget(QWidget *parent = 0);
    ~MusicWidget();
private:
    void initForm();
    void initConnect();
    
private:
    Ui::MusicWidget *ui;
};

#endif // MUSICWIDGET_H
