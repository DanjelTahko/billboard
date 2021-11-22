#include <iostream>
#include <vector>
#include "companyInfo.hpp"
#include "serialport.hpp"

using namespace std;

void printMainMeny() {

    cout << "\n ------------------------"  << endl;
    cout << "|  ** Billboard Menu **  |" << endl;
    cout << "|------------------------|"  << endl;
    cout << "|  1. Buy time           |" << endl;
    cout << "|  2. Upload ads         |" << endl; 
    cout << "|  3. Change ports       |" << endl;
    cout << "|  4. Quit               |" << endl;
    cout << " ------------------------"  << endl << "-> ";
}

int main() {

    string choice; 
    vector<Company> array;
    vector<string> ports;

    while (1) {
        
        printMainMeny();
        cin >> choice;
     
        if (choice == "1") {
            createCompany(array);
        }
        else if (choice == "2") {
            if (ports.size() >= 1) {
                showAds(array, ports);
            } else {
                cout << "\nNo serial ports found" << endl;
            }   
        }
        else if(choice == "3") {
            changePorts(ports);
        }
        else if (choice == "4") {
            break;
        }
        else {
            cout << "\nInvalid input" << endl;
        }
    }
    return 0;
}
