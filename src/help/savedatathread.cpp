/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-08
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---数据存定时储线程的实现
**************************************************/
#include "savedatathread.h"
#include <QDebug>
#include "sqlhelp.h"
#include "control.h"
#include "myhelper.h"
#include <QSqlQuery>
#include <QSqlError>

SaveDataThread::SaveDataThread(QObject *parent) :
    QThread(parent)
{
    this->initForm();
}

SaveDataThread::~SaveDataThread()
{
    if (m_sqlHelp != NULL)
    {
        delete m_sqlHelp;
        m_sqlHelp = NULL;
    }
}

void SaveDataThread::run()
{
    qDebug()<<"=======================\n";
    qDebug()<<"start save sensor data!";
    qDebug()<<"=======================\n";
    while (m_isStop)
    {
        msleep(1000);
        m_count++;

        if ( SAVE_DATA_INTERVAL ==  m_count)
        {
            //保存数据，请求数据，并将数据插入数据库中
            qDebug()<<"\n\n================================";
            qDebug() << SAVE_DATA_INTERVAL<<" come!";
#if 0
            //插入烟雾值
            this->insertData(DEVICE_SMOKE,cur_smoke_density);
            //插入温度值
            this->insertData(DEVICE_TEMP,cur_parlour_tempture);
            //插入湿度值
            this->insertData(DEVICE_HUM,cur_parlour_humidity);
#endif
            //插入数据
            this->insertData();

            emit signalUpdataData();
            m_count = 0;
        }
    }
}

void SaveDataThread::stopSaveThread()
{
    if (1 == m_isStop)
        m_isStop = 0;
}

void SaveDataThread::initForm()
{
    m_isStop = 1;
    m_count = 0;
}

void SaveDataThread::setStartTime(QTime time)
{
    m_time = time;

    m_sqlHelp = new SqlHelp;
}

/**
 * @Function:       insertData(enumDeviceName deviceName,
                                const QString &value)
 * @Description:    将数据插入到数据库中
 * @Calls:          本地调用
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 * 修改说明：
 * 时间：2016年1月20日16:45:02
 * 修改内容：重新实现数据保存的方式，采用批量保存的方式。
 *          之前挨个插入会出现有个传感器数据总是来不及保存！
 */
void SaveDataThread::insertData()
{
#if 0
    QString currentDataTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString sql = "INSERT INTO device_info(device_id,";
    sql += "device_value,device_data,remark) VALUES('";
    sql += deviceName +"','" + value+"','" + currentDataTime + "','" + "')";

    qDebug()<<"insert data:"<<sql;
    m_sqlHelp->ExecuteSql(sql);
#endif

    QString currentDataTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QSqlQuery query;
    query.exec("INSERT INTO[device_info] (device_id,device_value,device_data,remark) VALUES(?,?,?,?)");

    QVariantList sensor_id;
    sensor_id <<DEVICE_TEMP << DEVICE_HUM <<DEVICE_SMOKE;
    query.addBindValue(sensor_id);
    QVariantList sensor_value;
    sensor_value << cur_parlour_tempture <<cur_parlour_humidity
                    <<cur_smoke_density;
    query.addBindValue(sensor_value);
    QVariantList sensor_data;
    sensor_data << currentDataTime
                << QString::number(currentDataTime.toLongLong() +1)
                << QString::number(currentDataTime.toLongLong() +2);
    query.addBindValue(sensor_data);
    QVariantList sensor_remark;
    sensor_remark <<"" <<"" <<"";
    query.addBindValue(sensor_remark);

    try {
        if (!query.execBatch())
        {
            qDebug()<<query.lastQuery();
            qDebug()<<query.lastError();
            return;
        }else
        {
            qDebug()<<"\n=================\n";
            qDebug()<<"save data ok!\n";
            qDebug()<<"\n=================\n";
        }

    } catch (...) {
        qDebug()<<"Add New Sensor Data error!\nUnable to add \
                  a new Data!/n/n";
    }

}
