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
#include "systemsettingdialog.h"
#include "ui_systemsettingdialog.h"
#include "myapp.h"
#include "myhelper.h"

#include <QDebug>

SystemSettingDialog::SystemSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSettingDialog)
{
    ui->setupUi(this);

    this->initForm();
    this->initData();
    //this->initWidget();
    //this->initConnect();
}

SystemSettingDialog::~SystemSettingDialog()
{
    delete ui;
}

void SystemSettingDialog::initForm()
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
    m_portBaud <<"9600"<<"115200";

    QString port;
    foreach (port, m_portName) {
        ui->cbx_PortName->addItem(port);
    }
    QString baud;
    foreach (baud, m_portBaud) {
        ui->cbx_PortBaud->addItem(baud);
    }
    ui->cbx_PortBaud->setCurrentIndex(getBaudNum(Myapp::baudRate));
    ui->cbx_PortName->setCurrentIndex(getBaudName(Myapp::winPortName));

    this->setMaximumSize(245,292);
    ui->label_title->setText(tr("SystemSetting"));
    //ui->label_title->setStyleSheet("QLabel{font:bold,12pt;}");

    ui->cbx_PortName->setEnabled(false);
    ui->cbx_PortBaud->setEnabled(false);
    m_isopenPort = true;                    //默认串口已经打开
}

void SystemSettingDialog::initData()
{
    ui->spinBox_temp->setValue(Myapp::setTempValue);
    ui->spinBox_hum->setValue(Myapp::setHumValue);
    ui->spinBox_smoke->setValue(Myapp::setSmokeValue);
}

void SystemSettingDialog::initWidget()
{
    //根据不同平台初始化串口类的实例，串口名称已经写在了配置文件中
#ifdef Q_OS_LINUX
    //m_serialThread = new SerialThread(Myapp::portName,this);
#elif defined (Q_OS_WIN)
    //m_serialThread = new SerialThread("COM31",this);
#endif

}

void SystemSettingDialog::initConnect()
{
//    connect(m_serialThread,SIGNAL(serialFinished(QByteArray)),
//            this,SLOT(slotReadInfo(QByteArray)));
}

int SystemSettingDialog::getBaudNum(const int baud)
{
    if ( 9600 == baud)
        return E_BAUD9600;
    if (115200 == baud)
        return E_BAUD115200;
    return E_BAUDNUMNULL;
}

int SystemSettingDialog::getBaudName(const QString &baud)
{
    if (0 == QString::compare(baud,"COM0"))
        return E_BAUDCOM0;
    else if (0 == QString::compare(baud,"COM1"))
        return E_BAUDCOM1;
    else if (0 == QString::compare(baud,"COM2"))
        return E_BAUDCOM2;
    else if (0 == QString::compare(baud,"COM3"))
        return E_BAUDCOM3;
    else if (0 == QString::compare(baud,"COM4"))
        return E_BAUDCOM4;
    else if (0 == QString::compare(baud,"COM5"))
        return E_BAUDCOM5;
    else if (0 == QString::compare(baud,"COM6"))
        return E_BAUDCOM6;
    else if (0 == QString::compare(baud,"COM7"))
        return E_BAUDCOM7;
    else if (0 == QString::compare(baud,"COM8"))
        return E_BAUDCOM8;
    return E_BAUDNUMNULL;
}

void SystemSettingDialog::on_pbnOk_clicked()
{
    Myapp::winPortName = ui->cbx_PortName->currentText();
    Myapp::baudRate = ui->cbx_PortBaud->currentText().toInt();

    Myapp::WriteConfig();

    myHelper::showMessageBoxInfo(tr("configuration success!"));
    this->close();
}

void SystemSettingDialog::on_pbnClosePort_clicked()
{
    if (m_isopenPort)
    {
        //关闭串口
        //m_serialThread->stopThread();
        m_isopenPort = false;
        ui->cbx_PortName->setEnabled(true);
        ui->cbx_PortBaud->setEnabled(true);
        ui->pbnClosePort->setText(tr("open_port"));
    }else
    {
        //打开串口
        m_isopenPort = true;
        ui->cbx_PortName->setEnabled(false);
        ui->cbx_PortBaud->setEnabled(false);
        ui->pbnClosePort->setText(tr("close_port"));
        //m_serialThread->startThread();
    }
}

void SystemSettingDialog::on_tbnMenuClose_clicked()
{
    this->close();
}


void SystemSettingDialog::on_spinBox_temp_valueChanged(int arg1)
{
    emit signalSendSetTempValue(arg1);
}

void SystemSettingDialog::on_spinBox_hum_valueChanged(int arg1)
{
    emit signalSendSetHumValue(arg1);
}

void SystemSettingDialog::on_spinBox_smoke_valueChanged(int arg1)
{
    emit signalSendSetSmokeValue(arg1);
}

void SystemSettingDialog::on_spinBox_save_time_valueChanged(int arg1)
{
    emit signalSendSetSaveDataTime(arg1);
}
