#include "Menu.hpp"
#include "nlohmann/json.hpp" // For AI model persistence
#include <fstream>
#include <random>

// Helper to convert string to lowercase
inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return res;
}

namespace menu {

// --- MenuItem Implementation ---
MenuItem::MenuItem(std::string n, double p, TasteProfile tb) 
    : name(n), price(p), taste_balance(tb) {}

// Copy constructor for making unique copies of menu items for each user
MenuItem::MenuItem(const MenuItem& other)
    : name(other.name), price(other.price), taste_balance(other.taste_balance) {}

std::string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }
const TasteProfile& MenuItem::getTasteBalance() const { return taste_balance; }
void MenuItem::setName(std::string n) { name = n; }
void MenuItem::setPrice(double p) { price = p; }
void MenuItem::setTasteBalance(TasteProfile tb) { taste_balance = tb; }

void MenuItem::printInfo() const {
    std::cout << name << " - $" << price;
}

// --- Appetizer Implementation ---
Appetizer::Appetizer(std::string n, double p, TasteProfile tb)
    : MenuItem(n, p, tb), serveTime("before") {}

void Appetizer::printInfo() const {
    MenuItem::printInfo();
    std::cout << " (Serve: " << serveTime << " main course)\n";
}

void Appetizer::customize() {
    // Implementation from your Appetizer.cpp
    while(true) {
        std::string input;
        std::cout << "When should we serve the appetizer? (before/after main course): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "before") { serveTime = "before"; break; }
        else if(input == "after") { serveTime = "after"; break; }
        else { std::cout << "Invalid input! Please enter 'before' or 'after'.\n"; }
    }
}

// --- Dessert Implementation ---
Dessert::Dessert(std::string n, double p, TasteProfile tb)
    : MenuItem(n, p, tb), extraChocolate(false) {}

void Dessert::printInfo() const {
    MenuItem::printInfo();
    if(extraChocolate) std::cout << " (+Chocolate $1.5)";
    std::cout << "\n";
}

void Dessert::customize() {
    // Implementation from your Dessert.cpp
    while(true) {
        std::string input;
        std::cout << "Do you want extra chocolate? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") {
            if (!extraChocolate) price += 1.5; // Add price only once
            extraChocolate = true;
            break;
        } else if(input == "no") {
            if (extraChocolate) price -= 1.5; // Revert price if changed
            extraChocolate = false;
            break;
        } else { std::cout << "Invalid input! Please enter 'yes' or 'no'.\n"; }
    }
}

// --- Drink Implementation ---
Drink::Drink(std::string n, double p, TasteProfile tb)
    : MenuItem(n, p, tb), carbonated(false), extraShot(false) {}

void Drink::printInfo() const {
    MenuItem::printInfo();
    if(carbonated) std::cout << " (Carbonated)";
    if(extraShot) std::cout << " (+Alcohol $2.5)";
    std::cout << "\n";
}

void Drink::customize() {
    // Implementation from your Drink.cpp
    while(true) {
        std::string input;
        std::cout << "Do you want your drink carbonated? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") { carbonated = true; break; }
        else if(input == "no") { carbonated = false; break; }
        else { std::cout << "Invalid input! Please enter 'yes' or 'no'.\n"; }
    }
    while(true) {
        std::string input;
        std::cout << "Do you want an extra alcohol shot? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") {
            if (!extraShot) price += 2.5; // Add price only once
            extraShot = true;
            break;
        } else if(input == "no") {
            if (extraShot) price -= 2.5; // Revert price if changed
            extraShot = false;
            break;
        } else { std::cout << "Invalid input! Please enter 'yes' or 'no'.\n"; }
    }
}

// --- MainCourse Implementation ---
MainCourse::MainCourse(std::string n, double p, TasteProfile tb, bool veg)
    : MenuItem(n, p, tb), vegetarian(veg) {}

void MainCourse::printInfo() const {
    MenuItem::printInfo();
    std::cout << " (" << (vegetarian ? "Vegetarian" : "Non-Vegetarian") << ")\n";
}

void MainCourse::customize() {
    // Implementation from your MainCourse.cpp
    while(true) {
        std::string input;
        std::cout << "Do you want a vegetarian main course? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") { vegetarian = true; break; }
        else if(input == "no") { vegetarian = false; break; }
        else { std::cout << "Invalid input! Please enter 'yes' or 'no'.\n"; }
    }
}

// --- Salad Implementation ---
Salad::Salad(std::string n, double p, TasteProfile tb)
    : MenuItem(n, p, tb), hasTopping(false), topping("") {}

void Salad::printInfo() const {
    MenuItem::printInfo();
    if(hasTopping) std::cout << " (Topping: " << topping << " +$2.25)";
    std::cout << "\n";
}

void Salad::customize() {
    // Implementation from your Salad.cpp
    while(true) {
        std::string input;
        std::cout << "Do you want a topping for your salad? (yes/no): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "yes") {
            if (!hasTopping) price += 2.25; // Add price only once
            hasTopping = true;
            std::cout << "Enter topping name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, topping);
            break;
        } else if(input == "no") {
            if (hasTopping) price -= 2.25; // Revert price if changed
            hasTopping = false;
            topping = "";
            break;
        } else { std::cout << "Invalid input! Please enter 'yes' or 'no'.\n"; }
    }
}

// --- Starter Implementation ---
Starter::Starter(std::string n, double p, TasteProfile tb, bool hot)
    : MenuItem(n, p, tb), isHot(hot) {}

void Starter::printInfo() const {
    MenuItem::printInfo();
    std::cout << " (" << (isHot ? "Hot" : "Cold") << ")\n";
}

void Starter::customize() {
    // Implementation from your Starter.cpp
    while(true) {
        std::string input;
        std::cout << "Do you want your starter hot or cold? (hot/cold): ";
        std::cin >> input;
        input = toLower(input);
        if(input == "hot") { isHot = true; break; }
        else if(input == "cold") { isHot = false; break; }
        else { std::cout << "Invalid input! Please enter 'hot' or 'cold'.\n"; }
    }
}

// --- Menu Implementation ---
void Menu::addItem(std::shared_ptr<MenuItem> item) {
    items.push_back(item);
}

void Menu::removeItem(const std::string& name) {
    // Implementation from your Menu.cpp
    auto it = std::remove_if(items.begin(), items.end(), [&](const std::shared_ptr<MenuItem>& i) {
        return i->getName() == name;
    });
    if(it != items.end()) {
        items.erase(it, items.end());
        std::cout << name << " removed from menu.\n";
    } else {
        std::cout << "Item not found!\n";
    }
}

void Menu::showMenu() const {
    if (items.empty()) {
        std::cout << "\nYour menu is empty.\n";
        return;
    }
    std::cout << "\n----- Your Menu -----\n";
    for (const auto &it : items) {
        it->printInfo();
    }
    std::cout << "---------------------\n";
    std::cout << "Total Cost: $" << totalCost() << std::endl;
}

double Menu::totalCost() const {
    double sum = 0;
    for (const auto &i : items) sum += i->getPrice();
    return sum;
}

const std::vector<std::shared_ptr<MenuItem>>& Menu::getItems() const {
    return items;
}

// New method to calculate average taste profile for the AI
TasteProfile Menu::getAverageTasteProfile() const {
    if (items.empty()) {
        return {0,0,0,0,0};
    }
    TasteProfile total = {0,0,0,0,0};
    for(const auto& item : items) {
        const auto& tb = item->getTasteBalance();
        for(size_t i = 0; i < total.size(); ++i) {
            total[i] += tb[i];
        }
    }
    for(size_t i = 0; i < total.size(); ++i) {
        total[i] /= items.size();
    }
    return total;
}

// --- User Implementation ---
User::User(std::string fn, std::string ln, std::string g) 
    : firstName(fn), lastName(ln), gender(g) {}
void User::setFirstName(std::string fn) { firstName = fn; }
void User::setLastName(std::string ln) { lastName = ln; }
void User::setGender(std::string g) { gender = g; }
std::string User::getFullName() const { return (gender == "male" ? "Mr. " : "Mrs. ") + lastName; }
Menu& User::getMenu() { return userMenu; }

} // namespace menu


namespace ai_recommender {

using json = nlohmann::json;

// --- LinearRegressor Implementation ---
LinearRegressor::LinearRegressor(int num_features, double alpha) : learning_rate(alpha) {
    // Initialize weights randomly (w0 is bias term)
    weights.resize(num_features + 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.1, 0.1);
    for(size_t i = 0; i < weights.size(); ++i) {
        weights[i] = dis(gen);
    }
}

double LinearRegressor::predict(const menu::TasteProfile& features) const {
    double prediction = weights[0]; // Start with bias w0
    for(size_t i = 0; i < features.size(); ++i) {
        prediction += weights[i+1] * features[i];
    }
    // Sigmoid function to keep prediction between 0 and 1
    return 1.0 / (1.0 + exp(-prediction));
}

void LinearRegressor::update(const menu::TasteProfile& features, double y_actual, double y_predicted) {
    double error = y_actual - y_predicted;
    weights[0] += learning_rate * error; // Update bias weight w0
    for(size_t i = 0; i < features.size(); ++i) {
        weights[i+1] += learning_rate * error * features[i];
    }
}

void LinearRegressor::load_weights(const std::string& filename) {
    std::ifstream file(filename);
    if(file.is_open()) {
        json j;
        file >> j;
        weights = j["weights"].get<std::vector<double>>();
        std::cout << "AI model weights loaded successfully.\n";
    } else {
        std::cout << "No existing AI model found. Starting with a new one.\n";
    }
}

void LinearRegressor::save_weights(const std::string& filename) const {
    std::ofstream file(filename);
    json j;
    j["weights"] = weights;
    file << j.dump(4);
}

} // namespace ai_recommender
