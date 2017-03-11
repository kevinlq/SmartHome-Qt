/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-05
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--烟雾检测模块的实现
**************************************************/
#ifndef SMOKESETTING_H
#define SMOKESETTING_H

#include <QWidget>
class QToolButton;

namespace Ui {
class SmokeSetting;
}

class SmokeSetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit SmokeSetting(QWidget *parent = 0);
    ~SmokeSetting();

    void refreshSmokeValue();       //刷新烟雾浓度值

private:
    void initForm();                //样式初始化
    void initConnect();             //初始化信号和槽的链接

    //设置按钮样式
    void setToolButtonStyle(QToolButton*tbn, const QString &text,
                            const QString iconName);

private slots:
    void slot_add_smoke();
    void slot_sub_smoke();
    
private:
    Ui::SmokeSetting *ui;

    int m_smoke_density;            //预设烟雾浓度值
};

#endif // SMOKESETTING_H
