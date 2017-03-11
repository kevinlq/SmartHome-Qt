#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>

class MainMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);

    void translateActions();
    
signals:
   void showSettingDialog();
   void showCheckUpdateDialog();
   void showAboutUs();
   void signal_quit();
    
private:
    void createActions();
    void createConnect();

private:

    QAction *action_setting;        //设置
    QAction *action_help;           //帮助
    QAction *action_home;           //网站首页
    QAction *action_check_update;   //检车更新
    QAction *action_about_us;       //关于我们
    QAction *action_contract_author;//联系作者
    QAction *action_quit;           //退出
    
};

#endif // MAINMENU_H
