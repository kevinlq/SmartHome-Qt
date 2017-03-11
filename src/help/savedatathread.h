/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-08
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---数据存定时储线程的实现
**************************************************/
#ifndef SAVEDATATHREAD_H
#define SAVEDATATHREAD_H

#include <QThread>
#include <QDateTime>
#include "control.h"
#include <QMutex>

class SqlHelp;

class SaveDataThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveDataThread(QObject *parent = 0);
    ~SaveDataThread();

    void run();

    void stopSaveThread();

signals:
    void signalUpdataData();            //通知统计图界面，更新数据

private:
    void initForm();

    void setStartTime(QTime time);

    //void insertData(const QString &deviceName, const QString &value);
    void insertData();

private:
    bool m_isStop;
    int m_count;

    QTime m_time;
    SqlHelp *m_sqlHelp;
    
};

#endif // SAVEDATATHREAD_H
