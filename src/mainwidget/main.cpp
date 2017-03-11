/*************************************************
Copyright:kevin
Author:Kevin LiQi
Date:2015-12-01
Email:kevinlq0912@163.com
QQ:936563422
Version:V1.0
Description:智能家居---主程序，加载配置信息、程序样式，设置编码方式
**************************************************/
#include <QApplication>
#include <QMetaType>
#include <QSharedMemory>
#include <QDir>

#include "widget.h"
#include "myhelper.h"
#include "myapp.h"
#include "database.h"
#include "control.h"
#include "logindialog.h"
//#include "systemsettingdialog.h"
#include "analysisdata.h"

#if __ARM__
#include <QWSServer>
#endif

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<MODEL>("MODEL");                    //注册数据类型
#if __ARM__
    QWSServer::setCursorVisible(false);
#endif


    Myapp::ReadConfig();                                  //读配置文件
    myHelper::setUTF8Code();                              //设置编码方式
    myHelper::setStyle(":/images/css/style.css");         //加载样式表
    myHelper::setChinese(":/images/translator/zh_CN.qm");
    myHelper::setChinese(":/images/qt_zh_CN.qm");         //加载中文字符

    QDir dir;
    Myapp::AppPath = dir.currentPath();

    //使程序只能运行一个实例
//    QSharedMemory shared_memory("SmartHome");

//    if (!shared_memory.create(1))
//    {
//        myHelper::showMessageBoxError("程序已经运行，系统将自动关闭!");
//        return 1;
//    }

    if (!myHelper::FileIsExist("SmartHome.db"))
    {
#if QDEBUG
        qDebug()<<"database file is not find!System Now Will Close!";
        qDebug()<<Myapp::AppPath;
#endif
        return 1;
    }else
    {
#if QDEBUG
        qDebug()<<"database file is find OK!";
#endif
    }
    if (!createConnection())
    {
#if QDEBUG
        qDebug()<<"open database failed!";
#endif
    }else
    {
#if QDEBUG
        qDebug()<<"open database succeed!";
#endif
    }

    Widget w;
    w.show();
    
    return a.exec();
}
