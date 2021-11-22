#include <iostream>

typedef struct {

    std::string name;
    std::string ad;
    float price;
    std::string output;

} Company;

float getSum(std::vector<Company>& array);

float getMin(std::vector<Company>& array);

bool isNumber(std::string input_number);

void createCompany(std::vector<Company>& array);

void showAds(std::vector<Company>& array, std::vector<std::string> ports);