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
#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "myapp.h"
#include "myhelper.h"
#include "serialthread.h"
#include "control.h"
#include <QByteArray>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    this->initForm();
    this->initWidget();
    this->initConnect();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::initForm()
{

    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint);

   //根据不同平台初始化串口名称
#ifdef Q_OS_LINUX
    m_portName << "ttySAC0" <<"ttySAC1" << "ttySAC2" << "ttySAC3"<< "ttySAC4";
#elif defined (Q_OS_WIN)
    m_portName <<"COM0" <<"COM1"<<"COM2" <<"COM3" <<"COM4" <<"COM5"<<"COM6"
               <<"COM7" <<"COM8"<<"COM9" <<"COM10"<<"COM11"<<"COM12"<<"COM13";
#endif

    QString port;
    foreach (port, m_portName) {
        ui->cbx_PortName->addItem(port);
    }

    ui->letAppTitle->setText(Myapp::SoftTitle);
    ui->letAuthor->setText(Myapp::ContactName);

    this->setMaximumSize(245,292);
    ui->label->setText("系统设置");
}

void SettingDialog::initWidget()
{
    //根据不同平台初始化串口类的实例，串口名称已经写在了配置文件中
#ifdef Q_OS_LINUX
    m_serialThread = new SerialThread(Myapp::portName,this);
#elif defined (Q_OS_WIN)
    m_serialThread = new SerialThread("COM31",this);
#endif

    m_serialThread->start();
}

void SettingDialog::initConnect()
{
    connect(ui->pbnOk,SIGNAL(clicked()),this,SLOT(slotSaveInfo()));
    connect(ui->tbnMenuClose,SIGNAL(clicked()),this,SLOT(close()));

    connect(m_serialThread,SIGNAL(serialFinished(QByteArray)),
            this,SLOT(slotReadInfo(QByteArray)));

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_stop()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slot_start()));
}

//保存配置信息,写入配置文件
void SettingDialog::slotSaveInfo()
{
    Myapp::winPortName = ui->cbx_PortName->currentText();
    Myapp::SoftTitle = ui->letAppTitle->text();
    Myapp::ContactName = ui->letAuthor->text();

    Myapp::WriteConfig();

    myHelper::showMessageBoxInfo("配置成功!");
    this->close();
}

void SettingDialog::slotReadInfo(QByteArray by)
{
   //QString temp = myHelper::ByteArrayToHexStr(by);
   //qDebug() <<temp;
    QString strHex;
    QDataStream out(&by,QIODevice::ReadWrite);//将字节数组读入
    while(!out.atEnd())
    {
        quint8 outchar = 0;
        out >>outchar;      //每字节填充一次，直到结束
        QString str = QString("%1").arg(outchar&0xff,2,16,QLatin1Char('0'));
        strHex +=str;
    }

    qDebug()<<strHex.split("");
//#ifdef  QDEBUG
//    qDebug()<<"receive:"<<by.toHex();
//    qDebug()<<"data size:"<<by.size();
//#endif

}

void SettingDialog::slot_stop()
{
    m_serialThread->stopThread();
}

void SettingDialog::slot_start()
{
    m_serialThread->startThread();
}
