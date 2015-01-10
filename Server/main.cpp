#include <iostream>
#include <iostream>
#include <stdio.h>
#include "../Commons/connectiondata.h"
#include "../Commons/utils.h"
#include "qwirkleserver.h"

using namespace std;

int main(int argc, char *argv[])
{
    stdout = freopen("server.log", "w", stdout);

        cout<<"Running server..."<<endl;

        if(argc == 3) {
            ConnectionData* cd;
            int players;

            try{
                cd = new ConnectionData(argv[1]);
                players = stoi(argv[2]);
            } catch(exception e) {
                cout<<"Invalid connection data "<<e.what()<<endl;
                return 2;
            }

            Utils::printDate();
            cout<< "\nSerwer process started with data: "<<endl;
            cout<< cd->toString();
            cout<< "Players: " << players << endl;
            //new QwirkleServer(cd, players);

        } else {
            cout<<"Server cannot be created due to lack of connection details passed as an argument"<<endl;
            return 1;
        }
    return 0;
}

