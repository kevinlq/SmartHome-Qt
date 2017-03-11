#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QWidget>
#include "drop_shadow_widget.h"
#include "push_button.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>

class LoginDialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    
private:
    void initForm();
    void initConnect();
    void translateLanguage();

    void paintEvent(QPaintEvent *event);
signals:
    
private slots:
    void slot_verify();

private:
    QLabel *m_labelIcon;
    QLabel *m_labelTitle;
    QLabel *m_labelName;                //
    QLabel *m_labelPwd;                 //
    QComboBox *m_comboBox_account;      //用户名输入框
    QLineEdit *m_lineEditPwd;           //密码输入框
    PushButton *m_closeButton;
    QPushButton *m_loginButton;          //登录按钮

    QHBoxLayout *m_titleLayout;         //标题栏布局
    QGridLayout *m_grid_layout;
    QHBoxLayout *m_bottomLayout;        //底部布局
    QVBoxLayout *m_mainLayout;          //主布局
    
};

#endif // LOGINDIALOG_H
