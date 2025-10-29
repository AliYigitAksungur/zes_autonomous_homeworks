#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <limits>
#include <numeric>

namespace menu {

// Forward declaration
class MenuItem;

// Represents the 5-dimensional taste profile of a menu item
// Order: [sweet, sour, bitter, salty, savory]
using TasteProfile = std::vector<double>;

/**
 * @class MenuItem
 * @brief Base class for all items on the menu.
 *
 * Now uses a vector of doubles for taste_balance to represent a full taste profile.
 */
class MenuItem {
protected:
    std::string name;
    double price;
    TasteProfile taste_balance;

public:
    MenuItem(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0});
    MenuItem(const MenuItem& other); // Copy constructor
    virtual ~MenuItem() {}

    std::string getName() const;
    double getPrice() const;
    const TasteProfile& getTasteBalance() const;

    void setName(std::string n);
    void setPrice(double p);
    void setTasteBalance(TasteProfile tb);

    virtual void customize() = 0;
    virtual void printInfo() const; // Default implementation provided
};

// --- Derived MenuItem Classes ---

class Appetizer : public MenuItem {
    std::string serveTime;
public:
    Appetizer(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0});
    void customize() override;
    void printInfo() const override;
};

class Dessert : public MenuItem {
    bool extraChocolate;
public:
    Dessert(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0});
    void customize() override;
    void printInfo() const override;
};

class Drink : public MenuItem {
    bool carbonated;
    bool extraShot;
public:
    Drink(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0});
    void customize() override;
    void printInfo() const override;
};

class MainCourse : public MenuItem {
    bool vegetarian;
public:
    MainCourse(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0}, bool veg = false);
    void customize() override;
    void printInfo() const override;
};

class Salad : public MenuItem {
    bool hasTopping;
    std::string topping;
public:
    Salad(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0});
    void customize() override;
    void printInfo() const override;
};

class Starter : public MenuItem {
    bool isHot;
public:
    Starter(std::string n = "", double p = 0.0, TasteProfile tb = {0,0,0,0,0}, bool hot = true);
    void customize() override;
    void printInfo() const override;
};


/**
 * @class Menu
 * @brief Represents a collection of menu items selected by a user.
 *
 * Added a function to calculate the average taste profile of the entire menu.
 */
class Menu {
    std::vector<std::shared_ptr<MenuItem>> items;
public:
    void addItem(std::shared_ptr<MenuItem> item);
    void removeItem(const std::string& name);
    void showMenu() const;
    double totalCost() const;
    TasteProfile getAverageTasteProfile() const; // New function for AI
    const std::vector<std::shared_ptr<MenuItem>>& getItems() const;
};

/**
 * @class User
 * @brief Represents a user of the restaurant bot.
 */
class User {
    std::string firstName;
    std::string lastName;
    std::string gender;
    Menu userMenu;
public:
    User(std::string fn = "", std::string ln = "", std::string g = "Mr.");
    void setFirstName(std::string fn);
    void setLastName(std::string ln);
    void setGender(std::string g);
    std::string getFullName() const;
    Menu& getMenu();
};

} // namespace menu

/**
 * @namespace ai_recommender
 * @brief Contains the AI logic for menu recommendations.
 */
namespace ai_recommender {

class LinearRegressor {
    std::vector<double> weights; // [w0, w1, w2, w3, w4, w5]
    double learning_rate;
public:
    LinearRegressor(int num_features = 5, double alpha = 0.01);
    double predict(const menu::TasteProfile& features) const;
    void update(const menu::TasteProfile& features, double y_actual, double y_predicted);
    void load_weights(const std::string& filename);
    void save_weights(const std::string& filename) const;
};

} // namespace ai_recommender

#endif // MENU_HPP
