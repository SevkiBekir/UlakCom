#include "Communication.h"




//
//#include <hvlsim/simbase/output/Logger.h>
//#include <QtNetwork/QUdpSocket>
//#include "NetworkInfo.h"
//#include "Script.h"
//
//
//Communication::Communication(const NetworkInfo &networkInfo, Enumarators::CommunicationType communicationType) {
//
//
//    this->ip = networkInfo.getIp().toStdString();
//    this->port = networkInfo.getPort();
//    this->communicationType = communicationType;
//    isSocketOpened = false;
//    udpSocketPtr= nullptr;
//
//}
//
//
//Communication::~Communication() {
//    delete udpSocketPtr;
//}
//
//Communication::Communication(const Communication &other) {
//
//    port = other.getPort();
//    ip = other.getIp();
//    communicationType = other.getCommunicationType();
//
//}
//
//bool Communication::createSocket() {
//    if (this->communicationType == Enumarators::CommunicationType::communication_Receiver) {
//        udpSocketPtr = new hvlsim::simbase::UdpSocket(hvlsim::simbase::tconnecttype_RECEIVER);
//        udpSocketPtr->setLocalIP(ip.c_str());
//        udpSocketPtr->setLocalPort(port);
//        SIM_INFO("Receiver communication set up");
//
//
//    } else if (this->communicationType == Enumarators::CommunicationType::communication_Sender) {
//        udpSocketPtr = new hvlsim::simbase::UdpSocket(hvlsim::simbase::tconnecttype_SENDER);
//        udpSocketPtr->setRemoteIP(ip.c_str());
//        udpSocketPtr->setRemotePort(port);
//        SIM_INFO("Sender communication set up");
//    }
//
//
//    udpSocketPtr->setSizeControl(false);
//    bool result = udpSocketPtr->IsAnyError();
//
//    return result;
//}
//
//int Communication::getPort() const {
//    return port;
//}
//
//const std::string &Communication::getIp() const {
//    return ip;
//}
//
//hvlsim::simbase::UdpSocket *Communication::getUdpSocketPtr() const {
//    return udpSocketPtr;
//}
//
//Enumarators::CommunicationType Communication::getCommunicationType() const {
//    return communicationType;
//}
//
//void Communication::initialize() {
//    createSocket();
//    isSocketOpened = openSocket();
//}
//
//bool Communication::openSocket() {
//    int result = udpSocketPtr->Open();
//
//    return result > 0;
//}
//
//Communication &Communication::operator=(const Communication &other) {
//
//    if (this != &other) {
//        port = other.getPort();
//        ip = other.getIp();
//        communicationType = other.getCommunicationType();
//    }
//
//    return *this;
//}
//
//bool Communication::operator==(const Communication &rhs) const {
//    return port == rhs.port &&
//           ip == rhs.ip;
//}
//
//bool Communication::operator!=(const Communication &rhs) const {
//    return !(rhs == *this);
//}
//
//bool Communication::sendAgentToRun(Script *scriptPtr) {
//    qDebug() << scriptPtr->getType();
//    qDebug() << scriptPtr->getArguments();
//    qDebug() << scriptPtr->getApplication();
//    QUdpSocket *socket = new QUdpSocket();
//    QHostAddress qHostAddress;
//    QString ipAddress = QString::fromUtf8(ip.c_str());
//    qHostAddress.setAddress(ipAddress);
//    socket->bind(qHostAddress,port);
//
//    QByteArray data;
//    QDataStream out(&data, QIODevice::WriteOnly);
//    out << *scriptPtr;
//
//    socket->writeDatagram(data,qHostAddress,port);
//    socket->close();
//
//
////    if(!isSocketOpened)
////        initialize();
////
////    int sentPacketSize = 0;
////
////    uint packetSize = sizeof(*scriptPtr);
////    sentPacketSize = udpSocketPtr->Send((hvlsim::simUByte *) scriptPtr, packetSize);
////
////    bool result = sentPacketSize == packetSize;
////    if (result) {
////        std::cout << "packet loss while sending" << std::endl;
////    } else {
////        std::cout << "no packet loss while sending " << std::endl;
////
////    }
////
////    return  result;
//}
//
//void Communication::closeSocket() {
//    udpSocketPtr->Close();
//
//}

//
//int Communication::receiveFromDiscreteAnalogIF(int requestedSize, DataIn* dataInPtr) {
//
//    int receivedSize = 0;
//    if(requestedSize){
//        receivedSize = udpSocketPtr->ReceiveAndReturnSize((hvlsim::simUByte *) dataInPtr,  (sizeof(*dataInPtr)));
//    }
//
//    return receivedSize;
//
//}
//
//void Communication::receiveFromCalibrationTool(int requestedSize, DataOut* dataSender){
//    int receivedSize = 0;
//    if(requestedSize){
//        receivedSize = udpSocketPtr->ReceiveAndReturnSize((hvlsim::simUByte *) dataSender, (sizeof(DataOut)));
//        if(receivedSize  < requestedSize){
//            std::cout << "packet loss while receiving" << std::endl;
//        }else{
//            std::cout << "no packet loss while receiving" << std::endl;
//
//        }
//    }
//}
//
//
//void Communication::sendToDiscreteAnalogIF(uint32_t packetNumberToSend, DataOut *sendData) {
//    uint32_t sentPacketSize = 0;
//
//    // if there is a packet to send
//    if(packetNumberToSend){
//        sentPacketSize = udpSocketPtr->Send((hvlsim::simUByte *) sendData, sizeof(DataOut) * packetNumberToSend);
//        if(sentPacketSize < packetNumberToSend){
//            std::cout << "packet loss while sending"  << std::endl;
//        }else{
//            std::cout << "no packet loss while sending " << std::endl;
//
//        }
//    }
//}
//
Communication::Communication(const NetworkInfo &networkInfo, Enumarators::CommunicationType communicationType,
                             QObject *parent) : QObject(parent),
                                                networkInfo(networkInfo) {

    udpSocketSenderPtr = nullptr;
    udpSocketListenerPtr = nullptr;
    udpSocketListenerThreadPtr = nullptr;
    this->communicationType = communicationType;
    isInitialized = false;
}

void Communication::initialize() {
    if (!isInitialized) {
        if (communicationType == Enumarators::CommunicationType::communication_Sender) {
            udpSocketSenderPtr = new UdpSocketSender(networkInfo, this);
            isInitialized = true;
        }else if(communicationType == Enumarators::CommunicationType::communication_Receiver){
            udpSocketListenerThreadPtr = new QThread();
            udpSocketListenerPtr = new UdpSocketListener(networkInfo);
            isInitialized = true;

            //Startup
            connect(udpSocketListenerThreadPtr, SIGNAL(started()), udpSocketListenerPtr, SLOT(run()));
            connect(udpSocketListenerPtr, SIGNAL(finished()), udpSocketListenerThreadPtr, SLOT(quit()));

            //automatically delete thread and task object when work is done:
            connect(udpSocketListenerPtr, SIGNAL(finished()), udpSocketListenerPtr, SLOT(deleteLater()));
            connect(udpSocketListenerThreadPtr, SIGNAL(finished()), udpSocketListenerThreadPtr, SLOT(deleteLater()));

            udpSocketListenerPtr->setParent(0);
            udpSocketListenerPtr->moveToThread(udpSocketListenerThreadPtr);
            udpSocketListenerThreadPtr->start();

        }
    }

}

Communication::~Communication() {
    delete udpSocketSenderPtr;

}

bool Communication::sendAgentToRun(Script *scriptPtr) {
    if(!isInitialized){
        initialize();
    }
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << *scriptPtr;

    udpSocketSenderPtr->send(data);
}

void Communication::receiveScriptFromLauncher() {
    if(!isInitialized){
        initialize();
    }


}
