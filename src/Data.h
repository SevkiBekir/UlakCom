/******************************************************************
*   HAVELSAN A.Ş
*
*   Project: CIVILSIM
*
*   File:   Data.h
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/
#ifndef ULAKCOM_DATA_H
#define ULAKCOM_DATA_H


#include <QtCore/QString>
#include <ostream>

class Data {
public:
    /*
     * VARIABLES
     */

    /*
     * FUNCTIONS
     */
    Data();

    ~Data();

    Data(const Data &other);

    Data &operator=(const Data &other);

    const QString &getNodeName() const;

    void setNodeName(const QString &nodeName);

    const QString &getSignal() const;

    void setSignal(const QString &signal);

    friend std::ostream &operator<<(std::ostream &os, const Data &data);
    friend QDataStream& operator>>(QDataStream& in, Data& data);
    friend QDataStream& operator<<(QDataStream& out, const Data& data);

private:
    /*
     * VARIABLES
     */
    QString nodeName;
    QString signal;

    /*
     * FUNCTIONS
     */



};


#endif //ULAKCOM_DATA_H
