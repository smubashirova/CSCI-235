/**
 * @file MainCourse.cpp
 * @brief This file contains the declaration of the MainCourse subclass of ArrayBag that stores Dish objects, displays the main course's details, and modifies the main course based on dietary accommodations.
 * 
 * The MainCourse class includes attributes such as side_dishes and gluten_free. 
 * It provides constructors, and unique methods, display, and dietaryAccommodations.
 * 
 * @date [10/28/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "MainCourse.hpp"
#include <algorithm>    // std::find

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}

/**
 * Displays the main course's details.
 * @post Outputs the main course's details, including name, ingredients,
 preparation time, price, cuisine type, cooking method, protein type,
 side dishes, and gluten-free status to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 * Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
 * Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
 * Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
 Vegetables])
 * Gluten-Free: [Yes/No]
 */
void MainCourse::display() {
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
    std::cout << "Cooking Method: " << CookingMethod_toString(cooking_method_) << '\n';
    std::cout << "Protein Type: " << protein_type_ << '\n';
    std::cout << "Side Dishes: ";
    for (size_t i = 0; i < side_dishes_.size(); i++) {
        std::cout << side_dishes_[i].name << " (Category: " << Category_toString(side_dishes_[i].category) << ")";
        if (i != side_dishes_.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << (gluten_free_ ? "Yes" : "No") << '\n';
}

/**
 * Modifies the main course based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
 accommodations.
 * @post Adjusts the main course's attributes to meet the specified
 dietary needs.
 * - If `request.vegetarian` is true:
 * - Changes `protein_type_` to "Tofu".
 * - Searches `ingredients_` for any non-vegetarian
 ingredients and replaces the first occurrence with "Beans". If there are
 other non-vegetarian ingredients, the next non-vegetarian ingredient is
 replaced with "Mushrooms". If there are more, they will be removed
 without substitution.
 * Non-vegetarian ingredients are: "Meat", "Chicken",
 "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
 * - If `request.vegan` is true:
 * - Changes `protein_type_` to "Tofu".
 * - Removes dairy and egg ingredients from `ingredients_`.
 * Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
 "Butter", "Cream", "Yogurt".
 * - If `request.gluten_free` is true:
 * - Sets `gluten_free_` to true.
 * - Removes side dishes from `side_dishes_` whose category
 involves gluten.
 * Gluten-containing side dish categories are: `GRAIN`,
 `PASTA`, `BREAD`, `STARCHES`.
 */
void MainCourse::dietaryAccommodations(DietaryRequest& request) {
    std::vector<std::string> non_vegetarian = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"}; // List of non-vegetarian ingredients
    std::vector<std::string> dairy_egg = { "Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt" }; // List of dairy and egg containing ingredients
    std::vector<Category> gluten = { GRAIN, PASTA, BREAD, STARCHES }; // List of gluten-containing ingredients
    std::vector<std::string> ingredients_ = getIngredients(); // Retrieve the current ingredients list
    if (request.vegetarian){ // Check if the vegetarian request is true
        setProteinType("Tofu"); // Set the protein type to tofu
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
    if (request.vegan){
        setProteinType("Tofu"); // Set the protein type to tofu
        for (size_t i = 0; i < ingredients_.size(); i++){ // Loop through each ingredient
            if (std::find(dairy_egg.begin(), dairy_egg.end(), ingredients_[i]) != dairy_egg.end()){ // Check if the ingredient is dairy or egg
                // Removes the dairy or egg ingredient
                ingredients_.erase(ingredients_.begin() + i);
                i--;
            }
        }
    }
    if (request.gluten_free){
        setGlutenFree(true); // Sets gluten_free_ to true
        for (size_t i = 0; i < side_dishes_.size(); i++){ // Loop through each side dish
            if (std::find(gluten.begin(), gluten.end(), side_dishes_[i].category) != gluten.end()){ // Check if the side dish contains gluten
                // Removes the gluten side dish
                side_dishes_.erase(side_dishes_.begin() + i);
                i--;
            }
        }
    }
    // Updates the ingredients_
    setIngredients(ingredients_);
}

// Helper Functions
//Helper function to convert CookingMethod enum to a string
/**
 * Converts CookingMethod enum to a string
 * @param cooking_method An enum CookingMethod.
 * @return The cooking method of the main course in string form.
 */
std::string MainCourse::CookingMethod_toString(const CookingMethod& cooking_method) const {
    switch (cooking_method) {
        case MainCourse::CookingMethod::GRILLED: return "Grilled"; // returns string "Grilled" if the enum is GRILLED
        case MainCourse::CookingMethod::BOILED: return "Boiled"; // returns string "Boiled" if the enum is BOILED
        case MainCourse::CookingMethod::BAKED: return "Baked"; // returns string "Baked" if the enum is BAKED
        case MainCourse::CookingMethod::FRIED: return "Fried"; // returns string "Fried" if the enum is FRIED
        case MainCourse::CookingMethod::STEAMED: return "Steamed"; // returns string "Steamed" if the enum is STEAMED
        default: return "Raw"; // returns string "Raw" by default
    }
}

//Helper function to convert Category enum to a string
/**
 * Converts Category enum to a string
 * @param category An enum Category.
 * @return The category of the side dish in string form.
 */
std::string MainCourse::Category_toString(const Category& category) const {
    switch (category) {
        case MainCourse::Category::GRAIN: return "GRAIN"; // returns string "GRAIN" if the enum is GRAIN
        case MainCourse::Category::PASTA: return "PASTA"; // returns string "PASTA" if the enum is PASTA
        case MainCourse::Category::LEGUME: return "LEGUME"; // returns string "LEGUME" if the enum is LEGUME
        case MainCourse::Category::BREAD: return "BREAD"; // returns string "BREAD" if the enum is BREAD
        case MainCourse::Category::SALAD: return "SALAD"; // returns string "SALAD" if the enum is SALAD
        case MainCourse::Category::SOUP: return "SOUP"; // returns string "SOUP" if the enum is SOUP
        case MainCourse::Category::STARCHES: return "STARCHES"; // returns string "STARCHES" if the enum is STARCHES
        default: return "VEGETABLE"; // returns string "VEGETABLE" by default
    }
}
