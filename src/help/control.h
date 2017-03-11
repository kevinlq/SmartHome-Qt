/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-06
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---系统所需常量的声明及定义
**************************************************/
#ifndef CONTROL_H
#define CONTROL_H

#include <QString>

#define SHADOW_WIDTH            5
#define WINDOW_WIDTH            680
#define WINDOW_HEIGHT           372
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFALUT_SKIN    "images/login/skin"

#define _ARM_        0

//调试信息输出控制，1：输出信息，0：不输出信息
#define QDEBUG  1

//保存数据时间间隔 （单位：秒）(5秒测试可以用)
#define SAVE_DATA_INTERVAL  60

//是否显示图例(1：显示，0：不显示;默认显示)
#define SHOW_LEGEND     1

//设备名称,用于插入数据时使用
#define DEVICE_TEMP         "01"    //温度
#define DEVICE_HUM          "02"    //湿度
#define DEVICE_SMOKE        "03"    //烟雾

#define LED_ON      1
#define LED_OFF     0


extern bool gIsSendMessage;

//预设温度值
extern int set_parlour_tempture;
extern int set_bedroom_tempture;
extern int set_parlour_humidity;        //预设湿度值
extern int set_smoke_density;           //预设烟雾浓度

//各个传感器实时值
extern QString cur_parlour_tempture;    //只统计客厅温度(DS18B20温度值)
extern QString cur_parlour_humidity;    //(DHT11值)
extern QString cur_smoke_density;       //(MQ_2值)

extern bool gIsOpenPort;                //串口打开标志位
extern bool gIsOpenCurtain;             //窗帘是否打开

//灯的名称枚举
enum enum_light_name{
    E_BED_ROOM = 0,             //卧室
    E_PARLOUR,                  //客厅
    E_KITCHEN                   //厨房
};
//灯的数量枚举
enum enum_ligt_num{
    ENUM_ONE = 1,
    ENUM_TWO ,
    ENUM_THREE
};
//统计界面标题
enum enum_statistic_title
{
    ENUM_TEMPTURE,                  //温度统计
    ENUM_HUMIDITY_DENSITY,          //湿度浓度统计
    ENUM_SMOKE_DENSITY              //烟雾浓度统计
};

#endif // CONTROL_H
