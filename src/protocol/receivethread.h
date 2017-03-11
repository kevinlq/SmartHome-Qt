#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QThread>

class ReceiveThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveThread(QObject *parent = 0);
        
};

#endif // RECEIVETHREAD_H
