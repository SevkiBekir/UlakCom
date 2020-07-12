#ifndef UdpSocketSender_H
#define UdpSocketSender_H

#include <QThread>
#include <QUdpSocket>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QDataStream>

#include <QMutex>

class UdpSocketSender : public QObject {
    Q_OBJECT
  public:
    explicit UdpSocketSender(const int& port, QObject *parent=0);
    UdpSocketSender(const UdpSocketSender& other);
    UdpSocketSender&operator=(const UdpSocketSender& other);
    ~UdpSocketSender();

    bool send(const QByteArray& data);

    QUdpSocket *getSocketSender() const;

    const QHostAddress &getIp() const;

    quint16 getPort() const;


signals:
    void error(QString);

  public slots:



  private:
    QUdpSocket* socketSender;
    QHostAddress ip;
    quint16 port;



    void initialize();

};

#endif // UdpSocketSender_H
