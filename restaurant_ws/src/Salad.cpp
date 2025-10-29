#include "Salad.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Salad::Salad(std::string n, double p, double tb) {
    name = n;
    price = p;
    taste_balance = tb;
    hasTopping = false;
    topping = "";
}

void Salad::printInfo() const {
    std::cout << name << " - $" << price;
    if(hasTopping)
        std::cout << " (Topping: " << topping << " +$2.25)";
    std::cout << "\n";
}

void Salad::customize() {
    while(true) {
        std::string input;
        std::cout << "Do you want a topping for your salad? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") {
            hasTopping = true;
            std::cout << "Enter topping name: (1, 2, 3, 4, 5)";
            std::cin >> topping;
            price += 2.25;
            break;
        } else if(input == "no") {
            hasTopping = false;
            break;
        } else {
            std::cout << "Invalid input! Geçersiz karakter.\n";
        }
    }
}
