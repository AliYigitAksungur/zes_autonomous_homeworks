#include "MainCourse.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

MainCourse::MainCourse(std::string n, double p, double tb, bool veg) {
    name = n;
    price = p;
    taste_balance = tb;
    vegetarian = veg;
}

void MainCourse::printInfo() const {
    std::cout << name << " - $" << price << " (" << (vegetarian ? "Vegetarian" : "Non-Vegetarian") << ")\n";
}

void MainCourse::customize() {
    while(true) {
        std::string input;
        std::cout << "Do you want a vegetarian main course? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") {
            vegetarian = true;
            break;
        } else if(input == "no") {
            vegetarian = false;
            break;
        } else {
            std::cout << "Invalid input! Geçersiz karakter.\n";
        }
    }
}
