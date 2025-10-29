#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <string>
#include "MenuItem.h"

namespace menu {

class Menu {
    std::vector<std::shared_ptr<MenuItem>> items;

public:
    void addItem(std::shared_ptr<MenuItem> item);
    void removeItem(const std::string& name);
    void showMenu() const;
    double totalCost() const;
    double averageTaste() const;
    const std::vector<std::shared_ptr<MenuItem>>& getItems() const;
};

}

#endif
