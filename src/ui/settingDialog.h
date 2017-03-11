/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-10
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:完成系统设置功能
            1.主要包括连接ZigBee的串口号、波特率等串口信息的设置
            2.系统启动默认参数设置(比如开机启动，软件名称……)
            2.系统主题
**************************************************/
#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

class SerialThread;

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private:
    void initForm();
    void initWidget();
    void initConnect();
private slots:
    void slotSaveInfo();

    void slotReadInfo(QByteArray by);

    void slot_stop();
    void slot_start();
private:
    Ui::SettingDialog *ui;

    QStringList m_portName;

    SerialThread *m_serialThread;
};

#endif // SETTINGDIALOG_H
