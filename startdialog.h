#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "Commons/connectiondata.h"
#include <string>
#include <iostream>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent, ConnectionData** connectionData, bool* host);
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
    void enableStartButton();
    bool validateName(std::string name);
    bool validateIp(std::string ip);
    std::string concatIp();
};

#endif // STARTDIALOG_H
