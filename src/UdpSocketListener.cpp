#include "UdpSocketListener.h"
#include <QDataStream>
#include "QDebug"
#include "QThread"
#include "QColor"
#include "QMutexLocker"
#include <QTextStream>
#include <QtCore/QTextCodec>
#include <iostream>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include "QDateTime"
#include "QMessageBox"
#include "QTime"
#include "QHostAddress"
#include "Data.h"


using namespace std;

/*!
    \class UdpSocketListener::UdpSocketListener

    \brief The UdpSocketListener class provides data from Tvico.
*/

UdpSocketListener::UdpSocketListener(int port) {
    ip.setAddress("127.0.0.1");
    this->port = static_cast<quint16>(port);
    listenerSocket = new QUdpSocket(this);
}

/*!
 \fn void UdpSocketListener::~UdpSocketListener()()

 Decostructor.
*/
UdpSocketListener::~UdpSocketListener() {
    delete listenerSocket;
    qDebug() << "Exit form ~UdpSocketListener";
}

/*!
 \fn void UdpSocketListener::run()

 Thread starting function.
*/

void UdpSocketListener::run() {
    qDebug() << "From UdpSocketListener: " << QThread::currentThreadId();

    if (!listenerSocket->bind(port))
        emit error("Socket can not created for: " + QString::number(port) + "-" + ip.toString());
    else
        qDebug() << "Socket Created: "  << QString::number(port) + "-" + ip.toString();

    connect(listenerSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    //emit printString("Socket Created.");
}


/*!
 \fn void UdpSocketListener::()


*/

void UdpSocketListener::readyRead() {
    // when data comes in
    QByteArray buffer;
    buffer.resize(listenerSocket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    listenerSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    qDebug() << "sender: " << sender << senderPort;
    qDebug() << "buffer size:" << buffer.data() << buffer.size();

    Data dataIn;

    QDataStream in(&buffer, QIODevice::ReadOnly);
    in >> dataIn;

    emit dataInSignal(dataIn);

}


///*!
// \fn void UdpSocketListener::()
//
//
//*/
//void UdpSocketListener::process(QByteArray buffer) {
//
//    if (buffer.size() >= 0 ) {
//        //QByteArray data;
//        Script script;
//
//        QDataStream in(&buffer, QIODevice::ReadOnly);
//        in >> script;
//        QString cmd = QString::fromStdString(buffer.data());
//        qDebug() << cmd;
////        std::cout << script;
//    }
//
//
//
//}




