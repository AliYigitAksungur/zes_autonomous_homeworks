#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

namespace menu {

class MenuItem {
protected:
    std::string name;
    double price;
    int tasteScore; // taste score 0–10 (default 5)

public:
    MenuItem(const std::string& n, double p, int score = 5)
        : name(n), price(p), tasteScore(score) {}

    virtual ~MenuItem() = default;

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getTasteScore() const { return tasteScore; } // <-- Added for averageTaste()

    virtual void printInfo() const {
        std::cout << name << " ($" << price << ", Taste: " << tasteScore << ")\n";
    }

    virtual void customize() {
        int newScore;
        std::cout << "Enter taste score for " << name << " (0–10, default " << tasteScore << "): ";
        std::cin >> newScore;

        if (!std::cin.fail() && newScore >= 0 && newScore <= 10)
            tasteScore = newScore;
        else {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input! Keeping default taste score (" << tasteScore << ").\n";
        }
    }
};

} // namespace menu

#endif
