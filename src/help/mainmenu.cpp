/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-10-23
Email:kevinlq0912@163.com
QQ:936563422
Description:自定义菜单项
**************************************************/
#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMenu(parent)
{
    this->createActions();

    this->createConnect();
}

void MainMenu::translateActions()
{
    action_setting->setText(tr("setting"));
    action_help->setText(tr("help"));
    action_home->setText(tr("home"));
    action_check_update->setText(tr("check_update"));
    action_about_us->setText(tr("about_us"));
    action_contract_author->setText(tr("contract_author"));
    action_quit->setText(tr("quit"));
}

void MainMenu::createActions()
{
    //创建菜单项
    action_setting = new QAction(this);
    action_help = new QAction(this);
    action_home = new QAction(this);
    action_check_update = new QAction(this);
    action_about_us = new QAction(this);
    action_contract_author = new QAction(this);
    action_quit = new QAction(this);

    action_setting->setIcon(QIcon(":/image/mainMenu/setting.png"));
    action_help->setIcon(QIcon(":/image/mainMenu/help.png"));
    action_home->setIcon(QIcon(":/image/mainMenu/home.png"));
    action_check_update->setIcon(QIcon(":/image/mainMenu/update.png"));
    action_about_us->setIcon(QIcon(":/image/mainMenu/about.png"));
    action_contract_author->setIcon(QIcon(":/image/mainMenu/open.png"));
    action_quit->setIcon(QIcon(":/image/mainMenu/quit.png"));

    //添加菜单项
    this->addAction(action_setting);
    this->addAction(action_help);
    this->addSeparator();
    this->addAction(action_home);
    this->addAction(action_check_update);
    this->addAction(action_about_us);
    this->addSeparator();
    this->addAction(action_contract_author);
    this->addSeparator();
    this->addAction(action_quit);
}

void MainMenu::createConnect()
{
    connect(action_setting,SIGNAL(triggered()),this,SIGNAL(showSettingDialog()));
    connect(action_check_update,SIGNAL(triggered()),this,SIGNAL(showCheckUpdateDialog()));
    connect(action_about_us,SIGNAL(triggered()),this,SIGNAL(showAboutUs()));
    connect(action_quit,SIGNAL(triggered()),this,SIGNAL(signal_quit()));
}
