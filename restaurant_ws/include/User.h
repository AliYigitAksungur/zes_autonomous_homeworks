#ifndef USER_H
#define USER_H

#include <string>
#include "Menu.h"

namespace menu {

class User {
    std::string firstName;
    std::string lastName;
    std::string gender; // Mr. or Mrs.
    Menu userMenu;

public:
    User(std::string fn = "", std::string ln = "", std::string g = "Mr.");

    void setFirstName(std::string fn);
    void setLastName(std::string ln);
    void setGender(std::string g);

    std::string getFullName() const;
    Menu& getMenu();
};

}

#endif
