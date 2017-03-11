#ifndef READSERIALPORTDATA_H
#define READSERIALPORTDATA_H
#include <QObject>
#include "qextserialport.h"

#include "analysisdata.h"

//延时，TIME_OUT是串口读写的延时
#define TIME_OUT 100
//连续发送定时器计时间隔,200ms
#define OBO_TIMER_INTERVAL 200

#include <QTimer>

class ReadSerialPortData : public QObject
{
    Q_OBJECT
public:
    explicit ReadSerialPortData(QObject *parent = 0);
    ~ReadSerialPortData();

    void execCmd(QByteArray buff);

private:
    void initData();
    void init();
    void openSerialPort();      //open
    void initConnect();

    void packSendData(quint8 drive, quint8 drive_cmd,
                      quint8 data_len, QString data);
    void sendData();

    quint8 getProtocolLen();
    quint8 getDevice();
    quint8 getDevieCmd();
    quint8 getDataLen();
    QString getData();

    void execData();
    void execDs18b20Data(QByteArray buff);
    void execDHT11_HumData(QByteArray buff);
    void execDHT11_TemData(QByteArray buff);
    void execSMOKEData(QByteArray buff);

    void sendBedRoomCmd(quint8 cmd);              //发送卧室相关控制命令
    void sendParlourCmd(quint8 cmd);              //发送客厅相关控制命令
    void sendCurtainCmd(quint8 cmd);              //发送窗帘相关控制命令
    void sendKitchenCmd(quint8 cmd);              //发送厨房相关控制命令
    void sendModelCmd(quint8 cmd);                //发送模式控制界面

    //下位机复位后发送的LED状态命令解析函数
//    void execBedRoomeLedStatus(quint8 device);     //卧室灯状态
//    void execParlourLedStatus(quint8 device);      //客厅灯状态
//    void execKitchenLedStatus(quint8 device);      //厨房灯状态
//    void execCurtainStatus(quint8 device);         //窗帘状态
    
signals:
    void singnalReceiveData(QByteArray buff);      //接收数据
    void signalBedRoomTempture(QString);           //卧室温度
    void signalParlourTempture(QString);           //客厅温度
    void signalParlourHumidity(QString);           //客厅湿度
    void signalKitchenSmoke(QString);              //厨房烟雾浓度

    //下位机复位后发送的LED状态命令
    void signalBedRoomeLedStatus(quint8 device,quint8 cmd);
    void signalParlourLedStatus(quint8 device,quint8 cmd);
    void signalKitchenLedStatus(quint8 device,quint8 cmd);
    //窗帘状态
    void signalCurtainStatus(quint8 cmd);

    //状态信息
    void signalFinished();
    void signalError(QString err);
    
public slots:
    void slotReadData();                           //读取数据槽函数
    void slotInitSerialPort();                     //串口初始化

    //发送数据槽函数
    //void sendData(AnalysisData *);

    void slotSendMessage();
    //接收各个子界面传递过来信息,用于向下位机发送
    void slotReceiveChildrenValue(quint8 value);

    //接收客厅传递过来的温湿度预设值
    void slotReceiveParlourValue(quint8,const QString &);

private:
    quint8 m_sendBegin;			//起始标志  以“#”开始
    quint8 m_potocolLen;		//信息长度  可变长
    quint8 m_device;            //设备名
    quint8 m_deviceCmd;         //设备命令
    quint8 m_dataLen;			//数据长度   	没有为0
    QString m_data;             //数据		没有指向空
    quint8 m_sendEnd;			//结束标志	以“@”结束

    QextSerialPort *m_myCom;
    QByteArray m_temp;          //串口接收数据临时变量
    QString strHex;
    AnalysisData *m_analysis;   

    QTimer *m_obotimer;
    unsigned int m_timer_delay;
    unsigned int m_obo_timer_delay;
};

#endif // READSERIALPORTDATA_H
