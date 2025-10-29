cmake_minimum_required(VERSION 3.10)
project(RestaurantBot CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the nlohmann_json library
find_package(nlohmann_json 3.2.0 REQUIRED)

# --- UPDATED SECTION ---
# Add the 'include' directory so the compiler can find "Menu.hpp"
include_directories(include)

# Add the executable from your source files inside the 'src' directory
add_executable(restaurant_bot
    src/main.cpp
    src/Menu.cpp
)
# --- END UPDATED SECTION ---

# Link the nlohmann_json library to your executable
target_link_libraries(restaurant_bot PRIVATE nlohmann_json::nlohmann_json)
