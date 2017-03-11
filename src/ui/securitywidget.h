/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-18
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--安防监控界面
**************************************************/
#ifndef SECURITYWIDGET_H
#define SECURITYWIDGET_H

#include <QWidget>

class QVBoxLayout;
class SecuritySetting;

class SecurityWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SecurityWidget(QWidget *parent = 0);
    ~SecurityWidget();
private:
    void initForm();
signals:
    
private:
    SecuritySetting *m_securitySetting;
    QVBoxLayout *m_mainLayout;
    
};

#endif // SECURITYWIDGET_H
