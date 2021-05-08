#ifndef MYHELPER_H
#define MYHELPER_H

/*Qt lib*/
#include <QtCore>
//#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <QSound>

#include "frmmessagebox.h"

class myHelper:public QObject
{
public:
    //设置开机启动
    static void setAutoRunWithSystem(bool isAutoRun,const QString &appName,
                                     const QString &appPath)
    {
        QSettings *reg = new QSettings(
                    "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                    QSettings::NativeFormat);

        if (isAutoRun){
            reg->setValue(appName,appPath);
        }else{
            reg->setValue(appName,"");
        }
    }

    //设置编码方式
    static void setUTF8Code()
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
#endif
    }

    //设置皮肤样式
    static bool setStyle(const QString &styleName)
    {
        QFile file(QString("%1").arg(styleName));
        if ( !file.open(QFile::ReadOnly))
        {
            return false;
        }

        QString css = QLatin1String(file.readAll());
        file.close();

        qApp->setStyleSheet(css);

        return true;
    }

    //加载中文字符
    static void setChinese(const QString &fileName)
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(QString("%1").arg(fileName));
        qApp->installTranslator(translator);
    }

    //显示信息框，仅确认按钮
    static void showMessageBoxInfo(const QString &info)
    {
        frmMessageBox *msg = new frmMessageBox;
        msg->SetMessage(info,0);
        msg->exec();
    }

    //显示询问框，确认和取消按钮
    static int showMessageBoxQusetion(const QString &info)
    {
        frmMessageBox *msg = new frmMessageBox;
        msg->SetMessage(info,1);
        return msg->exec();
    }

    //显示错误框,确认和取消按钮
    static void showMessageBoxError(const QString &info)
    {
        frmMessageBox *msg = new frmMessageBox;
        msg->SetMessage(info,2);
        msg->exec();
    }

    //延时
    static void sleep(const int &sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }

    //窗体居中显示
    static void FormInCenter(QWidget *frm,int deskWidth,int deskHeigth)
    {
        int frmX=frm->width();
        int frmY=frm->height();
        QPoint movePoint(deskWidth/2-frmX/2,deskHeigth/2-frmY/2);
        frm->move(movePoint);
    }

    //文件夹是否存在
    static bool FolderIsExist(QString strFolder)
    {
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    //文件是否存在
    static bool FileIsExist(QString strFile)
    {
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    //判断是否是IP地址
    static bool isIpAddress(const QString &ip)
    {
        QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return regExp.exactMatch(ip);
    }

    //16进制字符串转字节数组
    static QByteArray HexStrToByteArray(QString str)
    {
        QByteArray senddata;
        int hexdata,lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len/2);
        char lstr,hstr;
        for(int i=0; i<len; )
        {
            hstr = str[i].toLatin1();
            if(hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16+lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }
    //Conver字符型
    static char ConvertHexChar(char ch)
    {
        if((ch >= '0') && (ch <= '9'))
            return ch - 0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
    }

    //字节数组转16进制字符串
    static QString ByteArrayToHexStr(QByteArray data)
    {
        QString temp="";
        QString hex=data.toHex();
        for (int i=0;i<hex.length();i=i+2)
        {
            temp+=hex.mid(i,2)+" ";
        }
        return temp.trimmed().toUpper();
    }

    //16进制字符串转10进制
    static int StrHexToDecimal(QString strHex)
    {
        bool ok;
        return strHex.toInt(&ok,16);
    }

    //10进制字符串转10进制
    static int StrDecimalToDecimal(QString strDecimal)
    {
        bool ok;
        return strDecimal.toInt(&ok,10);
    }

    //2进制字符串转10进制
    static int StrBinToDecimal(QString strBin)
    {
        bool ok;
        return strBin.toInt(&ok,2);
    }

    //16进制字符串转2进制字符串
    static QString StrHexToStrBin(QString strHex)
    {
        uchar decimal=StrHexToDecimal(strHex);
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<8)
        {
            for (int i=0;i<8-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }

    //10进制转2进制字符串一个字节
    static QString DecimalToStrBin1(int decimal)
    {
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<=8)
        {
            for (int i=0;i<8-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }

    //10进制转2进制字符串两个字节
    static QString DecimalToStrBin2(int decimal)
    {
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<=16)
        {
            for (int i=0;i<16-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }

    //计算校验码
    static uchar GetCheckCode(uchar data[],uchar len)
    {
        uchar temp=0;

        for (uchar i=0;i<len;i++)
        {
            temp+=data[i];
        }

        return temp%256;
    }

    //将溢出的char转为正确的uchar
    static uchar GetUChar(char data)
    {
        uchar temp;
        if (data > 126)
        {
            temp = data + 256;
        }
        else
        {
            temp = data;
        }
        return temp;
    }

    //延时
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //获取当前路径
    static QString GetCurrentPath()
    {
        return QString(QCoreApplication::applicationDirPath()+"/");
    }

    //播放声音
    static void PlaySound(QString soundName)
    {
        QSound::play(soundName);
    }
};

#endif
