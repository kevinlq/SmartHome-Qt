/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-04
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--灯光设置类的实现，主要包括对灯光的控制
**************************************************/
#ifndef LIGHTSETTINGS_H
#define LIGHTSETTINGS_H

#include <QWidget>
#include "myswitchbutton.h"
#include "control.h"

namespace Ui {
class LightSettings;
}

class LightSettings : public QWidget
{
    Q_OBJECT
    
public:
    explicit LightSettings(enum_light_name lightName,enum_ligt_num light_num,
                           QWidget *parent = 0);
    ~LightSettings();

private:
    void initStyle();                                       //样式初始化
    void initConnect();                                     //信号和槽初始化

    bool getLightStatus() const {return m_isTurnOn;}        //获取灯的状态

    //设置灯的样式
    void setLightStyle(const QString &styleName);

private slots:
    void slot_lightMain();
    void slot_lightTop();
    void slot_lightHelp();
    
private:

    Ui::LightSettings *ui;

    bool m_isTurnOn;                    //灯是否打开
    QString m_styleOn;                  //灯打开
    QString m_styleOff;                 //灯关闭

    enum_light_name m_lightName;        //灯的名称
    enum_ligt_num m_lightNum;           //灯的数量
};

#endif // LIGHTSETTINGS_H
