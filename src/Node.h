/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   Node.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/
#ifndef ULAKCOM_NODE_H
#define ULAKCOM_NODE_H


#include <QtCore/QString>
#include <ostream>

class Data;

class Node {
public:
    /*
     * VARIABLES
     */

    /*
     * FUNCTIONS
     */
    Node();

    Node(const QString &name, int port);

    ~Node();

    Node(const Node &other);

    Node &operator=(const Node &other);

    const QString &getName() const;

    void setName(const QString &name);

    int getPort() const;

    void setPort(int port);

    QList<QString> *getNodesToSendPtr() const;

    void setNodesToSendPtr(QList<QString> *nodesToSendPtr);

    friend std::ostream &operator<<(std::ostream &os, const Node &node);



private:
    /*
     * VARIABLES
     */
    QString name;
    int port;
    QList<QString> *nodesToSendPtr;

    /*
     * FUNCTIONS
     */



};


#endif //ULAKCOM_NODE_H
