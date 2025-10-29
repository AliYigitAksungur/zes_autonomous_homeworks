#ifndef DRINK_H
#define DRINK_H

#include "MenuItem.h"

namespace menu {

class Drink : public MenuItem {
    bool carbonated;
    bool extraShot;
public:
    Drink(std::string n = "", double p = 0.0, double tb = 0.0);
    void customize() override;
    void printInfo() const override;
};

}

#endif
