/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class, which represents an appetizer dish.
 * 
 * The Appetizer class includes methods to manage and present the details of a appetizer dish, including serving style, spiciness level and a flag indicating if the appetizer is vegetarian, along with methods for displaying details and modifying dietary accommodations.
 * The implementation ensures that the appetizer dish displays and dietary accommodations are correctly implemented.
 * 
 * @date [10/28/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "Appetizer.hpp"
#include <algorithm>    // std::find

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
 * Displays the appetizer's details.
 * @post Outputs the appetizer's details, including name, ingredients,
 preparation time, price, cuisine type, serving style, spiciness level, and
 vegetarian status, to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 * Serving Style: [Serving style: Plated, Family Style, or Buffet]
 * Spiciness Level: [Spiciness level]
 * Vegetarian: [Yes/No]
 */
void Appetizer::display() {
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    std::vector<std::string> ingredients_ = getIngredients();
    for (size_t i = 0; i < ingredients_.size(); ++i) {
        std::cout << ingredients_[i];
        if (i != ingredients_.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;
    std::cout << "Serving Style: " << ServingStyle_toString(serving_style_) << std::endl;
    std::cout << "Spiciness Level: " << spiciness_level_ << std::endl;
    std::cout << "Vegetarian: " << (vegetarian_ ? "Yes" : "No") << std::endl;
}

/**
 * Modifies the appetizer based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
 accommodations.
 * @post Adjusts the appetizer's attributes to meet the specified
 MainCourse Class
 dietary needs.
 * - If `request.vegetarian` is true:
 * - Sets `vegetarian_` to true.
 * - Searches `ingredients_` for any non-vegetarian
 ingredients and replaces the first occurrence with "Beans". If there are
 other non-vegetarian ingredients, the next non-vegetarian ingredient is
 replaced with "Mushrooms". If there are more, they will be removed
 without substitution.
 * Non-vegetarian ingredients are: "Meat", "Chicken",
 "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
 * - If `request.low_sodium` is true:
 * - Reduces `spiciness_level_` by 2 (minimum of 0).
 * - If `request.gluten_free` is true:
 * - Removes gluten-containing ingredients from
 `ingredients_`.
 * Gluten-containing ingredients are: "Wheat", "Flour",
 "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
 */
void Appetizer::dietaryAccommodations(DietaryRequest& request) {
    std::vector<std::string> non_vegetarian = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"}; // List of non-vegetarian ingredients
    std::vector<std::string> gluten = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"}; // List of gluten-containing ingredients
    std::vector<std::string> ingredients_ = getIngredients(); // Retrieve the current ingredients list
    if (request.vegetarian){ // Check if the vegetarian request is true
        setVegetarian(true); // Set the appetizer as vegetarian
        int counter = 0; // Counter to track replacements (Beans and Mushrooms)
        for (size_t i = 0; i < ingredients_.size(); i++){ // Loop through each ingredient
            if (std::find(non_vegetarian.begin(), non_vegetarian.end(), ingredients_[i]) != non_vegetarian.end()){ // Check if the ingredient is non-vegetarian
                // Replace the second non-vegetarian ingredient with "Mushrooms"
                if (counter == 0){
                    ingredients_[i] = "Beans";
                    counter++;
                // Replace the second non-vegetarian ingredient with "Mushrooms"
                } else if (counter == 1){
                    ingredients_[i] = "Mushrooms";
                    counter++;
                // Remove any additional non-vegetarian ingredients
                } else {
                    ingredients_.erase(ingredients_.begin() + i);
                    i--;
                }
            }
        }
    }
    if (request.low_sodium){
        spiciness_level_ -= 2;
        if (spiciness_level_ < 0){
            spiciness_level_ = 0;
        }
    }
    if (request.gluten_free){
        for (size_t i = 0; i < ingredients_.size(); i++){ // Loop through each ingredient
            if (std::find(gluten.begin(), gluten.end(), ingredients_[i]) != gluten.end()){ // Check if the ingredient is gluten
                // Removes the gluten ingredient
                ingredients_.erase(ingredients_.begin() + i);
                i--;
            }
        }
    }
    // Updates the ingredients_
    setIngredients(ingredients_);
}

// Helper function to convert enum to string
/**
 * Converts ServingStyle enum to a string
 * @param serving_style An enum ServingStyle.
 * @return The serving type of the appetizer in string form.
 */
std::string Appetizer::ServingStyle_toString(const ServingStyle& serving_style) const {
    switch (serving_style) {
        case Appetizer::ServingStyle::BUFFET: return "Buffet"; // returns string "Buffet" if the enum is BUFFET
        case Appetizer::ServingStyle::FAMILY_STYLE: return "Family Style"; // returns string "Family Style" if the enum is FAMILY_STYLE
        default: return "Plated"; // returns string "Plated" by default
    }
}
