#include "Dessert.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Dessert::Dessert(std::string n, double p, double tb) {
    name = n;
    price = p;
    taste_balance = tb;
    extraChocolate = false;
}

void Dessert::printInfo() const {
    std::cout << name << " - $" << price;
    if(extraChocolate) std::cout << " (+Chocolate $1.5)";
    std::cout << "\n";
}

void Dessert::customize() {
    while(true) {
        std::string input;
        std::cout << "Do you want extra chocolate? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") { extraChocolate = true; price += 1.5; break; }
        else if(input == "no") { extraChocolate = false; break; }
        else { std::cout << "Invalid input! Geçersiz karakter.\n"; }
    }
}
