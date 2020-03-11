#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"

/*Qt lib*/
#include <QMouseEvent>

frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);

    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);

    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    this->setMaximumSize(270,140);
    //窗体居中显示
    //myHelper::FormInCenter(this,Myapp::DeskWidth,Myapp::DeskHeigth);

}

frmMessageBox::~frmMessageBox()
{
    delete ui;
}

void frmMessageBox::SetMessage(const QString &msg, int type)
{
    //提示消息框
    if (type == 0)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/message/info.png);");
        ui->btnCancel->setVisible(false);   //取消按钮不可见
        ui->lab_Title->setText(tr("title"));
    }
    //询问消息框
    else if (type == 1)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/message/question.png);");
        ui->lab_Title->setText(tr("question"));
    }
    //错误消息框
    else if (type == 2)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/message/error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText(tr("error"));
    }

    ui->labInfo->setText(msg);
}

void frmMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}

void frmMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
