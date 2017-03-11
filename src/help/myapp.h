#ifndef MYAPP_H
#define MYAPP_H
#include <QString>

class Myapp
{
public:
    static QString AppPath;             //应用程序路径
    static int DeskWidth;               //桌面宽度
    static int DeskHeigth;              //桌面高度

    static QString SoftTitle ;          //软件标题
    static QString SoftVersion;         //软件版本
    static QString CompanyName;         //开发商名称
    static QString ContactName;         //联系人
    static QString ContactTel;          //联系电话

    static QString winPortName;         //串口名称
    static QString linuxPortName;
    static int baudRate;                //波特率

    static bool bed_room_led_left;      //卧室左灯
    static bool bed_room_led_right;     //卧室右灯
    static bool parlour_led_main;       //客厅主灯
    static bool parlour_led_top;        //客厅顶灯
    static bool parlour_led_help;       //客厅辅灯
    static bool kitchen_led;            //厨房LED灯
    static bool curtain_status;         //窗帘状态

    static int setHumValue;             //
    static int setTempValue;
    static int setSmokeValue;

    static bool AutoRun;                //是否开机启动,在windows下有用

    static void ReadConfig();           //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();          //写入配置文件,在更改配置文件、程序关闭时调用
};

#endif // MYAPP_H
