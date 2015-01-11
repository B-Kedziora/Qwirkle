#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "Commons/connectiondata.h"
#include <string>
#include <iostream>
#include <connection.h>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(ConnectionData** connectionData, bool* host, int* players);
    ~StartDialog();

private slots:
    void on_ExitButton_clicked();

    void on_StartButton_clicked();

    void on_hostRadio_clicked();

    void on_joinRadio_clicked();

private:
    Ui::StartDialog *ui;
    ConnectionData** connectionData;
    bool* hostGame;
    int* playersCount;
    void enableStartButton();
    bool validateName(std::string name);
    bool validateIp(std::string ip);
    std::string concatIp();
};

#endif // STARTDIALOG_H
