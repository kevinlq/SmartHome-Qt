/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-08-25
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居---窗帘的实现
**************************************************/
#ifndef CURTAINSETTING_H
#define CURTAINSETTING_H

#include <QWidget>

namespace Ui {
class CurtainSetting;
}

class CurtainSetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit CurtainSetting(QWidget *parent = 0);
    ~CurtainSetting();

private:
    void initForm();            //初始化样式
    void initConnect();         //初始化信号和槽的连接
    
private:
    Ui::CurtainSetting *ui;
};

#endif // CURTAINSETTING_H
