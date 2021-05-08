#include "serialthread.h"
#include <QDebug>
#include "control.h"
#include "myhelper.h"
#include "myapp.h"

#include <QDebug>

SerialThread::SerialThread(QObject *parent):
    QThread(parent)
{
#ifdef Q_OS_LINUX
    //初始化串口操作对象
    m_myCom = new QextSerialPort("/dev/" + Myapp::linuxPortName);
#elif  defined (Q_OS_WIN)
    m_myCom = new QextSerialPort(Myapp::winPortName);
#endif

    m_isStopped = 0;

    //设置串口的一些参数
    m_myCom->setBaudRate(BAUD9600);
    m_myCom->setDataBits(DATA_8);
    m_myCom->setParity(PAR_NONE);
    m_myCom->setStopBits(STOP_1);
    m_myCom->setFlowControl(FLOW_OFF);
    m_myCom->setTimeout(TIME_OUT);

    m_isOpenPort = m_myCom->open(QIODevice::ReadWrite);
    if (m_isOpenPort)
    {
        m_myCom->flush();//清空缓冲区
        m_isStopped = true;

        qDebug()<<"open serial ok!";

    }else
    {
        m_isStopped = false;
        qDebug()<<"open serial failed!";
    }
}

//开启线程，用来接收数据
void SerialThread::run()
{
    QByteArray temp;
    while(m_isStopped)
    {
        msleep(1000);                       //delay 1000ms
        if (m_myCom->bytesAvailable() <= 10){return;};
        temp = m_myCom->readAll();

        emit serialFinished(temp);
    }
}

//停止线程
void SerialThread::stopThread()
{
    if (1 == m_isStopped)
        m_isStopped = 0;
}

//开启线程
void SerialThread::startThread()
{
    if (!m_isOpenPort)
    {
        myHelper::showMessageBoxError(tr("open Serialport fail,please open !"));
        return;
    }else
    {
        if (0 == m_isStopped)
        {
            m_isStopped = 1;
            this->start();
        }
    }
}
