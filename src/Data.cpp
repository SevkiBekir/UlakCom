/******************************************************************
*   HAVELSAN A.Ş
*
*   Project: CIVILSIM
*
*   File:   Data.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/
#include "Data.h"


Data::Data() {
    signal = "";
    nodeName = "";
}

Data::~Data() {

}

Data::Data(const Data &other) {
    signal = other.getSignal();
    nodeName = other.getNodeName();
}

Data &Data::operator=(const Data &other) {
    if (this != &other) {
        signal = other.getSignal();
        nodeName = other.getNodeName();
    }
    return *this;
}

const QString &Data::getNodeName() const {
    return nodeName;
}

void Data::setNodeName(const QString &nodeName) {
    Data::nodeName = nodeName;
}

const QString &Data::getSignal() const {
    return signal;
}

void Data::setSignal(const QString &signal) {
    Data::signal = signal;
}

std::ostream &operator<<(std::ostream &os, const Data &data) {
    os << "nodeName: " << data.nodeName.toStdString() << " signal: " << data.signal.toStdString();
    return os;
}


QDataStream &operator<<(QDataStream &out, const Data &data) {
    out << data.nodeName
        << data.signal;

    return out;
}

QDataStream &operator>>(QDataStream &in, Data &data) {
    in >> data.nodeName
       >> data.signal;

    return in;
}