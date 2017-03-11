#include "modelchoosewidget.h"
#include "ui_modelchoosewidget.h"

#include "analysisdata.h"

ModelChooseWidget::ModelChooseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelChooseWidget)
{
    ui->setupUi(this);
    this->initForm();
}

ModelChooseWidget::~ModelChooseWidget()
{
    delete ui;
}

void ModelChooseWidget::initForm()
{
    ui->label_led_note->setText(tr("default ture on all led"));

    ui->label_leave_model->setVisible(false);
    ui->pbn_leve_home->setVisible(false);
}

/**
 * @Function:       on_pbn_key_led_clicked()
 * @Description:    一键开关灯功能的实现
 * @Calls:
 * @Input:          无
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 */
void ModelChooseWidget::on_pbn_key_led_clicked()
{
    if (ui->pbn_key_led->GetCheck())
    {
        //开灯
        ui->label_led_note->setText(tr("turn off all led"));
        //emit signalChangeLedStatus(CMD_TURN_ON_ALL_LED);
        emit signalControlModel(CMD_TURN_ON_ALL_LED);
    }else
    {
        //关灯
        ui->label_led_note->setText(tr("ture on all led"));
        //emit signalChangeLedStatus(CMD_TURN_OFF_ALL_LED);
        emit signalControlModel(CMD_TURN_OFF_ALL_LED);
    }
}

#if 0
//离家模式
void ModelChooseWidget::on_pbn_leve_home_clicked()
{
    if (ui->pbn_leve_home->GetCheck())
    {
        emit signalControlModel(CMD_LEAVE_HOME_ON);
        //ui->label_leave_model->setText(tr(""));
    }else
    {
        emit signalControlModel(CMD_LEAVE_HOME_OFF);
    }
}
#endif

//回家模式
void ModelChooseWidget::on_pbn_go_home_clicked()
{
    if (ui->pbn_go_home->GetCheck())
    {
        ui->label_go_model->setText(tr("go home model"));
        emit signalControlModel(CMD_GO_HOME_ON);
    }else
    {
        ui->label_go_model->setText(tr("leave home model"));
        emit signalControlModel(CMD_GO_HOME_OFF);
    }
}
