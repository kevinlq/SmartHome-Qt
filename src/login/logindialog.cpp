#include "logindialog.h"
#include "control.h"

LoginDialog::LoginDialog(QWidget *parent) :
    DropShadowWidget(parent)
{
    this->initForm();
    this->initConnect();
    this->translateLanguage();
}

void LoginDialog::initForm()
{
    this->resize(370,275);

    m_labelIcon = new QLabel();             //图标
    m_labelTitle = new QLabel();            //标题

    m_labelName = new QLabel();             //账号
    m_labelPwd = new QLabel();              //密码

    m_comboBox_account = new QComboBox();   //账号选择框
    m_lineEditPwd = new QLineEdit();        //密码输入框

    m_closeButton = new PushButton();       //关闭按钮
    m_loginButton = new QPushButton();       //登录按钮

    m_labelTitle->setAlignment(Qt::AlignBottom);

    m_closeButton->setPicName(":/images/close");
    m_labelTitle->setObjectName("whiteLabel");

    m_loginButton->setFixedSize(80,25);
    m_loginButton->setObjectName("loginGreenButton");

    m_comboBox_account->setFixedSize(160,25);
    m_lineEditPwd->setFixedSize(160,25);

    m_titleLayout = new QHBoxLayout();      //标题栏布局
    m_titleLayout->addWidget(m_labelIcon);
    m_titleLayout->addWidget(m_labelTitle);
    m_titleLayout->addStretch();
    m_titleLayout->addWidget(m_closeButton);
    m_titleLayout->addSpacing(0);
    m_titleLayout->setContentsMargins(10, 0, 5, 10);

    m_grid_layout = new QGridLayout();          //中间内容布局
    m_grid_layout->addWidget(m_labelName,0,0);
    m_grid_layout->addWidget(m_comboBox_account,0,1);
    m_grid_layout->addWidget(m_labelPwd,1,0);
    m_grid_layout->addWidget(m_lineEditPwd,1,1);
    m_grid_layout->setHorizontalSpacing(5);
    m_grid_layout->setVerticalSpacing(5);
    m_grid_layout->setContentsMargins(20,0,20,0);

    m_bottomLayout = new QHBoxLayout();         //底部布局
    m_bottomLayout->addSpacing(160);
    m_bottomLayout->addWidget(m_loginButton);
    m_bottomLayout->addSpacing(120);
    m_bottomLayout->setContentsMargins(0,4,0,4);

    m_mainLayout = new QVBoxLayout();       //整体布局
    m_mainLayout->addLayout(m_titleLayout);
    m_mainLayout->addSpacing(10);
    m_mainLayout->addLayout(m_grid_layout);
    m_mainLayout->addLayout(m_bottomLayout);
    m_mainLayout->setContentsMargins(0,0,0,0);

    this->setLayout(m_mainLayout);
}

void LoginDialog::initConnect()
{
    connect(m_closeButton,SIGNAL(clicked()),this,
            SLOT(close()));
    connect(m_loginButton,SIGNAL(clicked()),this,
            SLOT(slot_verify()));
}

void LoginDialog::translateLanguage()
{
    this->setWindowTitle(tr("login manage system"));
    m_labelTitle->setText(tr("title_login"));
    m_labelName->setText(tr("accounr"));
    m_labelPwd->setText(tr("password"));
    m_loginButton->setText(tr("pbn_login"));

    m_closeButton->setToolTip(tr("tip_close"));
    m_loginButton->setToolTip(tr("tip_login"));
}

void LoginDialog::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    int width = this->width();
    int height = this->height();
    int draw_height = 95;

    QString skin_name = DEFALUT_SKIN;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH,
                             this->width()-2*SHADOW_WIDTH,
                             this->height()-2*SHADOW_WIDTH),
                       QPixmap(skin_name));

//    QPainter painter3(this);
//    painter3.setPen(Qt::NoPen);
//    painter3.setBrush(Qt::white);
//    painter3.drawRect(QRect(SHADOW_WIDTH, draw_height,
//                            width-2*SHADOW_WIDTH,
//                            height-draw_height -SHADOW_WIDTH));
}

void LoginDialog::slot_verify()
{
}
