#include "../include/MenuItem.h"

using namespace menu;

MenuItem::MenuItem(std::string n, double p, double tb)
    : name(n), price(p), taste_balance(tb) {}

std::string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }
double MenuItem::getTasteBalance() const { return taste_balance; }

void MenuItem::setName(std::string n) { name = n; }
void MenuItem::setPrice(double p) { price = p; }
void MenuItem::setTasteBalance(double tb) { taste_balance = tb; }
