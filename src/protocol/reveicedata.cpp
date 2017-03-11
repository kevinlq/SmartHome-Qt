/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-01-2
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居系统---接收数据部分功能的实现
**************************************************/
#include "reveicedata.h"
#include "serialthread.h"
#include "myapp.h"
#include "analysisdata.h"
#include "myhelper.h"
#include <QDebug>
#include <QStringList>

ReveiceDAta::ReveiceDAta(QObject *parent) :
    QObject(parent)
{
    this->init();
    this->initConnect();
}

void ReveiceDAta::init()
{
    //根据不同平台初始化串口类的实例，串口名称已经写在了配置文件中
#ifdef Q_OS_LINUX
    //m_serialThread = new SerialThread(Myapp::portName,this);
#elif defined (Q_OS_WIN)
    //m_serialThread = new SerialThread("COM31",this);
#endif

    m_analtisis = new AnalysisData;

    m_serialThread->start();
}

void ReveiceDAta::initConnect()
{
    connect(m_serialThread,SIGNAL(serialFinished(QByteArray)),
            this,SLOT(slotReadInfo(QByteArray)));
}

/**
 * @Function:       slotReadInfo(QByteArray byte)
 * @Description:    读取串口数据的一帧数据
 * @Calls:
 * @Input:          字节数据
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 */
void ReveiceDAta::slotReadInfo(QByteArray byte)
{
    qDebug()<<myHelper::ByteArrayToHexStr(byte);
//    if (BGN_RESD_MSG == byte.at(0))
//    {
//        m_analtisis->m_sendBegin  = byte.at(0);
//        m_analtisis->m_potocolLen = byte.at(1);
//        m_analtisis->m_device     = byte.at(2);
//        m_analtisis->m_deviceCmd  = byte.at(3);
//        m_analtisis->m_dataLen    = byte.at(4);
//        m_analtisis->m_data       = byte.at(6);
//        m_analtisis->m_sendEnd    = byte.at(10);

//    }else
//    {
//        byte.clear();
//        qDebug()<<"byte is not";
//    }

    //    QString strHex;
    //    QDataStream out(&byte,QIODevice::ReadWrite);//将字节数组读入
    //    while(!out.atEnd())
    //    {
    //        quint8 outchar = 0;
    //        out >>outchar;      //每字节填充一次，直到结束
    //        QString str = QString("%1").arg(outchar&0xff,2,16,QLatin1Char('0'));
    //        strHex +=str;
    //    }
    //    qDebug()<<strHex.split("");
    //#ifdef  QDEBUG
    //    qDebug()<<"receive:"<<by.toHex();
    //    qDebug()<<"data size:"<<by.size();
    //#endif
}
