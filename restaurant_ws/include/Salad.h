#ifndef SALAD_H
#define SALAD_H

#include "MenuItem.h"
#include <string>

namespace menu {

class Salad : public MenuItem {
    bool hasTopping;
    std::string topping;
public:
    Salad(std::string n = "", double p = 0.0, double tb = 0.0);

    void customize() override;
    void printInfo() const override;
};

} // namespace menu

#endif
