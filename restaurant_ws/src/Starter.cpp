#include "Starter.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Starter::Starter(std::string n, double p, double tb, bool hot) {
    name = n;
    price = p;
    taste_balance = tb;
    isHot = hot;
}

void Starter::printInfo() const {
    std::cout << name << " - $" << price << " (" << (isHot ? "Hot" : "Cold") << ")\n";
}

void Starter::customize() {
    while(true) {
        std::string input;
        std::cout << "Do you want your starter hot or cold? (hot/cold): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "hot") {
            isHot = true;
            break;
        } else if(input == "cold") {
            isHot = false;
            break;
        } else {
            std::cout << "Invalid input! Geçersiz karakter.\n";
        }
    }
}
