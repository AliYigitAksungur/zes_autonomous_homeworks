#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Menu.hpp" // Consolidated header
#include "nlohmann/json.hpp"

using namespace menu;
using json = nlohmann::json;

// --- Global vectors for menu item templates ---
std::vector<std::shared_ptr<Starter>> starters;
std::vector<std::shared_ptr<Salad>> salads;
std::vector<std::shared_ptr<MainCourse>> mains;
std::vector<std::shared_ptr<Drink>> drinks;
std::vector<std::shared_ptr<Appetizer>> apps;
std::vector<std::shared_ptr<Dessert>> desserts;

// --- Function Prototypes for New Features ---
void recommend_menu_ai(ai_recommender::LinearRegressor& regressor);
void suggest_by_taste();

// --- START FIX 1: Add toLower helper function ---
// Helper to convert string to lowercase
inline std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return res;
}
// --- END FIX 1 ---


/**
 * @brief Loads all menu items from the JSON file.
 *
 * Updated to parse the taste_balance object into a TasteProfile vector.
 */
void loadMenuFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Failed to open menu.json\n";
        return;
    }
    json j;
    file >> j;

    auto parse_items = [&](const json& category, auto& vec) {
        using ItemType = typename std::decay_t<decltype(*vec.front())>;
        for(const auto& s : category) {
            TasteProfile tb = {
                s["taste_balance"]["sweet"],
                s["taste_balance"]["sour"],
                s["taste_balance"]["bitter"],
                s["taste_balance"]["salty"],
                s["taste_balance"]["savory"]
            };
            auto item = std::make_shared<ItemType>(s["name"], s["price"], tb);
            vec.push_back(item);
        }
    };

    parse_items(j["starters"], starters);
    parse_items(j["salads"], salads);
    parse_items(j["main_courses"], mains);
    parse_items(j["drinks"], drinks);
    parse_items(j["appetizers"], apps);
    parse_items(j["desserts"], desserts);
}

/**
 * @brief Selects an item from a category and returns a COPY of it.
 *
 * This is crucial so that customizations for one user don't affect the
 * template item available to others.
 */
template<typename T>
std::shared_ptr<T> selectAndCopyItem(const std::vector<std::shared_ptr<T>>& items, const std::string& category) {
    if(items.empty()) {
        std::cout << "No " << category << " available.\n";
        return nullptr;
    }

    std::cout << "\nAvailable " << category << ":\n";
    for(size_t i=0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i]->getName() << " - $" << items[i]->getPrice() << "\n";
    }
    
    int sel;
    while(true) {
        std::cout << "Select number: ";
        std::cin >> sel;
        if(!std::cin.fail() && sel >= 1 && sel <= (int)items.size()) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!\n";
    }
    // Return a new copy of the selected item
    return std::make_shared<T>(*items[sel-1]);
}

// Helper to get yes/no input
bool askYesNo(const std::string& question) {
    std::string input;
    while(true) {
        std::cout << question << " (yes/no): ";
        std::cin >> input;
        input = toLower(input); // This function now exists
        if(input == "yes") return true;
        if(input == "no") return false;
        std::cout << "Invalid input! Please enter 'yes' or 'no'.\n";
    }
}


int main() {
    ai_recommender::LinearRegressor regressor;
    regressor.load_weights("weights.json");
    
    loadMenuFromJSON("menu.json");

    std::string fn, ln, g;
    std::cout << "🍽️ Welcome to the Fancy Night Restaurant Bot!\n";
    std::cout << "Enter first name: ";
    std::cin >> fn;
    std::cout << "Enter last name: ";
    std::cin >> ln;
    while(true) {
        std::cout << "Enter gender (male/female): ";
        std::cin >> g;
        g = toLower(g); // This function now exists
        if(g == "male" || g == "female") break;
        std::cout << "Invalid input! Please enter 'male' or 'female'.\n";
    }
    User user(fn, ln, g);
    Menu& userMenu = user.getMenu();

    int choice;
    do {
        std::cout << "\n" << user.getFullName() << ", what would you like to do?\n"
            "1. Show My Menu & Total Cost\n"
            "2. Add Starter\n"
            "3. Add Salad\n"
            "4. Add Main Course\n"
            "5. Add Drink\n"
            "6. Add Appetizer\n"
            "7. Add Dessert\n"
            "8. Remove Item from My Menu\n"
            "---------- AI Features ----------\n"
            "9. Get an AI Menu Recommendation\n"
            "10. Find a Menu by Taste Profile\n"
            "---------------------------------\n"
            "11. Exit\n> ";
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input!\n";
            continue;
        }

        switch(choice) {
            case 1: userMenu.showMenu(); break;
            case 2: { auto item = selectAndCopyItem(starters, "Starters"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 3: { auto item = selectAndCopyItem(salads, "Salads"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 4: { auto item = selectAndCopyItem(mains, "Main Courses"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 5: { auto item = selectAndCopyItem(drinks, "Drinks"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 6: { auto item = selectAndCopyItem(apps, "Appetizers"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 7: { auto item = selectAndCopyItem(desserts, "Desserts"); if(item) { item->customize(); userMenu.addItem(item); } break; }
            case 8: {
                const auto& items = userMenu.getItems();
                if(items.empty()) { std::cout << "Your menu is empty.\n"; break; }
                std::cout << "\nCurrent items in your menu:\n";
                for(size_t i=0; i<items.size(); ++i) std::cout << i+1 << ". " << items[i]->getName() << "\n";
                int sel;
                while(true) {
                    std::cout << "Enter number of item to remove: ";
                    std::cin >> sel;
                    if(!std::cin.fail() && sel>=1 && sel <= (int)items.size()) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input!\n";
                }
                userMenu.removeItem(items[sel-1]->getName());
                break;
            }
            case 9: recommend_menu_ai(regressor); break;
            case 10: suggest_by_taste(); break;
            case 11:
                regressor.save_weights("weights.json");
                std::cout << "Thanks for dining with us! 🍷\n";
                break;
            default: std::cout << "Invalid choice. Please try again.\n"; break;
        }
    } while(choice != 11);

    return 0;
}

// --- AI Feature Implementations ---

/**
 * @brief Generates random menus, picks the best one according to the AI,
 * asks for user feedback, and updates the AI model.
 */
void recommend_menu_ai(ai_recommender::LinearRegressor& regressor) {
    std::cout << "\n🤖 Generating an AI-powered menu recommendation for you...\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    Menu best_menu;
    double best_score = -1.0;

    // Generate 100 random menus and find the one with the highest predicted satisfaction
    for(int i = 0; i < 100; ++i) {
        Menu current_menu;
        // Add one random item from each non-empty category
        if (!starters.empty()) current_menu.addItem(starters[std::uniform_int_distribution<size_t>(0, starters.size()-1)(gen)]);
        if (!salads.empty()) current_menu.addItem(salads[std::uniform_int_distribution<size_t>(0, salads.size()-1)(gen)]);
        if (!mains.empty()) current_menu.addItem(mains[std::uniform_int_distribution<size_t>(0, mains.size()-1)(gen)]);
        if (!drinks.empty()) current_menu.addItem(drinks[std::uniform_int_distribution<size_t>(0, drinks.size()-1)(gen)]);
        if (!apps.empty()) current_menu.addItem(apps[std::uniform_int_distribution<size_t>(0, apps.size()-1)(gen)]);
        if (!desserts.empty()) current_menu.addItem(desserts[std::uniform_int_distribution<size_t>(0, desserts.size()-1)(gen)]);

        double score = regressor.predict(current_menu.getAverageTasteProfile());
        if(score > best_score) {
            best_score = score;
            best_menu = current_menu;
        }
    }

    std::cout << "I recommend the following menu with a predicted satisfaction score of " << static_cast<int>(best_score * 100) << "%:\n";
    best_menu.showMenu();

    bool liked = askYesNo("Do you like this suggestion?");
    
    double actual_y = liked ? 1.0 : 0.0;
    regressor.update(best_menu.getAverageTasteProfile(), actual_y, best_score);
    std::cout << "Thank you for your feedback! The AI model has been updated.\n";
}

/**
 * @brief Finds a menu that is closest to a user-specified taste profile.
 */
void suggest_by_taste() {
    TasteProfile target_profile(5);
    std::cout << "\nTell us your preferred taste profile (values 0-10).\n";
    std::string balanced_choice;
    std::cout << "Or type 'balanced' for a generally balanced menu: ";
    std::cin >> balanced_choice;

    if (toLower(balanced_choice) == "balanced") { // This function now exists
        target_profile = {5.0, 5.0, 5.0, 5.0, 5.0};
    } else {
        // If they didn't type balanced, assume the first input was the sweet value
        try { target_profile[0] = std::stod(balanced_choice); }
        catch(...) { target_profile[0] = 5.0; } // Default on bad input
        std::cout << "Enter sour (0-10): "; std::cin >> target_profile[1];
        std::cout << "Enter bitter (0-10): "; std::cin >> target_profile[2];
        std::cout << "Enter salty (0-10): "; std::cin >> target_profile[3];
        std::cout << "Enter savory (0-10): "; std::cin >> target_profile[4];
    }
    
    std::cout << "\nSearching for the best menu to match your taste...\n";
    
    Menu best_match_menu;
    double min_distance = std::numeric_limits<double>::max();

    // This is a brute-force search through all combinations.
    // It's feasible for a small menu but would need optimization for larger ones.
    for(const auto& starter : starters) {
    for(const auto& salad : salads) {
    for(const auto& main_course : mains) {
    for(const auto& drink : drinks) {
    for(const auto& app : apps) {
    for(const auto& dessert : desserts) {
        Menu temp_menu;
        temp_menu.addItem(starter);
        temp_menu.addItem(salad);
        temp_menu.addItem(main_course);
        temp_menu.addItem(drink);
        temp_menu.addItem(app);
        temp_menu.addItem(dessert);
        
        TasteProfile avg_profile = temp_menu.getAverageTasteProfile();
        double distance = 0.0;
        for(size_t i = 0; i < 5; ++i) {
            distance += pow(avg_profile[i] - target_profile[i], 2);
        }
        distance = sqrt(distance);

        if (distance < min_distance) {
            min_distance = distance;
            best_match_menu = temp_menu;
        }
    }}}}}}

    std::cout << "\nFound the closest match for your taste profile:\n";
    best_match_menu.showMenu();
}

// --- START FIX 2: Remove the typo at the end of the file ---
// The stray 'clea' text that was here is now gone.
// --- END FIX 2 ---
