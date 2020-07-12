/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   MainWindow.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/

#include <iostream>
#include <QtWidgets/QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ConfigParserUtil.h"
#include "Data.h"
#include "Node.h"
#include "UdpSocketSender.h"

MainWindow::MainWindow(const QString nodeName, QWidget *parent) :
    QMainWindow(parent),
    currentNodeName(nodeName),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedNode = nullptr;
    nodeListPtr = nullptr;
    udpSocketSenderListPtr = new QList<UdpSocketSender>();
    udpSocketListenerPtr = nullptr;
    udpSocketListenerThreadPtr = nullptr;

    ConfigParserUtil::getInstance();

    this->setWindowTitle(currentNodeName + " Main Application");

    connect(ui->startPushButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    //for debug
//    ConfigParserUtil::getInstance()->printNodes();

    initialize();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendDataToAll(const Data &sendingdata) {

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << sendingdata;

    for(auto& udpSocketSender : *udpSocketSenderListPtr){
        udpSocketSender.send(data);
    }

}

void MainWindow::initialize() {
    nodeListPtr = ConfigParserUtil::getInstance()->getNodeListPtr();
    selectedNode = findSelectedNode();

    initializeUdpSenderSockets();
    initializeUdpListenerSocket();


}

Node* MainWindow::findSelectedNode() {
    return findNode(currentNodeName);
}


void MainWindow::initializeUdpSenderSockets() {
    for(const QString& nodeToSend : *selectedNode->getNodesToSendPtr()){
        Node* node = findNode(nodeToSend);

        UdpSocketSender *udpSocketSenderPtr = new UdpSocketSender(node->getPort(),this);

//        UdpSocketSender udpSocketSender(node->getPort(),this);
        udpSocketSenderListPtr->append(*udpSocketSenderPtr);
    }



}

Node *MainWindow::findNode(const QString& nodeName) {
    for(Node& node: *nodeListPtr){
        if(nodeName == node.getName()){
            // found it.
            return &node;
        }
    }

    return nullptr;
}

void MainWindow::initializeUdpListenerSocket() {
    udpSocketListenerThreadPtr = new QThread();
    udpSocketListenerPtr = new UdpSocketListener(selectedNode->getPort());

    //Startup
    connect(udpSocketListenerThreadPtr, SIGNAL(started()), udpSocketListenerPtr, SLOT(run()));
    connect(udpSocketListenerPtr, SIGNAL(finished()), udpSocketListenerThreadPtr, SLOT(quit()));

    //automatically delete thread and task object when work is done:
    connect(udpSocketListenerPtr, SIGNAL(finished()), udpSocketListenerPtr, SLOT(deleteLater()));
    connect(udpSocketListenerThreadPtr, SIGNAL(finished()), udpSocketListenerThreadPtr, SLOT(deleteLater()));

    udpSocketListenerPtr->setParent(0);
    udpSocketListenerPtr->moveToThread(udpSocketListenerThreadPtr);
    udpSocketListenerThreadPtr->start();

    connect(udpSocketListenerPtr, SIGNAL(error(QString)), this, SLOT(slotErrorString(QString)));
    qRegisterMetaType<Data>("Data");
    connect(udpSocketListenerPtr, SIGNAL(dataInSignal(Data)), this, SLOT(dataInSlot(Data)),Qt::QueuedConnection);

}

void MainWindow::buttonClicked() {
    /*
     *         MN                                    SN
     *         SgNB Addition Request---------------->
     *           <------SgNB Addition Request Acknowledge
     *         SgNB Reconfiguration Complete-------->
     *
     */


    Data* sendingDataPtr = nullptr;
    if(selectedNode->getName() == "MN"){
        if(comingData.getNodeName() == "MN"){
            // the relatedNode is MN from coming data
            if(comingData.getSignal() == "SgNB Addition Request Acknowledge"){
                sendingDataPtr = prepareData("SN", "SgNB Reconfiguration Complete");
                ui->sendingtextEdit->setText("Sending SgNB Reconfiguration Complete to SN");
            }
        }else if(comingData.getNodeName() == "" && comingData.getSignal() == ""){
            // the first data to prepare to send
            sendingDataPtr = prepareData("SN", "SgNB Addition Request");
            ui->sendingtextEdit->setText("Sending SgNB Addition Request to SN");
        }
    }else if(selectedNode->getName() == "SN"){
        if(comingData.getNodeName() == "SN"){
            if(comingData.getSignal() == "SgNB Addition Request"){
                sendingDataPtr = prepareData("MN", "SgNB Addition Request Acknowledge");
                ui->sendingtextEdit->setText("Sending SgNB Addition Request Acknowledge to MN");

            }

        }
    }

    if(sendingDataPtr)
        sendDataToAll(*sendingDataPtr) ;
}

void MainWindow::slotErrorString(QString err) {
    qDebug() << "Error: " << err;
    QMessageBox::warning(this, tr("Error"),
                         err,
                         QMessageBox::Ok);
}

void MainWindow::dataInSlot(Data data) {
    qDebug() << "Data in:" << data.getNodeName();
    qDebug() << "Data in:" << data.getSignal();
    ui->receivingTextEdit->setText("Receiving "+data.getSignal() + " from " + data.getNodeName());
    comingData = data;
}

Data *MainWindow::prepareData(const QString &relatedNodeName, const QString &signal) {
    Data* dataPtr = new Data();
    dataPtr->setSignal(signal);
    dataPtr->setNodeName(relatedNodeName);

    return dataPtr;

}


