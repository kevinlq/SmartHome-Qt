/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-18
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--安防监控功能的实现
**************************************************/
#ifndef SECURITYSETTING_H
#define SECURITYSETTING_H

#include <QWidget>

namespace Ui {
class SecuritySetting;
}

class SecuritySetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit SecuritySetting(QWidget *parent = 0);
    ~SecuritySetting();

private:
    void initForm();
    
private:
    Ui::SecuritySetting *ui;
};

#endif // SECURITYSETTING_H
