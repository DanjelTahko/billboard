#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

typedef struct {

    string name;
    string ad;
    int price;
    string output;

} Company;

void printPort(string word) {

    int serial_port = open("/dev/cu.usbmodem11401", O_RDWR);
    
    if (serial_port < 0) {
        cout << "Arduino not found" << endl;  
    }
    
    sleep(2);
    write(serial_port, word.c_str(), word.size());
  
    close(serial_port);

}

void createCompany(vector<Company>& array) {

    //Malloc ????
    string name, ad;
    int price;

    cout << "Company name ->";
    cin.ignore();
    getline(cin, name);

    cout << "Ad text -> "; 
    getline(cin, ad);

    cout << "Pay ->";
    cin >> price;

    while (price <= 0)
    {
        cout << "Invalid Input!" << endl;
        cout << "Pay ->";
        cin >> price;
    }

    array.push_back((Company){name, ad, price});

}

void showAds(vector<Company>& array) {

    float sum = 0.0;
    int time;

    if (array.size() == 0) {
        cout << "\nNo ads available" << endl;
    }

    for (int i = 0; i < array.size(); i++) {
        sum += array[i].price;
    }
    cout << " ------------------------"  << endl;
    cout << "| Showing ads on display |" << endl;
    cout << " ------------------------"  << endl;
    for (int k = 0; k < array.size(); k++) {
        time = (array[k].price / sum) * 60;
        string number = to_string(time);
        array[k].output = number + '-' + array[k].ad;
        
        printPort(array[k].output);
        cout << "Company : " << array[k].name << endl;
        cout << "Ad * " << array[k].ad << "\n" << endl;
        sleep(time);
    }
}

int main() {

    char choice;
    vector<Company> array;

    while (1) {
        
        cout << " ------------------------"  << endl;
        cout << "|  ** Billboard Menu **  |" << endl;
        cout << "|  1. Buy time           |" << endl;
        cout << "|  2. Show ads           |" << endl;
        cout << "|  3. Change ports       |" << endl;
        cout << "|  3. Quit               |" << endl;
        cout << " ------------------------"  << endl << "-> ";
        cin >> choice;
     
        if (choice == '1') {
            createCompany(array);
        }
        else if (choice == '2') {
            showAds(array);
        }
        else if (choice == '3') {
            break;
        }
        else {
            cout << "\nInvalid input" << endl;
        }
    }
    return 0;
}