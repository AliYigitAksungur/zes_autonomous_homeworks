#include "../include/User.h"

using namespace menu;

User::User(std::string fn, std::string ln, std::string g)
    : firstName(fn), lastName(ln), gender(g) {}

void User::setFirstName(std::string fn) { firstName = fn; }
void User::setLastName(std::string ln) { lastName = ln; }
void User::setGender(std::string g) { gender = g; }

std::string User::getFullName() const {
    return (gender == "male" ? "Mr. " : "Mrs. ") + lastName;
}

Menu& User::getMenu() { return userMenu; }
