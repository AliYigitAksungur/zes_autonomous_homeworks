#ifndef MAINCOURSE_H
#define MAINCOURSE_H

#include "MenuItem.h"

namespace menu {

class MainCourse : public MenuItem {
    bool vegetarian;
public:
    MainCourse(std::string n = "", double p = 0.0, double tb = 0.0, bool veg = false);
    void customize() override;
    void printInfo() const override;
};

}

#endif
