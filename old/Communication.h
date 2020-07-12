#ifndef UTIL_IOCALIBRATIONTOOL_COMMUNICATION_H
#define UTIL_IOCALIBRATIONTOOL_COMMUNICATION_H


#include <string>
#include <QtCore/QObject>

#include "Definitions.h"
#include "NetworkInfo.h"
#include "UdpSocketSender.h"
#include "Script.h"
#include "UdpSocketListener.h"

class Communication : public QObject{
    Q_OBJECT

private:
    /*
     * VARIABLES
     */
    NetworkInfo networkInfo;
    UdpSocketSender *udpSocketSenderPtr;
    Enumarators::CommunicationType communicationType;
    bool isInitialized;

    QThread* udpSocketListenerThreadPtr;
    UdpSocketListener *udpSocketListenerPtr;

    /*
     * FUNCTIONS
     */

signals:

private slots:


public slots:


public:
    /*
     * VARIABLES
     */


    /*
     * FUNCTIONS
     */
    explicit Communication(const NetworkInfo &networkInfo, Enumarators::CommunicationType communicationType,QObject* parent = 0);

    virtual ~Communication();

    bool sendAgentToRun(Script *scriptPtr);

    void initialize();

    void receiveScriptFromLauncher();
};




//#include <hvlsim/simbase/network/UdpSocket.h>
//#include <hvlsim/simbase/network/BaseSocket.h>
//#include <hvlsim/simbase/definitions.h>

//class NetworkInfo;
//class Script;
//
//class Communication {
//public:
//    Communication(const NetworkInfo &networkInfo, Enumarators::CommunicationType communicationType);
//    ~Communication();
//    Communication(const Communication& other);
//    Communication&operator=(const Communication& other);
//
//    void receiveApplicationStatus();
//
//    void sendApplicationStatusToLauncher();
//
//    int getPort() const;
//
//    const std::string &getIp() const;
//
//    hvlsim::simbase::UdpSocket *getUdpSocketPtr() const;
//
//    Enumarators::CommunicationType getCommunicationType() const;
//
//    bool operator==(const Communication &rhs) const;
//
//    bool operator!=(const Communication &rhs) const;
//
//    bool sendAgentToRun(Script *scriptPtr);
//
//    void closeSocket();
//
//
////    void sendToDiscreteAnalogIF(uint32_t packetNumberToSend , DataOut *sendData);
////    int receiveFromDiscreteAnalogIF(int requestedSize, DataIn* dataInPtr);
////    void receiveFromCalibrationTool(int requestedSize, DataOut *dataSender);
//
//private:
//    int port;
//    std::string ip;
//
//    hvlsim::simbase::UdpSocket *udpSocketPtr;
//    Enumarators::CommunicationType communicationType;
//    bool isSocketOpened;
//
//    bool createSocket();
//    void initialize();
//
//    bool openSocket();
//
//};


#endif //UTIL_IOCALIBRATIONTOOL_COMMUNICATION_H
