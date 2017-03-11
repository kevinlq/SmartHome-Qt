/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-10-23
Email:kevinlq0912@163.com
QQ:936563422
Description:自定义系统托盘
**************************************************/
#include "systemtray.h"
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

#include "myswitchbutton.h"

SystemTray::SystemTray(QObject *parent) :
    QSystemTrayIcon(parent)
{
    this->initAction();
    this->initTopAction();
    this->initMidAction();
    this->initBottomAction();
    this->addActions();
    this->initConnect();
    //this->translateActions();
}

void SystemTray::translateActions()
{
    m_runOnSystemBoot->setIcon(QIcon(":/image/mainMenu/about.png"));
    m_helpOnline->setIcon(QIcon(":/image/mainMenu/open.png"));
    m_homePage->setIcon(QIcon(":/image/mainMenu/home.png"));
    m_notification->setIcon(QIcon(":/image/mainMenu/home.png"));
    m_settings->setIcon(QIcon(":/image/mainMenu/setting.png"));
}

void SystemTray::initTopAction()
{
    m_topWidget = new QWidget();
    m_topWidgetAction = new QWidgetAction(m_trayMenu);
    m_topLabel = new QLabel(tr("HUST Information Security Lab"));
    m_topLabel->setObjectName(QString("WhiteLabel"));
    m_homeBtn = new QLabel(tr("Visit"));
    m_homeBtn->setCursor(Qt::PointingHandCursor);
    m_homeBtn->setObjectName(QString("WhiteLabel"));

    QVBoxLayout* m_topLayout = new QVBoxLayout();
    m_topLayout->addWidget(m_topLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    m_topLayout->addWidget(m_homeBtn, 0, Qt::AlignRight|Qt::AlignVCenter);

    m_topLayout->setSpacing(5);
    m_topLayout->setContentsMargins(10, 5, 5, 5);

    m_topWidget->setLayout(m_topLayout);
    m_topWidget->installEventFilter(this);
    m_topWidgetAction->setDefaultWidget(m_topWidget);
}

/*
 * @Function:       initMidAction()
 * @Description:    中间action初始化
 * @Calls:          被本函数调用的函数清单
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         中间action添加了自动备份和开机启动开关按钮
 */
void SystemTray::initMidAction()
{
    m_midWidget = new QWidget();
    m_midWidgetAction = new QWidgetAction(m_trayMenu);

    m_autobackupLabel = new QLabel(tr("Auto backup"));
    m_autobackupLabel->setToolTip(tr("Auto backup database can protected your data"));
    m_autobackupBtn = new mySwitchButton();
    m_autobackupBtn->setFixedSize(60,25);
    m_autobackupBtn->setObjectName(QString("TrayButtonAuto"));
    //m_autobackupBtn->setStyleSheet("QPushButton:hover{border-image: url(:/image/switch/switch_hover.png);}");
    m_autobackupBtn->SetCheck(true);

    QHBoxLayout *m_midUpLayout = new QHBoxLayout();
    m_midUpLayout->addWidget(m_autobackupLabel);
    m_midUpLayout->addWidget(m_autobackupBtn);


    m_autoStartLabel = new QLabel(tr("Auto Start"));
    m_autoStartBtn = new mySwitchButton();
    m_autoStartBtn->setFixedSize(60,25);
    m_autoStartBtn->setObjectName(QString("TrayButtonAuto"));
    m_autoStartBtn->SetCheck(true);
    QHBoxLayout *m_midBottomLayout = new QHBoxLayout();
    m_midBottomLayout->addWidget(m_autoStartLabel);
    m_midBottomLayout->addWidget(m_autoStartBtn);


    QVBoxLayout *m_midMainLayout = new QVBoxLayout();
    m_midMainLayout->addLayout(m_midUpLayout);
    m_midMainLayout->addLayout(m_midBottomLayout);

    m_midWidget->setLayout(m_midMainLayout);
    m_midWidgetAction->setDefaultWidget(m_midWidget);

}

void SystemTray::initBottomAction()
{
    m_bottomWidget = new QWidget();
    m_bottomWidgetAction = new QWidgetAction(m_trayMenu);

    m_updateBtn = new QPushButton(QIcon(":/image/mainMenu/update.png"), tr("Update"));
    m_updateBtn->setObjectName(QString("TrayButton"));
    m_updateBtn->setFixedSize(60, 25);

    m_aboutBtn = new QPushButton(QIcon(":/image/mainMenu/about.png"), tr("About"));
    m_aboutBtn->setObjectName(QString("TrayButton"));
    m_aboutBtn->setFixedSize(60, 25);

    m_exitBtn = new QPushButton(QIcon(":/image/mainMenu/quit.png"), tr("Exit"));
    m_exitBtn->setObjectName(QString("TrayButton"));
    m_exitBtn->setFixedSize(60, 25);

    QHBoxLayout* m_bottomLayout = new QHBoxLayout();
    m_bottomLayout->addWidget(m_updateBtn, 0, Qt::AlignCenter);
    m_bottomLayout->addWidget(m_aboutBtn, 0, Qt::AlignCenter);
    m_bottomLayout->addWidget(m_exitBtn, 0, Qt::AlignCenter);

    m_bottomLayout->setSpacing(5);
    m_bottomLayout->setContentsMargins(5,5,5,5);

    m_bottomWidget->setLayout(m_bottomLayout);
    m_bottomWidgetAction->setDefaultWidget(m_bottomWidget);
}

void SystemTray::initAction()
{
    this->setToolTip(tr("POPV4"));
    this->setIcon(QIcon(":/image/system_tray.png"));
    m_trayMenu = new QMenu();

    m_runOnSystemBoot = new QAction(this);
    m_helpOnline = new QAction(this);
    m_homePage = new QAction(this);
    m_notification = new QAction(this);
    m_settings = new QAction(this);

    m_runOnSystemBoot->setText(tr("Restore Window"));
    m_helpOnline->setText(tr("Help Online"));
    m_homePage->setText(tr("Visit Home Page"));
    m_notification->setText(tr("Secturity Notification"));
    m_settings->setText(tr("Settings"));

    this->setContextMenu(m_trayMenu);
}


void SystemTray::addActions()
{
    m_trayMenu->addAction(m_topWidgetAction);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(m_helpOnline);
    m_trayMenu->addAction(m_homePage);
    m_trayMenu->addAction(m_notification);
    m_trayMenu->addAction(m_settings);
    m_trayMenu->addAction(m_runOnSystemBoot);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(m_midWidgetAction);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(m_bottomWidgetAction);
}

//初始化信号和槽的连接
void SystemTray::initConnect()
{
    connect(m_exitBtn,SIGNAL(clicked()),this,SIGNAL(signal_close()));
}

/*
 * @Function:       eventFilter(QObject *obj, QEvent *event)
 * @Description:    事件过滤器
 * @Calls:
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         安装事件过滤器是为了让顶部菜单和底部菜单的颜色区分开。
 *                  当过滤到绘制事件并且绘制的组件是顶部菜单项和底部菜单项时，我们改变绘制方式
 */
bool SystemTray::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_topWidget && event->type() == QEvent::Paint)
    {
        QPainter painter(m_topWidget);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(42,120,192));
        painter.drawRect(m_topWidget->rect());
    }
    return QSystemTrayIcon::eventFilter(obj,event);
}

