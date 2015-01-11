#include "startdialog.h"
#include "ui_startdialog.h"

using namespace std;

StartDialog::StartDialog(ConnectionData** connectionData, bool* host, int* players):
    QDialog(NULL),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    this->connectionData = connectionData;
    this->hostGame = host;
    this->playersCount = players;
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
    string temp(ip, 0); // strtok removes seperators from original string. Copy.
    char *bt = strtok(const_cast<char*>(temp.c_str()), ".");  // Splits ip into bytes
    while (bt) {        //Single byte check
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

string StartDialog::concatIp()
{
    string ip = (ui->IP1Edit->text() + "." + ui->IP2Edit->text() +
              "." + ui->IP3Edit->text() + "." + ui->IP4Edit->text()).toStdString();
    return ip;
}


void StartDialog::on_StartButton_clicked()
{
    ui->infoText->setText("");

    string ip = concatIp();
    string name = ui->nameEdit->text().toStdString();;
    int port = ui->portSpinBox->value();;

    bool dataValid = true;

    if(ui->hostRadio->isChecked()) {
        *hostGame = true;
    } else if (ui->joinRadio->isChecked()) {
        *hostGame = false;
    } else {
        ui->infoText->append("Do you want to host or join the game?\n");
        dataValid = false;
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
        *connectionData = new ConnectionData(name, ip, (unsigned short) port);
        *playersCount = ui->playersCount->value();
        this->close();
    }
}

void StartDialog::on_hostRadio_clicked()
{
    ui->ipNameLabel->setText("Your IP:");
    ui->playersLabel->setEnabled(true);
    ui->playersCount->setEnabled(true);
}

void StartDialog::on_joinRadio_clicked()
{
    ui->ipNameLabel->setText("Server IP:");
    ui->playersLabel->setEnabled(false);
    ui->playersCount->setEnabled(false);
}
