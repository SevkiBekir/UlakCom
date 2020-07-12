/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   ConfigParserUtil.h
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/

#ifndef ULAKCOM_CONFIGPARSERUTIL_H
#define ULAKCOM_CONFIGPARSERUTIL_H


#include <QtCore/QString>
#include <boost/property_tree/ptree.hpp>
#include "Node.h"

class ConfigParserUtil {
public:
    static ConfigParserUtil* getInstance();

    const QString &getProjectPath() const;
    const boost::property_tree::ptree &getXmlTree() const;

    QList<Node> *getNodeListPtr() const;
    void printNodes();


private:
    ConfigParserUtil();
    ~ConfigParserUtil();
    ConfigParserUtil& operator=(ConfigParserUtil const&){};
    ConfigParserUtil(ConfigParserUtil const&){};

    void readAppConfigXml();
    void parseAppConfigXml();
    void initialize();
    void parseNodes();



    static ConfigParserUtil *instance;

    QString configPath;
    QString projectPath;
    boost::property_tree::ptree xmlTree;

    QList<Node>* nodeListPtr;


};


#endif //ULAKCOM_CONFIGPARSERUTIL_H
