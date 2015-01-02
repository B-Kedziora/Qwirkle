#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent, std::string* name, std::string* ip, signed short int* port) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    name_ = name;
    ip_ = ip;
    port_ = port;
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::enableStartButton()
{
    ui->StartButton->setEnabled(true);
}

void StartDialog::on_ExitButton_clicked()
{
    exit(0);
}

bool StartDialog::validateName(std::string name)
{
    return false;
}

bool StartDialog::validatePort(int port)
{
    return false;
}

bool StartDialog::validateIp(std::string ip)
{
    return false;
}

std::string StartDialog::getNonLocalIp()
{
    return "";
}

std::string StartDialog::concatIp()
{
    return "";
}


void StartDialog::on_StartButton_clicked()
{
    ui->infoText->setText("");

    std::string ip;
    std::string name;
    int port;

    bool dataValid = true;

    if(ui->hostRadio->isChecked()) {
        name = ui->hostNameEdit->text().toStdString();
        port = ui->portSpinBoxHost->value();
        ip = getNonLocalIp();
    } else if(ui->joinRadio->isChecked()) {
        name = ui->joinNameEdit->text().toStdString();
        port = ui->portSpinBoxJoin->value();
        ip = concatIp();
    } else {
        ui->infoText->setText("You must provide data to start.");
        return;
    }

    if(validateName(name)) {

    } else {
        ui->infoText->append("Name is not valid. Ensure that lenght of the name is between 3 and 15. Name must contain only ASCII symbols with exception of '.'\n");

        dataValid = false;
    }

    if(validatePort(port)) {

    } else {
        ui->infoText->append("Port is not valid. Choose port from range: 1024 to 65000\n");
        dataValid = false;
    }

    if(validateIp(ip)){

    } else {
        ui->infoText->append("IP is not valid. No such IP");
        dataValid = false;
    }

    if(dataValid) {

    }
}
