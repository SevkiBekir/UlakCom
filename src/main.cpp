/******************************************************************
*   ULAK HABERLESME A.S.
*
*   Project: UlakCom
*
*   File:   Node.cpp
*   Date:   7/11/20
*   Author: Sevki Kocadag
/*******************************************************************/

#include "MainWindow.h"
#include <QApplication>
#include <iostream>
#include <QtCore/QCommandLineParser>
#include <QDebug>
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
                    context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
                    context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
                    context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
                    context.function);
            abort();
        default:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
                    context.function);
            break;
    }
}


int main(int argc, char *argv[]) {
    qInstallMessageHandler(messageHandler);


    QApplication a(argc, argv);
    QApplication::setApplicationName("UlakCom");
    QApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Description: This is example of console application");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption nameOption("n", "name of the node", "name", "MN");
    parser.addOption(nameOption);

    parser.process(a);

    QString nodeName = "";

    if (parser.isSet(nameOption)) {
        nodeName = parser.value(nameOption);

    }

//
//    for (const QString &arg: a.arguments()) {
//        qDebug() << arg;
//    }

    MainWindow w(nodeName);
    w.show();

    std::cout << "main" << std::endl;

    return a.exec();
}
