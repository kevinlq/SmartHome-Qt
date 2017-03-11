/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--主界面功能的实现
**************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

class QToolButton;
class EntertainmentWidget;
class SystemSettingDialog;

class Parlourwidget;
class BedRoomWidget;
class KitchenWidget;
class NightWidget;
class CurtainWidget;
class ModelChooseWidget;

class StatisticWidget;
class SecurityWidget;
class MusicWidget;

class ReadSerialPortData;

class SaveDataThread;

//class MenuWidget;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    //场景名称枚举
    enum enum_widget{
        E_Control_WIDGET = 0,       //控制主页
        E_HOME_WIDGET,              //首页
        E_PARLOUR_WIDGET = 2,       //客厅
        E_ENTERTAINMENT_WIDGET,     //娱乐
        E_BEDROOM_WIDGET,           //卧室
        E_KITCHEN_WIDGET,           //厨房
        E_TEMPTURE,
        E_NIGHT_WIDGET,             //夜间模式
        E_SECURITY_WIDGET,          //安防管理界面
        E_CURTAIN_WIDGET,           //窗帘界面
        E_MODEL_WIDGET,             //模式控制
        E_MUSIC_WIDGET              //音乐播放界面
    };
    enum E_TEXTSIZE{
        E_NORMAL = 0,
        E_BIG = !E_NORMAL
    };
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void initDataTime();                        //初始化系统日期和时间
    void initForm();                            //样式初始化
    void initWidget();                          //窗体初始化
    void initConnect();                         //信号和槽连接初始化
    void initToolTip();

    void deletWidget();

    //设置按钮样式
    void setToolButtonStyle(QToolButton*tbn,const QString &text,int textSize,
                            const QString iconName);
    void startAnimation();                      //设置动画效果
private slots:
    void setCurrentWidget(enum_widget enum_widget_name);

    //设置当前时间
    void slotShowCurrentDataTime();

    //输出错误信息
    void slotErrorString(QString err);

protected:
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void closeEvent(QCloseEvent *);
    
signals:
    void signalCloseSystem();
private slots:

    void on_tbnHome_clicked();

    void on_tbnBedRoom_clicked();

    void on_tbnParlor_clicked();

    void on_tbnKitchen_clicked();

    void on_tbnStatistic_clicked();

    void on_tbnNight_clicked();

    void on_tbnSafety_clicked();

    void slot_receiveData(QByteArray);

    void on_tbnControl_clicked();

    void on_tbnCurtain_clicked();

    void on_tbnModel_clicked();

    void on_tbnMusic_clicked();

    void on_tbnSetting_clicked();

private:
    Ui::Widget *ui;

    bool m_isPress;
    QPoint mousePoint;
    QRect location;
    SystemSettingDialog *m_settingDialog;           //设置界面
    Parlourwidget *m_parlourWidget;                 //客厅界面
    BedRoomWidget *m_bedRoomWidget;                 //卧室界面
    KitchenWidget *m_kitchenWidget;                 //厨房界面
    StatisticWidget *m_statisticWidget;             //统计界面
    EntertainmentWidget *m_entertainmentWidget;     //娱乐界面
    NightWidget *m_nightWidget;                     //夜间界面
    SecurityWidget *m_securityWidget;               //安防监控界面
    CurtainWidget *m_curtainWidget;                 //窗帘界面
    ModelChooseWidget *m_modelWidget;               //模式选择控制界面
    MusicWidget *m_musicPlayWidget;                 //音乐播放界面

    SaveDataThread *m_saveDataThread;               //定时保存数据指针

    ReadSerialPortData *m_readSerial;

    QTimer *m_timer;

    //MenuWidget *m_menuWidget;                       //菜单
};

#endif // WIDGET_H
