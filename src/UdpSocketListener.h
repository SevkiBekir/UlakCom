#ifndef UdpSocketListener_H
#define UdpSocketListener_H

#include <QThread>
#include <QUdpSocket>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QDataStream>

#include <QMutex>
#include "Data.h"

class UdpSocketListener : public QThread {
    Q_OBJECT
  public:
    explicit UdpSocketListener(int port);
    ~UdpSocketListener();


  signals:
    void error(QString);
    void printString(QString);
    void runApplication(const QString& applicationPath, const QString& applicationArguments);
    void dataInSignal(Data);

  public slots:
    void readyRead();
    void run();


  private:
    QUdpSocket* listenerSocket;
    QHostAddress ip;
    quint16 port;

    QTimer      m_timerSend;
    int m_lasttime;
    void process(QByteArray buffer);


    QMutex mutex;

};

#endif // UdpSocketListener_H
