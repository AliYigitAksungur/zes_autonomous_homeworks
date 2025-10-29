#ifndef APPETIZER_H
#define APPETIZER_H

#include "MenuItem.h"

namespace menu {

class Appetizer : public MenuItem {
    std::string serveTime;
public:
    Appetizer(std::string n = "", double p = 0.0, double tb = 0.0);
    void customize() override;
    void printInfo() const override;
};

}

#endif
