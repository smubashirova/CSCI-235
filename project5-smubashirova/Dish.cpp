/**
 * @file Dish.cpp
 * @brief This file contains the implementation of the Dish class, which represents a dish in a virtual bistro simulation.
 * 
 * The Dish class includes methods to manage and present the details of a dish, including name, ingredients, preparation time, price, and cuisine type.
 * The implementation ensures that the dish name is validated and correctly formatted.
 * 
 * @date [11/14/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "Dish.hpp"

// Default Ingredient Constructors
// Initialize member variables with default values
Ingredient::Ingredient() 
    : name("UNKNOWN"), quantity(0), required_quantity(0), price(0.0) {}

// Ingredient Parameterized Constructor
// Initialize member variables with provided values
Ingredient::Ingredient(const std::string& name, int quantity, int required_quantity, double price)
    : name(name), quantity(quantity), required_quantity(required_quantity), price(price) {}

// Default Constructor
// Initialize member variables with default values
Dish::Dish() 
    : name_("UNKNOWN"), ingredients_(std::vector<Ingredient>()), prep_time_(0), price_(0.0), cuisine_type_(CuisineType::OTHER) {}

// Dish Parameterized Constructor
Dish::Dish(const std::string& name, const std::vector<Ingredient>& ingredients, int prep_time, double price, CuisineType cuisine_type)
    : ingredients_(ingredients), prep_time_(prep_time), price_(price), cuisine_type_(cuisine_type) {
    setName(name);  // Use setName to validate the name
}

// Accessor Functions
std::string Dish::getName() const {
    return name_;
}

std::vector<Ingredient> Dish::getIngredients() const {
    return ingredients_; // Return the list of ingredients
}

int Dish::getPrepTime() const {
    return prep_time_;
}

double Dish::getPrice() const {
    return price_;
}

std::string Dish::getCuisineType() const {
    switch (cuisine_type_) {
        case CuisineType::ITALIAN: return "ITALIAN";
        case CuisineType::MEXICAN: return "MEXICAN";
        case CuisineType::CHINESE: return "CHINESE";
        case CuisineType::INDIAN: return "INDIAN";
        case CuisineType::AMERICAN: return "AMERICAN";
        case CuisineType::FRENCH: return "FRENCH";
        default: return "OTHER";
    }
}

// Mutator Functions
void Dish::setName(const std::string& name) {
    if (isValidName(name)) {
        name_ = name;
    } else {
        name_ = "UNKNOWN";
    }
}

void Dish::setIngredients(const std::vector<Ingredient>& ingredients) {
    ingredients_ = ingredients; // Set the list of ingredients
}

void Dish::setPrepTime(const int& prep_time) {
    prep_time_ = prep_time;
}

void Dish::setPrice(const double& price) {
    price_ = price;
}

void Dish::setCuisineType(const CuisineType& cuisine_type) {
    cuisine_type_ = cuisine_type;
}

// Helper function to check if the name is valid
bool Dish::isValidName(const std::string& name) const {
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c)) {  // Check if each character is a letter or space
            return false;  // Name contains non-alphabetic characters other than spaces
        }
    }
    return true;  // Name is valid
}

/**
    @param : A const reference to the right-hand side of the `==` operator.
    @return : Returns true if the right-hand side dish is "equal", false otherwise. Two dishes are equal if they have the same name, same cuisine type, same preparation time, and the same price.
*/
bool Dish::operator==(const Dish& rhs) const {
    return name_ == rhs.name_ && prep_time_ == rhs.prep_time_ && 
    price_ == rhs.price_ && cuisine_type_ == rhs.cuisine_type_;
}

/**
    @param : A const reference to the right-hand side of the `!=` operator.
    @return : Returns true if the right-hand side dish is NOT "equal" (`!=`),false otherwise. Two dishes are NOT equal if any of their name, cuisine type, preparation time, or price are not equal.
*/
bool Dish::operator!=(const Dish& rhs) const {
    return !(*this == rhs);
}
