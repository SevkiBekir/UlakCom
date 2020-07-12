#include "UdpSocketSender.h"

UdpSocketSender::UdpSocketSender(const int& port, QObject *parent): QObject(parent) {
    ip.setAddress("127.0.0.1");
    this->port = static_cast<quint16>(port);

    socketSender = new QUdpSocket(this);
    initialize();

}

UdpSocketSender::~UdpSocketSender() {

}

void UdpSocketSender::initialize() {
    qDebug() << "From UdpSocketSender: " << QThread::currentThreadId();

    int senderPort = port + 1;
    if (!socketSender->bind(ip,senderPort))
        emit error(tr("Socket can not created for: ") + QString::number(port) + "-" + ip.toString());
    else
        qDebug() << "Socket Created: "  << QString::number(senderPort) + "-" + ip.toString();


}

bool UdpSocketSender::send(const QByteArray& data){
    qint64 byteswitten;
    byteswitten = socketSender->writeDatagram(data, ip, port);

    qDebug()<<"Bytes Written :"<<byteswitten <<data.size();
    if (byteswitten < 0){
        emit error(tr("Unable to write datagram"));
        return false;
    }

    return true;
}

UdpSocketSender::UdpSocketSender(const UdpSocketSender &other) {
    this->setParent(other.parent());
    port = other.getPort();
    ip = other.getIp();
    socketSender = other.getSocketSender();

}

QUdpSocket *UdpSocketSender::getSocketSender() const {
    return socketSender;
}

const QHostAddress &UdpSocketSender::getIp() const {
    return ip;
}

quint16 UdpSocketSender::getPort() const {
    return port;
}

UdpSocketSender &UdpSocketSender::operator=(const UdpSocketSender &other) {
    if(this != &other){
        this->setParent(other.parent());
        port = other.getPort();
        ip = other.getIp();
        socketSender = other.getSocketSender();
    }

    return *this;
}

