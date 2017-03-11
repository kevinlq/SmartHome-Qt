/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-05
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--烟雾检测模块的实现
**************************************************/
#include "smokesetting.h"
#include "ui_smokesetting.h"
#include <QToolButton>

SmokeSetting::SmokeSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmokeSetting)
{
    ui->setupUi(this);

    this->initForm();
    this->initConnect();
}

SmokeSetting::~SmokeSetting()
{
    delete ui;
}

void SmokeSetting::refreshSmokeValue()
{
    ui->label_set_smoke->setText(QString::number(m_smoke_density,10) + "%");
}

void SmokeSetting::initForm()
{
    setToolButtonStyle(ui->tbn_smoke_add,tr("add_smoke"),
                       ":/images/module/temp_add.png");
    setToolButtonStyle(ui->tbn_smoke_sub,tr("sub_smoke"),
                       ":/images/module/temp_sub.png");

    m_smoke_density = 10;           //预设烟雾浓度值初始化为10
    refreshSmokeValue();
}


void SmokeSetting::initConnect()
{
    connect(ui->tbn_smoke_add,SIGNAL(clicked()),
            this,SLOT(slot_add_smoke()));
    connect(ui->tbn_smoke_sub,SIGNAL(clicked()),
            this,SLOT(slot_sub_smoke()));
}

void SmokeSetting::setToolButtonStyle(QToolButton *tbn, const QString &text,
                                      const QString iconName)
{
    //设置显示的文本
    tbn->setText(text);
    tbn->setFont(QFont("文泉驿雅黑",10,QFont::Normal));

    tbn->setAutoRaise(true);
    //设置按钮图标
    tbn->setIcon(QPixmap(QString("%1").arg(iconName)));
    tbn->setIconSize(QSize(40,40));
    //设置文本在图标下边
    tbn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void SmokeSetting::slot_add_smoke()
{
    m_smoke_density++;
    refreshSmokeValue();
}

void SmokeSetting::slot_sub_smoke()
{
    m_smoke_density--;
    refreshSmokeValue();
}
