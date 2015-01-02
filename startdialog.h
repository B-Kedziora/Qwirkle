#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent, std::string* name, std::string* ip, signed short int* port);
    ~StartDialog();

private slots:
    void on_ExitButton_clicked();

    void on_StartButton_clicked();

private:
    Ui::StartDialog *ui;
    std::string* name_;
    std::string* ip_;
    signed short int* port_;

    void enableStartButton();
    bool validateName(std::string name);
    bool validatePort(int port);
    bool validateIp(std::string ip);
    std::string getNonLocalIp();
    std::string concatIp();
};

#endif // STARTDIALOG_H
