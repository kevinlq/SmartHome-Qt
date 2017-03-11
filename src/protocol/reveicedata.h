/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-01-2
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居系统---接收数据部分功能的实现
**************************************************/
#ifndef REVEICEDATA_H
#define REVEICEDATA_H

#include <QObject>
class SerialThread;
class AnalysisData;

class ReveiceDAta : public QObject
{
    Q_OBJECT
public:
    explicit ReveiceDAta(QObject *parent = 0);
    
private:
    void init();
    void initConnect();
signals:
    void signalReceiveDataOk(QByteArray byte);
    
public slots:
    void slotReadInfo(QByteArray byte);

private:
    SerialThread *m_serialThread;
    AnalysisData *m_analtisis;
};

#endif // REVEICEDATA_H
