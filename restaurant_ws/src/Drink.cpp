#include "Drink.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Drink::Drink(std::string n, double p, double tb) {
    name = n;
    price = p;
    taste_balance = tb;
    carbonated = false;
    extraShot = false;
}

void Drink::printInfo() const {
    std::cout << name << " - $" << price;
    if(carbonated) std::cout << " (Carbonated)";
    if(extraShot) std::cout << " (+Alcohol $2.5)";
    std::cout << "\n";
}

void Drink::customize() {
    while(true) {
        std::string input;
        std::cout << "Do you want your drink carbonated? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") { carbonated = true; break; }
        else if(input == "no") { carbonated = false; break; }
        else { std::cout << "Invalid input! Geçersiz karakter.\n"; }
    }

    while(true) {
        std::string input;
        std::cout << "Do you want extra alcohol shot? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") { extraShot = true; price += 2.5; break; }
        else if(input == "no") { extraShot = false; break; }
        else { std::cout << "Invalid input! Geçersiz karakter.\n"; }
    }
}
