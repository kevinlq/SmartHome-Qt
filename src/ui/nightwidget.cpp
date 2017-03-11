#include "nightwidget.h"
#include "ui_nightwidget.h"

NightWidget::NightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NightWidget)
{
    ui->setupUi(this);
}

NightWidget::~NightWidget()
{
    delete ui;
}
