#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>

class QAction;
class QMemu;
class QSystemTrayIcon;
class QWidget;
class QWidgetAction;
class QPushButton;
class QLabel;
class QHBoxLayout;
class QPainter;

class mySwitchButton;

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0);

    void translateActions();    //翻译菜单名称

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    
signals:
    void signal_close();
public slots:

private:
    void initTopAction();
    void initMidAction();
    void initBottomAction();
    void initAction();
    void addActions();
    void initConnect();

private:

    QMenu* m_trayMenu;                      //系统托盘

    QWidget* m_topWidget;                   //顶部菜单
    QWidgetAction* m_topWidgetAction;       //顶部界面action
    QLabel* m_topLabel;                     //说明信息
    QLabel* m_homeBtn;                      //链接信息,可以进行跳转到自定义的web

    QWidget* m_bottomWidget;                //底部菜单
    QWidgetAction* m_bottomWidgetAction;    //底部界面action
    QPushButton* m_updateBtn;               //软件更新
    QPushButton* m_aboutBtn;                //关于我们
    QPushButton* m_exitBtn;                 //退出

    QWidget *m_midWidget;                   //中间菜单
    QWidgetAction *m_midWidgetAction;       //中间界面action
    QLabel *m_autobackupLabel;
    QLabel *m_autoStartLabel;
    mySwitchButton *m_autobackupBtn;        //自动备份
    mySwitchButton *m_autoStartBtn;         //开机启动

    QAction* m_runOnSystemBoot;             //重新启动
    QAction* m_helpOnline;                  //在线帮助
    QAction* m_homePage;                    //首页
    QAction* m_notification;                //
    QAction* m_settings;                    //设置
    
};

#endif // SYSTEMTRAY_H
