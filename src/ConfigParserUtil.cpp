/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   ConfigParserUtil.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include "ConfigParserUtil.h"
#include "qdir.h"
#include <QVector>
#include <QDebug>
#include <iostream>

// Global static pointer used to ensure a single instance of the class.
ConfigParserUtil *ConfigParserUtil::instance = NULL;


ConfigParserUtil::ConfigParserUtil() {
    projectPath = ".."; // for development computer

    initialize();
}

ConfigParserUtil::~ConfigParserUtil() {

}

ConfigParserUtil *ConfigParserUtil::getInstance() {
    if (!instance) {
        instance = new ConfigParserUtil();
    }
    return instance;
}


void ConfigParserUtil::readAppConfigXml() {
    configPath = projectPath + "/cfg";

#ifdef _WINDOWS
    configPath.replace("\\", "/");
    QDir::toNativeSeparators(configPath);
#endif // _WINDOWS


    QString fileName = "/config.xml";
    configPath += fileName;


    boost::property_tree::read_xml(configPath.toStdString(), xmlTree);

}

const boost::property_tree::ptree &ConfigParserUtil::getXmlTree() const {
    return xmlTree;
}

const QString &ConfigParserUtil::getProjectPath() const {
    return projectPath;
}


void ConfigParserUtil::parseAppConfigXml() {
    parseNodes();

}

void ConfigParserUtil::initialize() {
    nodeListPtr = new QList<Node>();


    readAppConfigXml();
    parseAppConfigXml();
}

QList<Node> *ConfigParserUtil::getNodeListPtr() const {
    return nodeListPtr;
}

void ConfigParserUtil::parseNodes() {

    using boost::property_tree::ptree;

    for(ptree::value_type const& v: xmlTree.get_child("configs.nodes")) {
        // guard
        if (v.first == "node") {
            QString name = QString::fromStdString(v.second.get<std::string>("name"));
            int port = v.second.get<int>("port");

            Node* node = new Node(name,port);

            for(ptree::value_type const& vNodeToSend: v.second.get_child("nodesToSend")) {
                if (v.first == "node") {
                    QString nameOfNode = QString::fromStdString(vNodeToSend.second.get<std::string>("<xmlattr>.name"));
                    node->getNodesToSendPtr()->append(nameOfNode);
                }
            }

            nodeListPtr->push_back(*node);
        }
    }

}

void ConfigParserUtil::printNodes() {
    for(const Node& node: *nodeListPtr){
        std::cout << node;
    }
}





