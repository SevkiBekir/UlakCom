/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   MainWindow.h
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UdpSocketListener.h"

namespace Ui {
class MainWindow;
}

class Data;
class Node;
class UdpSocketSender;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString nodeName, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void buttonClicked();
    void slotErrorString(QString err);
    void dataInSlot(Data);



private:
    Ui::MainWindow *ui;
    QString currentNodeName;

    Node* selectedNode;
    QList<Node>* nodeListPtr;
    Data comingData;

    void sendDataToAll(const Data &sendingdata);
    void initialize();
    void initializeUdpSenderSockets();
    void initializeUdpListenerSocket();
    Node* findSelectedNode();
    Node* findNode(const QString& nodeName);
    Data* prepareData(const QString& relatedNodeName, const QString& signal);

    QList<UdpSocketSender> *udpSocketSenderListPtr;

    QThread* udpSocketListenerThreadPtr;
    UdpSocketListener *udpSocketListenerPtr;



};

#endif // MAINWINDOW_H
