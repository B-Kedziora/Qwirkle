#include <QCoreApplication>
#include <iostream>
#include "qthread.h"
#include <stdio.h>
#include "../Commons/connectiondata.h"

int main(int argc, char *argv[])
{
    stdout = freopen("server.log", "w", stdout);

    if(argc == 2) {
        try{
            ConnectionData* cd = new ConnectionData(argv[1]);

        } catch(exception e) {
            cout<<"Invalid connection data "<<endl;
        }
    } else {
        cout<<"Server cannot be created due to lack of connection details passed as an argument"<<endl;
        return 1;
    }

    QThread::sleep(10000);
}
