#ifndef ANALYSISDATA_H
#define ANALYSISDATA_H

#include <QObject>

#define   BGN_RESD_MSG		     0x23	 //"#":起始符(0x23)
#define   END_RESD_MSG           0x2A  	 //"*":结束符(0x2A)

/*数据发送解析式的宏定义*/
#define PROTOCOL_BASIC_SIZE 	 0x07

#define PROTOCOL_FULL_CMD   	 0x00
#define PROTOCOL_ZERO_LEN        0x00
#define PROTOCOL_FULL_DATA       0x00
#define DATA_TO_ASCII            0x30   //发送数据时数字到ASCII码的基数0

/*默认数据类型宏定义*/
#define MSG_EMPTY_DATA           ""    //空数据
#define MSG_LEN                  5     //默认数据长度
#define MSG_EMPTY_MODEL          0x00  //默认设备名
#define MSG_EMPTY_MODEL_CMD      0x00  //默认设备命令

typedef enum MODEL{
    MODULE_BED_ROOM_LED_LEFT  = 0x30,     //卧室左灯    30
    MODULE_BED_ROOM_LED_RIGHT       ,     //卧室右灯    31
    MODULE_PARLOUR_LED_MAIN         ,     //客厅主灯    32
    MODULE_PARLOUR_LED_TOP          ,     //客厅顶灯    33
    MODULE_PARLOUR_LED_HELP         ,     //客厅辅灯    34
    MODULE_KITCHIN_LED              ,     //厨房灯      35
    MODULE_CURTAIN		  			,     //窗帘(步进电机控制)36
    MODULE_DS18B20			    	,     //温度(客厅温度)    37
    MODULE_DHT11_TEMP				,     //湿度(卧室温度)    38
    MODULE_DHT11_HUM                ,     //DHT11湿度        39
    MODULE_SMOKE					,     //烟雾浓度        0x3A
    MODULE_BEEP 					,     //蜂鸣器          0x3B
    MODULE_GO_HOME                  ,     //回家模式
    MODULE_LEAVE_HOME               ,     //离家模式
    MODULE_ALL_LED                  ,     //所有LED灯

    CMD_BED_ROOM_LED_LEFT_ON        ,     //卧室左灯亮        3C
    CMD_BED_ROOM_LED_LEFT_OFF       ,     //卧室左灯灭        3D
    CMD_BED_ROOM_LED_RIGHT_ON       ,     //卧室右灯亮        3E
    CMD_BED_ROOM_LED_RIGHT_OFF      ,     //卧室右灯灭        3F
    CMD_PARLOUR_LED_MAIN_ON         ,     //客厅主灯亮        40
    CMD_PARLOUR_LED_MAIN_OFF        ,     //客厅主灯灭        41
    CMD_PARLOUR_LED_TOP_ON          ,     //客厅顶灯亮        42
    CMD_PARLOUR_LED_TOP_OFF         ,     //客厅顶灯灭        43
    CMD_PARLOUR_LED_HELP_ON         ,     //客厅辅灯亮        44
    CMD_PARLOUR_LED_HELP_OFF        ,     //客厅福鼎灭        45
    CMD_KITCHEN_LED_ON              ,     //厨房灯亮          46
    CMD_KITCHEN_LED_OFF             ,     //厨房灯灭          47
    CMD_BEEP_ON						,     //蜂鸣器响          48
    CMD_BEEP_OFF      				,	  //蜂鸣器灭          49
    CMD_CURTAIN_ON 					,	  //窗帘开(步进电机正转)4A
    CMD_CURTAIN_STOP                ,     //窗帘停止          4B
    CMD_CURTAIN_OFF                 ,     //窗帘关(步进电机反转)4C
    CMD_LEAVE_HOME_ON               ,     //离家模式开启
    CMD_LEAVE_HOME_OFF              ,     //离家模式关闭
    CMD_GO_HOME_ON                  ,     //回家模式开启
    CMD_GO_HOME_OFF                 ,     //回家模式关闭
    CMD_TURN_ON_ALL_LED             ,     //一键开灯
    CMD_TURN_OFF_ALL_LED                  //一键关灯
}MODEL;


class AnalysisData : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisData(QObject *parent = 0);

    void initData(void);
    
public slots:

public:

    void packSendData(quint8 drive, quint8 drive_cmd,
                  quint8 data_len, QString data);
    void  sendData(AnalysisData *);                    //打包发送数据

    void updataPack();

    void receiveData(AnalysisData *pro);

    void execModuleBeep(AnalysisData *pro);

    //请求数据函数
    void requestData(MODEL deviceName);

    void printData();

private:
    quint8 m_sendBegin;			//起始标志  以“*”开始
    quint8 m_potocolLen;		//信息长度  可变长
    quint8 m_device;            //设备名
    quint8 m_deviceCmd;         //设备命令
    quint8 m_dataLen;			//数据长度   	没有为0
    QString m_data;             //数据		没有指向空
    quint8 m_sendEnd;			//结束标志	以“#”结束
    
};

#endif // ANALYSISDATA_H
