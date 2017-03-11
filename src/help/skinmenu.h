#ifndef SKINMENU_H
#define SKINMENU_H

#include <QMenu>

class SkinMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SkinMenu(QWidget *parent = 0);
    
     void translateActions();
signals:
    
public slots:
     void setWidgetSkin();     //设置界面皮肤

private:
    void initActions();
    void initConnect();
private:
    QAction *m_action_blue;     //蓝色皮肤
    QAction *m_action_navy;     //深蓝色
    QAction *m_action_black;    //黑色皮肤
    QAction *m_action_gray;     //灰色皮肤
    
};

#endif // SKINMENU_H
