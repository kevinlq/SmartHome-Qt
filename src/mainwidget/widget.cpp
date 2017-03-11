/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-11-12
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居--主界面功能的实现
**************************************************/
#include "widget.h"
#include "ui_widget.h"
#include "iconhelper.h"
#include <QKeyEvent>
#include <QToolButton>
#include <QThread>

#include "control.h"
#include "myhelper.h"
#include "myapp.h"
#include "lightwidget.h"
#include "entertainmentwidget.h"
#include "systemsettingdialog.h"

#include "readserialportdata.h"


#include "parlourwidget.h"          //客厅
#include "bedroomwidget.h"          //卧室
#include "kitchenwidget.h"          //厨房
#include "statisticwidget.h"        //统计界面
#include "curtainwidget.h"          //窗帘界面
#include "savedatathread.h"
#include "nightwidget.h"            //夜间模式
#include "securitywidget.h"         //安防监控界面
#include "modelchoosewidget.h"      //模式选择控制界面
#include "musicwidget.h"            //音乐播放界面


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->initDataTime();
    this->initForm();
    this->initWidget();
    this->initToolTip();
    this->initConnect();
}

Widget::~Widget()
{
    delete ui;

    deletWidget();
}

void Widget::initDataTime()
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),
            this,SLOT(slotShowCurrentDataTime()));
    m_timer->start(1000);
}

//界面样式初始化
void Widget::initForm()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle(tr("SmartHome System"));
    //顶部设置和首页的样式
    setToolButtonStyle(ui->tbnSetting,"设置",E_NORMAL,":/images/tool/setting_normal.png");
    setToolButtonStyle(ui->tbnHome,"首页",E_NORMAL,":/images/tool/home_normal.png");

    setStyleSheet(QLatin1String("QToolButton{border:0px;}"));

    //中间部分的样式
    setToolButtonStyle(ui->tbnBedRoom,"卧室",E_BIG,":/images/midwidget/Bedroom.png");
    setToolButtonStyle(ui->tbnParlor,"客厅",E_BIG,":/images/midwidget/Parlor.png");
    setToolButtonStyle(ui->tbnKitchen,"厨房",E_BIG,":/images/midwidget/kitchen.png");
    setToolButtonStyle(ui->tbnSafety,"安防",E_BIG,":/images/midwidget/Safety.png");

    //底部菜单的样式
    setToolButtonStyle(ui->tbnControl,"家居控制",E_NORMAL,
                       ":/images/bottom/control.png");
    setToolButtonStyle(ui->tbnCurtain,"窗帘",E_NORMAL,
                       ":/images/bottom/video.png");
    setToolButtonStyle(ui->tbnMusic,"音乐",E_NORMAL,
                       ":/images/bottom/music.png");
    setToolButtonStyle(ui->tbnModel,"模式选择",E_NORMAL,
                       ":/images/bottom/reset.png");
    setToolButtonStyle(ui->tbnNight,"夜间",E_NORMAL,
                       ":/images/bottom/night.png");
    setToolButtonStyle(ui->tbnStatistic,"统计",E_NORMAL,
                       ":/images/bottom/statistics.png");
    setToolButtonStyle(ui->tbnRelaxation,"添加",E_NORMAL,
                       ":/images/bottom/add.png");
    //    this->setCurrentWidget(E_HOME_WIDGET);
    ui->stackedWidget->setCurrentIndex(E_HOME_WIDGET);

    m_isPress = false;
    location = this->location;

    ui->tbnRelaxation->setVisible(false);
    ui->tbnMusic->setVisible(false);
    ui->tbnCurtain->setVisible(false);
    ui->tbnNight->setVisible(false);

    ui->tbnSafety->setVisible(false);
}

//界面初始化
void Widget::initWidget()
{
    m_settingDialog = new SystemSettingDialog;        //系统设置
    m_parlourWidget = new Parlourwidget;              //客厅
    m_bedRoomWidget = new BedRoomWidget;              //卧室
    m_kitchenWidget = new KitchenWidget;              //厨房
    m_statisticWidget = new StatisticWidget;          //统计
    m_entertainmentWidget = new EntertainmentWidget;  //娱乐
    m_nightWidget = new NightWidget;                  //夜间模式
    m_securityWidget = new SecurityWidget;            //安防监控界面
    m_curtainWidget= new CurtainWidget;               //窗帘界面
    m_modelWidget = new ModelChooseWidget;            //模式控制界面
    m_musicPlayWidget = new MusicWidget;              //音乐播放界面

    //m_menuWidget = new MenuWidget(this);
    //ui->tbnSetting->setMenu(m_menuWidget);


    //串口对象初始化并转移到一个子线程中取执行
    m_readSerial = new ReadSerialPortData;
    QThread *m_thread = new QThread;
    m_readSerial->moveToThread(m_thread);

    connect(m_readSerial,SIGNAL(signalError(QString)),
            this,SLOT(slotErrorString(QString)));
    connect(m_thread,SIGNAL(started()),
            m_readSerial,SLOT(slotInitSerialPort()));
    connect(m_readSerial,SIGNAL(signalFinished()),
            m_thread,SLOT(quit()));
    connect(m_thread,SIGNAL(finished()),
            m_readSerial,SLOT(deleteLater()));
    connect(m_thread,SIGNAL(finished()),
            m_thread,SLOT(deleteLater()));
    if (gIsOpenPort)
    {
        m_thread->start();
    }

    //开启线程定时保存数据
    m_saveDataThread = new SaveDataThread;
    if (gIsOpenPort)
    {
        m_saveDataThread->start();
    }

    ui->stackedWidget->addWidget(m_parlourWidget);
    ui->stackedWidget->addWidget(m_entertainmentWidget);
    ui->stackedWidget->addWidget(m_bedRoomWidget);
    ui->stackedWidget->addWidget(m_kitchenWidget);
    ui->stackedWidget->addWidget(m_statisticWidget);
    ui->stackedWidget->addWidget(m_nightWidget);
    ui->stackedWidget->addWidget(m_securityWidget);
    ui->stackedWidget->addWidget(m_curtainWidget);
    ui->stackedWidget->addWidget(m_modelWidget);
    ui->stackedWidget->addWidget(m_musicPlayWidget);
}

void Widget::initConnect()
{
    /****************客厅信息信号和槽关联*********************/
    //接收关联
    connect(m_readSerial,SIGNAL(signalParlourTempture(QString)),
            m_parlourWidget,SLOT(slotUpdataTemp(QString)));
    connect(m_readSerial,SIGNAL(signalParlourHumidity(QString)),
            m_parlourWidget,SLOT(slotUpdataHum(QString)));
    connect(m_readSerial,SIGNAL(signalParlourLedStatus(quint8,quint8)),
            m_parlourWidget,SLOT(slotUpdataLedStatus(quint8,quint8)));
    //发送关联
    connect(m_parlourWidget,SIGNAL(signalLightMain(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    connect(m_parlourWidget,SIGNAL(signalLightTop(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    connect(m_parlourWidget,SIGNAL(signalLightHelp(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    //发送温度和湿度预设值信息给下位机
    connect(m_parlourWidget,SIGNAL(signalSendTemptureValue(quint8,QString)),
            m_readSerial,SLOT(slotReceiveParlourValue(quint8,QString)));
    connect(m_parlourWidget,SIGNAL(signalSendHumidityVlaue(quint8,QString)),
            m_readSerial,SLOT(slotReceiveParlourValue(quint8,QString)));

    /*******************卧室信息信号和槽关联*********************/
    //接收关联
    connect(m_readSerial,SIGNAL(signalBedRoomTempture(QString)),
            m_bedRoomWidget,SLOT(slotUpdataTemp(QString)));
    connect(m_readSerial,SIGNAL(signalBedRoomeLedStatus(quint8,quint8)),
            m_bedRoomWidget,SLOT(slotUpdataLedStatus(quint8,quint8)));
    //发送关联
    connect(m_bedRoomWidget,SIGNAL(signalLightLeft(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    connect(m_bedRoomWidget,SIGNAL(signalLightRight(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));

    /*****************厨房信息信号和槽关联**********************/
    //接收关联
    connect(m_readSerial,SIGNAL(signalKitchenSmoke(QString)),
            m_kitchenWidget,SLOT(slotUpdataSmokeValue(QString)));
    connect(m_readSerial,SIGNAL(signalBedRoomeLedStatus(quint8,quint8)),
            m_kitchenWidget,SLOT(slotUpdataLedStatus(quint8,quint8)));
    //发送关联
    connect(m_kitchenWidget,SIGNAL(signalLight(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    connect(m_kitchenWidget,SIGNAL(signalSendSmokeValue(quint8,QString)),
            m_readSerial,SLOT(slotReceiveParlourValue(quint8,QString)));

    /*******************窗帘信号和槽关联************************/
    connect(m_curtainWidget,SIGNAL(signalControlCurtain(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));
    connect(m_readSerial,SIGNAL(signalCurtainStatus(quint8)),
            m_curtainWidget,SLOT(slotUpdataCurtainStatus(quint8)));

    /*程序退出时通知各个子界面，保存设备状态************/
    connect(this,SIGNAL(signalCloseSystem()),
            m_bedRoomWidget,SLOT(slotSaveLedStatus()));
    connect(this,SIGNAL(signalCloseSystem()),
            m_parlourWidget,SLOT(slotSaveLedStatus()));
    connect(this,SIGNAL(signalCloseSystem()),
            m_curtainWidget,SLOT(slotSaveCurtainStatus()));
    connect(this,SIGNAL(signalCloseSystem()),
            m_kitchenWidget,SLOT(slotSaveLedStatus()));

    /**************模式选择控制界面*******************/
    connect(m_modelWidget,SIGNAL(signalControlModel(quint8)),
            m_readSerial,SLOT(slotReceiveChildrenValue(quint8)));

    connect(m_modelWidget,SIGNAL(signalControlModel(quint8)),
            m_bedRoomWidget,SLOT(slotChangeLedStatus(quint8)));
    connect(m_modelWidget,SIGNAL(signalControlModel(quint8)),
            m_parlourWidget,SLOT(slotChangeLedStatus(quint8)));
    connect(m_modelWidget,SIGNAL(signalControlModel(quint8)),
            m_kitchenWidget,SLOT(slotChangeLedStatus(quint8)));

    /*****************更新统计图数据*********************/
    connect(m_saveDataThread,SIGNAL(signalUpdataData()),
            m_statisticWidget,SLOT(slotUpdataData()));

//    connect(m_saveDataThread,SIGNAL(signalUpdataData()),
//            m_statisticWidget,SLOT(loadPlotHumidity()));

//    connect(m_timer,SIGNAL(timeout()),
//            m_statisticWidget,SLOT(loadPlotHumidity()));
//    connect(m_timer,SIGNAL(timeout()),
//            m_statisticWidget,SLOT(loadPlotSmoke()));

    /*********************系统设置**********************/
    connect(m_settingDialog,SIGNAL(signalSendSetTempValue(int)),
            m_parlourWidget,SLOT(slotChangeTempSetValue(int)));
    connect(m_settingDialog,SIGNAL(signalSendSetHumValue(int)),
            m_parlourWidget,SLOT(slotChangeHumSetValue(int)));
    connect(m_settingDialog,SIGNAL(signalSendSetSmokeValue(int)),
            m_kitchenWidget,SLOT(slotChangeSmokeSetValue(int)));
}

void Widget::initToolTip()
{
    ui->tbnHome->setToolTip(tr("tip_home"));
    ui->tbnSetting->setToolTip(tr("tip_setting"));

    ui->tbnBedRoom->setToolTip(tr("tip_bedRoom"));
    ui->tbnParlor->setToolTip(tr("tip_parlot"));
    ui->tbnKitchen->setToolTip(tr("tip_kitchen"));
    ui->tbnSafety->setToolTip(tr("tip_safety"));

    ui->tbnCurtain->setToolTip(tr("tip_curtain"));
    ui->tbnStatistic->setToolTip(tr("tip_statistic"));
    ui->tbnNight->setToolTip(tr("tip_night"));

}

void Widget::deletWidget()
{
    if (m_settingDialog != NULL){
        delete m_settingDialog;
        m_settingDialog = NULL;
    }
    if (m_parlourWidget != NULL){
        delete m_parlourWidget;
        m_parlourWidget = NULL;
    }
    if (m_entertainmentWidget != NULL){
        delete m_entertainmentWidget;
        m_entertainmentWidget = NULL;
    }
    if (m_bedRoomWidget != NULL){
        delete m_bedRoomWidget;
        m_bedRoomWidget = NULL;
    }
    if (m_kitchenWidget != NULL){
        delete m_kitchenWidget;
        m_kitchenWidget = NULL;
    }
    if (m_statisticWidget != NULL){
        delete m_statisticWidget;
        m_statisticWidget = NULL;
    }
    if (m_securityWidget != NULL){
        delete m_securityWidget;
        m_securityWidget = NULL;
    }
    if (m_curtainWidget != NULL)
    {
        delete m_curtainWidget;
        m_curtainWidget = NULL;
    }
    if (m_saveDataThread != NULL)
    {
        delete m_saveDataThread;
        m_saveDataThread = NULL;
    }
}

/**
 * @Function:       setToolButtonStyle()
 * @Description:    设置按钮样式
 * @Calls:          被本函数调用
 * @Input:          tbn:        按钮名称
 *                  text:       按钮所显示的文本
 *                  textSize:   文本大小(E_NORMAL,E_BIG)
 *                  iconName:   按钮图标路径
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 */
void Widget::setToolButtonStyle(QToolButton *tbn, const QString &text,
                                int textSize,const QString iconName)
{
    //设置显示的文本
    tbn->setText(text);
    if (textSize == E_BIG)
    {
        tbn->setFont(QFont("文泉驿雅黑",16,QFont::Bold));
    }else if (textSize == E_NORMAL)
        tbn->setFont(QFont("文泉驿雅黑",12,QFont::Bold));

    tbn->setAutoRaise(true);
    //设置按钮图标
    tbn->setIcon(QPixmap(QString("%1").arg(iconName)));
    tbn->setIconSize(QPixmap(QString("%1").arg(iconName)).size());
    //设置文本在图标下边
    tbn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void Widget::startAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "geometry");
    animation->setDuration(800);
    animation->setStartValue(QRect(0, 0,100, 30));
    animation->setEndValue(QRect(0, 0, 800, 360));
    animation->start();
}

void Widget::setCurrentWidget(enum_widget enum_widget_name)
{
    startAnimation();
    ui->stackedWidget->setCurrentIndex(enum_widget_name);
}

//显示当前的日期和时间
void Widget::slotShowCurrentDataTime()
{
    ui->label_hour->setText(QTime::currentTime().toString("hh"));
    ui->label_min->setText(QTime::currentTime().toString("mm"));
    ui->label_sec->setText(QTime::currentTime().toString("ss"));
    ui->label_data->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    ui->label_week->setText(QDate::currentDate().toString("dddd"));
}

void Widget::slotErrorString(QString err)
{
#if QDEBUG
    qDebug()<<"error:"<<err;
#endif
}

void Widget::keyPressEvent(QKeyEvent *key)
{
    switch (key->key())
    {
        case Qt::Key_Escape:
            this->close();
            break;
        case Qt::Key_Space:
            this->showMinimized();
        default:
            break;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
#if _ARM_ == 0
    if (m_isPress && (e->buttons()) &&(Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
#endif
}

void Widget::mousePressEvent(QMouseEvent *e)
{
#if _ARM_ == 0
    if (e->button() == Qt::LeftButton)
    {
        m_isPress = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
#endif
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
#if _ARM_ == 0
    m_isPress = false;
#endif
}

void Widget::closeEvent(QCloseEvent *event)
{
    //软件关闭之前先关闭串口
    if (gIsOpenPort)
    {
        gIsOpenPort = false;
    }
    emit signalCloseSystem();
    event->accept();        //接收退出信号，程序退出
}

void Widget::on_tbnHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(E_HOME_WIDGET);
}


void Widget::on_tbnBedRoom_clicked()
{
    this->setCurrentWidget(E_BEDROOM_WIDGET);
}

void Widget::on_tbnParlor_clicked()
{
    this->setCurrentWidget(E_PARLOUR_WIDGET);
}

void Widget::on_tbnKitchen_clicked()
{
    this->setCurrentWidget(E_KITCHEN_WIDGET);
}

//统计功能界面调用
void Widget::on_tbnStatistic_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_TEMPTURE)
    {
        this->setCurrentWidget(E_TEMPTURE);
    }
}

/*夜间模式*/
void Widget::on_tbnNight_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_NIGHT_WIDGET)
    {
        this->setCurrentWidget(E_NIGHT_WIDGET);
    }
}

//安防监控界面
void Widget::on_tbnSafety_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_SECURITY_WIDGET)
    {
        this->setCurrentWidget(E_SECURITY_WIDGET);
    }
}

void Widget::slot_receiveData(QByteArray buff)
{
    qDebug()<<myHelper::ByteArrayToHexStr(buff);
}

//显示控制界面
void Widget::on_tbnControl_clicked()
{

    this->setCurrentWidget(E_Control_WIDGET);

}

//窗帘界面
void Widget::on_tbnCurtain_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_CURTAIN_WIDGET)
    {
        this->setCurrentWidget(E_CURTAIN_WIDGET);
    }
}

//模式控制界面
void Widget::on_tbnModel_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_MODEL_WIDGET)
    {
        this->setCurrentWidget(E_MODEL_WIDGET);
    }
}

//音乐播放控制界面
void Widget::on_tbnMusic_clicked()
{
    if (ui->stackedWidget->currentIndex() != E_MUSIC_WIDGET)
    {
        this->setCurrentWidget(E_MUSIC_WIDGET);
    }
}

void Widget::on_tbnSetting_clicked()
{
    //m_settingDialog->exec();
}
