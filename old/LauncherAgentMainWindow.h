/******************************************************************
*   HAVELSAN A.Ş
*
*   Project: CIVILSIM
*
*   File:   LauncherAgentMainWindow.cpp
*   Date:   7/02/20
*   Author: Sevki Kocadag
/*******************************************************************/

#ifndef LAUNCHERAGENTMAINWINDOW_H
#define LAUNCHERAGENTMAINWINDOW_H

#include <QMainWindow>
#include "UdpSocketListener.h"

namespace Ui {
class LauncherAgentMainWindow;
}

class LauncherAgentMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LauncherAgentMainWindow(QWidget *parent = 0);
    ~LauncherAgentMainWindow();

public slots:
    void sloterrorString(QString err);

private:
    Ui::LauncherAgentMainWindow *ui;

};

#endif // LAUNCHERAGENTMAINWINDOW_H
