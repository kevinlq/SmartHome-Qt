/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2016-01-28
Description:智能家居系统------菜单的实现
**************************************************/
#include "menuwidget.h"


MenuWidget::MenuWidget(QWidget *parent)
    :QMenu(parent)
{
    this->initForm();
    this->initMenu();
    this->initConnect();
}

MenuWidget::~MenuWidget()
{

}

void MenuWidget::initForm()
{
    m_actionSetting = new QAction(this);
    m_actionQuit = new QAction(this);

    m_actionSetting->setText("Setting");
    m_actionQuit->setText("Quit");
}

void MenuWidget::initMenu()
{
    this->addAction(m_actionSetting);
    this->addAction(m_actionQuit);
}

void MenuWidget::initConnect()
{
    connect(m_actionSetting,SIGNAL(triggered()),
            this,SIGNAL(signalSetting()));
    connect(m_actionQuit,SIGNAL(triggered()),
            this,SIGNAL(signalQuit()));
}

