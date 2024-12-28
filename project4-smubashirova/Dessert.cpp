/**
 * @file Dessert.cpp
 * @brief This file contains the implementation of the Dessert class, which represents a dessert dish.
 * 
 * The Dessert class includes methods to manage and present the details of a dessert dish, including flavor profile, sweetness level and a flag indicating if the dessert contains nuts, displays the desert's details, and modifies the dessert based on dietary accommodations.
 * The implementation ensures that the dessert dish contains nuts or not, displays the dessert's details, and modifies the dessert based on dietary accommodations. 
 * 
 * @date [10/28/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "Dessert.hpp"
#include <algorithm>    // std::find

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}

/**
 * Displays the dessert's details.
 * @post Outputs the dessert's details, including name, ingredients,
 preparation time, price, cuisine type, flavor profile, sweetness level, and
 whether it contains nuts.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
 Note for all subclasses: When multiple ingredients are removed, at most two replacement
 ingredients should be added, and they should replace the first and second (when applicable)
 occurrences of the ingredients to be removed.
 Step 3: Modify the Kitchen Class
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 * Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
 * Sweetness Level: [Sweetness level]
 * Contains Nuts: [Yes/No]
 */
void Dessert::display() {
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
    std::cout << "Flavor Profile: " << FlavorProfile_toString(flavor_profile_) << std::endl;
    std::cout << "Sweetness Level: " << sweetness_level_ << std::endl;
    std::cout << "Contains Nuts: " << (contains_nuts_ ? "Yes" : "No") << std::endl;
}

/**
 * Modifies the dessert based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
 accommodations.
 * @post Adjusts the dessert's attributes to meet the specified dietary
 needs.
 * - If `request.nut_free` is true:
 * - Sets `contains_nuts_` to false.
 * - Removes nuts from `ingredients_`.
 * Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
 "Peanuts", "Cashews", "Pistachios".
 * - If `request.low_sugar` is true:
 * - Reduces `sweetness_level_` by 3 (minimum of 0).
 * - If `request.vegan` is true:
 * - Removes dairy and egg ingredients from `ingredients_`.
 * Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
 "Butter", "Cream", "Yogurt".
 */
void Dessert::dietaryAccommodations(DietaryRequest& request) {
    std::vector<std::string> nuts = {"Almonds", "Walnuts", "Pecans", "Hazelnuts", "Peanuts", "Cashews", "Pistachios"}; // List of nuts-containing ingredients
    std::vector<std::string> dairy_egg = { "Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt" }; // List of dairy and egg containing ingredients
    std::vector<std::string> ingredients_ = getIngredients(); // Retrieve the current ingredients list
    if (request.nut_free){ // Check if the vegetarian request is true
        setContainsNuts(false); // Set the dessert as nut-free
        for (size_t i = 0; i < ingredients_.size(); i++){ // Loop through each ingredient
            if (std::find(nuts.begin(), nuts.end(), ingredients_[i]) != nuts.end()){ // Check if the ingredient contains nuts
                // Removes the nut-containing ingredient
                ingredients_.erase(ingredients_.begin() + i);
                i--;
            }
        }
    }
    if (request.low_sugar){
        sweetness_level_ -= 3;
        if (sweetness_level_ < 0){
            sweetness_level_ = 0;
        }
    }
    if (request.vegan){
        for (size_t i = 0; i < ingredients_.size(); i++){ // Loop through each ingredient
            if (std::find(dairy_egg.begin(), dairy_egg.end(), ingredients_[i]) != dairy_egg.end()){ // Check if the ingredient is dairy or egg
                // Removes the dairy or egg ingredient
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
 * Converts FlavorProfile enum to a string
 * @param flavor_profile An enum FlavorProfile.
 * @return The flavor profile of the Dessert in string form.
 */
std::string Dessert::FlavorProfile_toString(const FlavorProfile& flavor_profile) const {
    switch (flavor_profile) {
        case Dessert::FlavorProfile::SWEET: return "Sweet"; // returns string "Sweet" if the enum is SWEET
        case Dessert::FlavorProfile::BITTER: return "Bitter"; // returns string "Bitter" if the enum is BITTER
        case Dessert::FlavorProfile::SOUR: return "Sour"; // returns string "Sour" if the enum is SOUR
        case Dessert::FlavorProfile::SALTY: return "Salty"; // returns string "Salty" if the enum is SALTY
        default: return "Umani"; // returns string "Umani" by default
    }
}
