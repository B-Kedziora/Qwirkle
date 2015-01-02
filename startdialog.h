#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "connectiondata.h"
#include <string>
#include <iostream>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent, ConnectionData** connectionData);
    ~StartDialog();

private slots:
    void on_ExitButton_clicked();

    void on_StartButton_clicked();

    void on_hostNameEdit_editingFinished();

    void on_joinNameEdit_editingFinished();

private:
    Ui::StartDialog *ui;
    ConnectionData** connectionData;
    void enableStartButton();
    bool validateName(std::string name);
    bool validateIp(std::string ip);
    std::string getNonLocalIp();
    std::string concatIp();
};

#endif // STARTDIALOG_H
