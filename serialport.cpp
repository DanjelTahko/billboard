#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include "serialport.hpp"

using namespace std;

void printPortMeny() {

    cout << "\n ------------------------"  << endl;
    cout << "|   ** Serial Ports **   |" << endl;
    cout << "|  1. Show ports         |" << endl;
    cout << "|  2. Add port           |" << endl;
    cout << "|  3. Remove port        |" << endl;
    cout << "|  4. Back               |" << endl;
    cout << " ------------------------"  << endl << "-> ";

}

void printPort(string port, string word) {

    int serial_port = open(port.c_str(), O_RDWR);
    
    if (serial_port < 0) {
        cout << "* Arduino not found at : " << port << endl;  
    }
    
    sleep(2);
    write(serial_port, word.c_str(), word.size());
  
    close(serial_port);
}

void showports(vector<string>& ports) {

    for (int i = 0; i < ports.size(); i++){
        cout << "\n" << (i+1) << " - " << ports[i] << endl;
    }
}

void removePort(vector<string>& ports) {

    string input;

    while (1) {
        showports(ports);
        cout << "\nRemove port ->";
        cin >> input;

        try {
            int str_int = stoi(input);
            if (str_int > ports.size() || str_int == 0) {
                cout << "\nNo port found at " << input << endl;
            }
            else {
                ports.erase(std::next(ports.begin(), str_int-1));
                break;
            }
            throw;
        } 
        catch(...) {
            cout << "Only digits!" << endl;
        }
    }
}

int tryConnection(string port) {

    int serial_port = open(port.c_str(), O_RDWR);

    close(serial_port);
    
    return serial_port;

}

void changePorts(vector<string>& ports) {

    string port_name, choice;
    while (1) {

        printPortMeny();
        cin >> choice;

        if (choice == "1") {
            if (ports.size() > 0) {
                showports(ports);
            } else {
                cout << "\nNo ports found" << endl;
            }
        }
        else if (choice == "2") {
            cout << "PATH ->";
            cin >> port_name;
            if (tryConnection(port_name) < 0) {
                cout << "\nCan't find connection" << endl;
            } else {
                cout << "\nConnection found" << endl;
                ports.push_back(port_name);
            }
        }
        else if(choice == "3") {
            if (ports.size() > 0) {
                removePort(ports);
            } else {
                cout << "\nNo ports found" << endl; 
            }
        }
        else if (choice == "4") {
            break;
        }
        else {
            cout << "\nInvalid input" << endl;
        }

    }
}
