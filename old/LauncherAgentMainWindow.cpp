/******************************************************************
*   HAVELSAN A.Ş
*
*   Project: CIVILSIM
*
*   File:   LauncherAgentMainWindow.cpp
*   Date:   7/02/20
*   Author: Sevki Kocadag
/*******************************************************************/

#include <QtWidgets/QMessageBox>
#include "LauncherAgentMainWindow.h"
#include "ui_LauncherAgentMainWindow.h"
#include "Communication.h"
#include "NetworkInfo.h"
#include "Script.h"

LauncherAgentMainWindow::LauncherAgentMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::LauncherAgentMainWindow) {
    ui->setupUi(this);

    this->setWindowTitle("Agent");

    Communication *communication = new Communication(NetworkInfo("127.0.0.1",12346),Enumarators::CommunicationType::communication_Receiver);
    communication->receiveScriptFromLauncher();

    ///UDP AGENT LISTENER
    //Error from Thread
//    connect(udpSocketListener, SIGNAL(error(QString)), this, SLOT(sloterrorString(QString)));
//    //Startup
//    connect(thr_udpSocketListener, SIGNAL(started()), udpSocketListener, SLOT(run()));
//    connect(udpSocketListener, SIGNAL(finished()), thr_udpSocketListener, SLOT(quit()));
//
//    //automatically delete thread and task object when work is done:
//    connect(udpSocketListener, SIGNAL(finished()), udpSocketListener, SLOT(deleteLater()));
//    connect(thr_udpSocketListener, SIGNAL(finished()), thr_udpSocketListener, SLOT(deleteLater()));
//
////    connect(udpSocketListener, SIGNAL(runApplication(int, QString,QString,QString)), this, SLOT(runApplication(int,QString,QString,QString)));
////    connect(udpSocketListener, SIGNAL(killApplication(QString)), this, SLOT(killApplication(QString)));
//
////    connect(this, SIGNAL(signalsend(QString, QByteArray)), udpSocketListener, SLOT(slotsend(QString, QByteArray)));
//
//
//    udpSocketListener->setParent(0);
//    udpSocketListener->moveToThread(thr_udpSocketListener);
//    thr_udpSocketListener->start();


//    NetworkInfo networkInfo("127.0.0.1", 12346);
//    Communication *receiverCommunicationPtr = new Communication(networkInfo,
//                                                                Enumarators::CommunicationType::communication_Receiver);
//    bool received = false;
//    Script *comingScriptPtr = nullptr; //new Script();
//    while (!received) {
//        received = receiverCommunicationPtr->receiveScriptFromLauncher(comingScriptPtr);
//
//    }
}

void LauncherAgentMainWindow::sloterrorString(QString err) {
    qDebug() << "Error: " << err;
    QMessageBox::warning(this, tr("Error"),
                         err,
                         QMessageBox::Ok);
    //logger->slotLogtoSystem("Error:" + err);
}

LauncherAgentMainWindow::~LauncherAgentMainWindow() {
    delete ui;
}
