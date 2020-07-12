/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   Node.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/
#include "Node.h"
#include <QStringList>
#include "Data.h"
#include "QDataStream"

Node::Node() {
    name = "";
    port = -1;
    nodesToSendPtr = new QList<QString>();
}

Node::~Node() {
    delete nodesToSendPtr;
}

Node::Node(const Node &other) {
    name = other.getName();
    port = other.getPort();
    nodesToSendPtr = new QList<QString>(*other.getNodesToSendPtr());
}

Node &Node::operator=(const Node &other) {
    if (this != &other) {
        name = other.getName();
        port = other.getPort();
        nodesToSendPtr = new QList<QString>(*other.getNodesToSendPtr());

    }
    return *this;
}

Node::Node(const QString &name, int port) : name(name), port(port) {
    nodesToSendPtr = new QList<QString>();


}

const QString &Node::getName() const {
    return name;
}

void Node::setName(const QString &name) {
    Node::name = name;
}

int Node::getPort() const {
    return port;
}

void Node::setPort(int port) {
    Node::port = port;
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "-- NODE --" << std::endl;
    os << "name: " << node.name.toStdString() << " port: " << node.port << std::endl;
    for(QString& nodeItem:*node.nodesToSendPtr){
        os << "sending nodes: " << nodeItem.toStdString() << std::endl;

    }
    return os;
}

QList<QString> *Node::getNodesToSendPtr() const {
    return nodesToSendPtr;
}

void Node::setNodesToSendPtr(QList<QString> *nodesToSendPtr) {
    Node::nodesToSendPtr = nodesToSendPtr;
}



