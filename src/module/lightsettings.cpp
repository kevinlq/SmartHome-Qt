/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-04
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--灯光设置类的实现，主要包括对灯光的控制
**************************************************/
#include "lightsettings.h"
#include "ui_lightsettings.h"

#include <QDebug>


LightSettings::LightSettings(enum_light_name lightName, enum_ligt_num light_num,
                             QWidget *parent) :
    QWidget(parent),ui(new Ui::LightSettings),
    m_lightName(lightName),m_lightNum(light_num)
{
    ui->setupUi(this);

    this->initStyle();
    this->initConnect();
}


LightSettings::~LightSettings()
{
    delete ui;
}

/**
 * @Function:       initStyle()
 * @Description:    界面样式初始化
 * @Calls:          外部调用
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         无
 */
void LightSettings::initStyle()
{
    m_isTurnOn = false;
    m_styleOn = "QLabel{border-image:url(:/images/module/light_on.png);border:0px;}";
    m_styleOff = "QLabel{border-image:url(:/images/module/light_off.png);border:0px;}";
    setLightStyle(m_styleOff);

    //客厅
    if ((E_PARLOUR == m_lightName) && (ENUM_THREE == m_lightNum))
    {
        ui->lab_light_main->setText(tr("light_main"));
        ui->lab_light_top->setText(tr("light_top"));
        ui->lab_light_help->setText(tr("light_help"));
    }else if ((E_BED_ROOM == m_lightName) && (ENUM_THREE == m_lightNum))//卧室
    {
        //ui->lab_light_main->setText(tr("light_sleep"));
        ui->widget_light_top->setVisible(false);
        ui->lab_light_top->setText(tr("light_left_bed"));
        ui->lab_light_help->setText(tr("light_right_bed"));
    }else if ((E_KITCHEN == m_lightName)&&(ENUM_ONE == m_lightNum))//厨房
    {
        ui->widget_light_bottom->setVisible(false);//辅灯隐藏,只显示
        ui->widget_light_mid->setVisible(false);
        ui->lab_light_main->setText(tr("light_kitchen_main"));
    }
}

/**
 * @Function:       initConnect()
 * @Description:    初始化信号和槽的连接
 * @Calls:          被本函数调用的
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 */
void LightSettings::initConnect()
{
    connect(ui->pbn_light_main,SIGNAL(clicked()),
            this,SLOT(slot_lightMain()));
    connect(ui->pbn_light_top,SIGNAL(clicked()),
            this,SLOT(slot_lightTop()));
    connect(ui->pbn_light_help,SIGNAL(clicked()),
            this,SLOT(slot_lightHelp()));
}

//设置灯的状态样式
void LightSettings::setLightStyle(const QString &styleName)
{
    ui->label_light_main->setStyleSheet(styleName);
    ui->label_light_top->setStyleSheet(styleName);
    ui->label_light_help->setStyleSheet(styleName);
}

void LightSettings::slot_lightMain()
{
    if (ui->pbn_light_main->GetCheck())
        ui->label_light_main->setStyleSheet(m_styleOn);
    else
        ui->label_light_main->setStyleSheet(m_styleOff);
}

void LightSettings::slot_lightTop()
{
    if (ui->pbn_light_top->GetCheck())
        ui->label_light_top->setStyleSheet(m_styleOn);
    else
        ui->label_light_top->setStyleSheet(m_styleOff);
}

void LightSettings::slot_lightHelp()
{
    if (ui->pbn_light_help->GetCheck())
        ui->label_light_help->setStyleSheet(m_styleOn);
    else
        ui->label_light_help->setStyleSheet(m_styleOff);
}
