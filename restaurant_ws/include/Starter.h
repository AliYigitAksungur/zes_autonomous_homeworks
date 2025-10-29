#ifndef STARTER_H
#define STARTER_H

#include "MenuItem.h"

namespace menu {

class Starter : public MenuItem {
    bool isHot;
public:
    Starter(std::string n = "", double p = 0.0, double tb = 0.0, bool hot = true);
    void customize() override;
    void printInfo() const override;
};

}

#endif
