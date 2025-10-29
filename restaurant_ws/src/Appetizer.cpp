#include "Appetizer.h"
#include <iostream>
#include <algorithm>

using namespace menu;

inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Appetizer::Appetizer(std::string n, double p, double tb) {
    name = n;
    price = p;
    taste_balance = tb;
    serveTime = "before";
}

void Appetizer::printInfo() const {
    std::cout << name << " - $" << price << " (Serve: " << serveTime << " main course)\n";
}

void Appetizer::customize() {
    while(true) {
        std::string input;
        std::cout << "When should we serve the appetizer? (before/after main course): ";
        std::cin >> input;
        input = toLower(input);

        if(input == "before") { serveTime = "before"; break; }
        else if(input == "after") { serveTime = "after"; break; }
        else { std::cout << "Invalid input! Geçersiz karakter.\n"; }
    }
}
