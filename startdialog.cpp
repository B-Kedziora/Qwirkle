#include "startdialog.h"
#include "ui_startdialog.h"

using namespace std;

StartDialog::StartDialog(QWidget *parent, ConnectionData* connectionData) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    this->connectionData = connectionData;
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

bool StartDialog::validateName(string name)
{
    if(name.length() > 2 && name.length() < 16 && name.find(".") == string::npos) {
        return true;
    } else {
        return false;
    }
}

bool StartDialog::validateIp(string ip)
{
    int bytesCount = 0;
    short byte;
    char *bt = strtok(const_cast<char*>(ip.c_str()), ".");  // Splits ip into bytes
    while (bt) {    //Single byte check
        bytesCount++;
        try{
            byte = stoi(string(bt));
        } catch(exception e) {
            return false;
        }

        if(byte < 0 || byte > 255)
            return false;
        bt = strtok(NULL, ".");
    }

    if(bytesCount == 4)
        return true;
    else
        return false;
}

string StartDialog::getNonLocalIp()
{
    return "";
}

string StartDialog::concatIp()
{
    string ip = (ui->IP1Edit->text() + "." + ui->IP2Edit->text() +
              "." + ui->IP3Edit->text() + "." + ui->IP4Edit->text()).toStdString();
    return ip;
}


void StartDialog::on_StartButton_clicked()
{
    ui->infoText->setText("");

    string ip;
    string name;
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

    if(!validateName(name)) {
        ui->infoText->append("Name is not valid. Ensure that lenght of the name is between 3 and 15. Name must contain only ASCII symbols with exception of '.'\n");
        dataValid = false;
    }

    if(!validateIp(ip)) {
        ui->infoText->append("IP is not valid. No such IP");
        dataValid = false;
    }

    if(dataValid) {
        connectionData = new ConnectionData(name, ip, (unsigned short) port);
        this->close();
    }
}

void StartDialog::on_hostNameEdit_editingFinished()
{
    ui->hostRadio->setChecked(true);
}

void StartDialog::on_joinNameEdit_editingFinished()
{
    ui->joinRadio->setChecked(true);
}
