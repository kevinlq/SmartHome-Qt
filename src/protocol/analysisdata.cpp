#include "analysisdata.h"
#include <QDebug>
#include "control.h"

AnalysisData::AnalysisData(QObject *parent) :
    QObject(parent)
{
    initData();
}

//初始化数据包
void AnalysisData::initData()
{
    m_sendBegin = BGN_RESD_MSG;
    m_dataLen = PROTOCOL_BASIC_SIZE;
    m_device = MSG_EMPTY_MODEL;
    m_deviceCmd = MSG_EMPTY_MODEL_CMD;
    m_dataLen = MSG_LEN;
    m_data = MSG_EMPTY_DATA;
    m_sendEnd = END_RESD_MSG;
}

void AnalysisData::packSendData(quint8 drive, quint8 drive_cmd,
                            quint8 data_len, QString data)
{
    m_sendBegin = BGN_RESD_MSG;
    m_dataLen = PROTOCOL_BASIC_SIZE + data_len;
    m_device = drive;
    m_deviceCmd = drive_cmd;
    m_dataLen = data_len;
    m_data = data;
    m_sendEnd = END_RESD_MSG;

    //sendData();
}


/**
 * @Function:       receiveData(Protocol *pro)
 * @Description:    接受数据函数
 * @Calls:          外部调用
 * @Input:          所接受数据的结构体
 * @Output:         无
 * @Return:         无
 * @Others:         其它说明
 */
void AnalysisData::receiveData(AnalysisData *pro)
{
    switch (pro->m_device) {
    case MODULE_BEEP:
        execModuleBeep(pro);
        break;
    default:
        break;
    }
}

void AnalysisData::execModuleBeep(AnalysisData *pro)
{
    switch (pro->m_deviceCmd) {
        case CMD_BEEP_ON:
            qDebug()<<"beep on!";
            break;
        case CMD_BEEP_OFF:
            qDebug()<<"beep off!";
            break;
        default:
            break;
    }
}

void AnalysisData::printData()
{
#ifdef  QDEBUG
    qDebug()<<"============================";
    qDebug()<<"m_sendBegin:"<<m_sendBegin;
    qDebug()<<"m_potocolLen:"<<m_potocolLen;
    qDebug()<<"m_device:"<<m_device;
    qDebug()<<"m_deviceCmd:"<<m_deviceCmd;
    qDebug()<<"m_dataLen:"<<m_dataLen;
    qDebug()<<"m_data:"<<m_data;
    qDebug()<<"m_sendEnd:"<<m_sendEnd;
    qDebug()<<"============================";

#endif
}
