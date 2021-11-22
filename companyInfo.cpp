#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include "companyInfo.hpp"
#include "serialport.hpp"

using namespace std;

float getSum(vector<Company>& array) {

    float sum = 0.00;

    for (int i = 0; i < array.size(); i++) {
        sum += array[i].price;
    }

    return sum;
}

float getMin(vector<Company>& array) {

    float min = 0.00;

    for (int i = 0; i < array.size(); i++) {

        if (min == 0.00) {
            min = array[i].price / 0.15;
        }
        else if (min > (array[i].price / 0.15)) {
            min = array[i].price / 0.15;
        }
    }
    return min;
}

bool isNumber(string input_number)
{
    for (int i =0; i < input_number.size(); i++) {
        if (isdigit(input_number[i]) == 0){
            return false;
        }
    }
    return true;
}

void createCompany(vector<Company>& array) {

    string name, ad, price;
    float price_to_f = 0.00;
    bool space = true;

    float sum = getSum(array);
    float min = getMin(array);
    float max_price = min - sum;
    float new_seconds = max_price / min;
    

    if (array.size() != 0) {

        if (new_seconds >= 0.15) {
            cout << "MAX PRICE : " << max_price << "kr" << endl;
        } else {
            cout << "\nNo spots available at the moment" << endl;
            space = false;
        }
    }

    if (space) {
        cout << "Company name ->";
        cin.ignore();
        getline(cin, name);

        cout << "Ad text -> "; 
        getline(cin, ad);

        while (ad.size() > 30) {
            cout << "* Max 30 characters!" << endl;
            cout << "You wrote " << ad.size() << " characters.." << endl;
            cout << "Ad text -> "; 
            getline(cin, ad);
        }

        while (1) {
            cout << "Pay ->";
            cin >> price;

            if (! isNumber(price)) {
                cout << "\nYou can't buy ads with words..\n" << endl;
            } else {
                price_to_f = stof(price);
                float checkSeconds = price_to_f/(price_to_f + sum);

                if (price_to_f <= 0) {
                    cout << "\nInvalid input! You have to pay something!" << endl;
                } else if (checkSeconds < 0.15) {
                    cout << "\nToo low! Ad will only be shown for " << checkSeconds*60 << " seconds" << endl;
                    cout << "Has to be atleast 9 seconds." << endl;
                } else if (array.size() != 0 && price_to_f > max_price) {
                    cout << "\nToo high!!! You can only pay max " << max_price << "kr" << endl;
                } else {
                    array.push_back((Company){name, ad, price_to_f});
                    break;
                }
            }
        }
    }
}

void showAds(vector<Company>& array, vector<string> ports) {

    float sum = 0.0;
    int time;

    if (array.size() == 0) {
        cout << "\nNo ads available" << endl;
    }
    else  {
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

            // Sends ads to all arduinos
            for (int p = 0; p < ports.size(); p++) {
                printPort(ports[p], array[k].output);        
            }
            // Prints info in terminal 
            cout << "Company : " << array[k].name << endl;
            cout << "Ad * " << array[k].ad << endl;
            cout << "Visible in " << time << " seconds\n" << endl;
            sleep(time);
        }
        // Removes all ads
        while(array.size() > 0) {
            array.pop_back();
        } 
    }
}