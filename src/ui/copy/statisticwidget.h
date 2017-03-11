/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-07
Email:kevinlq0912@163.com
QQ:936563422
Description:智能家居--统计模块的实现
            温度统计、湿度统计、烟雾浓度统计
**************************************************/
#ifndef STATISTICWIDGET_H
#define STATISTICWIDGET_H

#include <QWidget>
#include "qcustomplot.h"

class SqlHelp;

namespace Ui {
class StatisticWidget;
}

class StatisticWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatisticWidget(QWidget *parent = 0);
    ~StatisticWidget();

private slots:
    void loadPlotTempture();                //加载温度绘图
    void loadPlotHumidity();                //加载湿度绘图
    void loadPlotSmoke();                   //加载烟雾浓度绘图
    
    void on_ckMove_stateChanged(int arg1);

    void on_ckBackground_stateChanged(int arg1);

    void on_ckText_stateChanged(int arg1);

    void slotUpdataData();                  //更新统计图数据

    void slotChangeData(int);               //改变显示数据的方式(当天，本周)

    //显示一周数据
    void slotShowTempWeekData();
    void slotShowHumWeekData();
    void slotShowSmokeWeedData();

private:
    Ui::StatisticWidget *ui;

    int m_currentIndex;                       //当前界面id
    QList<QCustomPlot *> m_plots_list;

    QVector<double> m_plot_tempture_keys;
    QVector<QString> m_plot_tempture_labels;
    QVector<double> m_plot_tempture_values;

    QVector<double> m_plot_hum_keys;
    QVector<double> m_plot_hum_values;

    QVector<double> m_plot_smoke_values;
    QVector<double> m_plot_smoke_keys;
    int m_smoke_count;

    void initStyle();                       //初始化样式
    void initForm();                        //初始化界面
    void initPlot();                        //初始化绘图
    void initPlotTempture();                //初始化温度绘图
    void initPlotHumidity();                //初始化湿度绘图
    void initPlotSmoke();                   //初始化烟雾浓度绘图

    //显示历史数据
    void initData();
    QString ColumnNames[4];                    //列名数组声明
    int ColumnWidths[4];                       //列宽数组声明

    void initConnect();                     //初始化信号和槽连接

    SqlHelp *m_sqlhelp;
};

#endif // STATISTICWIDGET_H
