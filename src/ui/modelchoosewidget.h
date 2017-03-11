#ifndef MODELCHOOSEWIDGET_H
#define MODELCHOOSEWIDGET_H

#include <QWidget>

namespace Ui {
class ModelChooseWidget;
}

class ModelChooseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelChooseWidget(QWidget *parent = 0);
    ~ModelChooseWidget();

private:
    void initForm();

signals:
    void signalControlModel(quint8 model);              //控制模式信号
    void signalChangeLedStatus(quint8 model);

private slots:
    void on_pbn_key_led_clicked();

    //void on_pbn_leve_home_clicked();

    void on_pbn_go_home_clicked();

private:
    Ui::ModelChooseWidget *ui;
};

#endif // MODELCHOOSEWIDGET_H
