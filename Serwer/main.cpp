#include <QCoreApplication>
#include <iostream>
#include "qthread.h"
#include <stdio.h>
#include "../Commons/connectiondata.h"
#include "../Commons/utils.h"

int main(int argc, char *argv[])
{
    stdout = freopen("server.log", "w", stdout);

    if(argc == 3) {
        try{
            ConnectionData* cd = new ConnectionData(argv[1]);
            int players = stoi(argv[2]);

            cout<< Utils::getDate() <<endl;
            cout<< "\nSerwer process started with data: "<<endl;
            cout<< cd->toString();
            cout<< "Players: " << players << endl;

            QwirkleServer server = new QwirkleServer(cd, players);
        } catch(exception e) {
            cout<<"Invalid connection data "<<endl;
            return 2;
        }
    } else {
        cout<<"Server cannot be created due to lack of connection details passed as an argument"<<endl;
        return 1;
    }

    return 0;
}
