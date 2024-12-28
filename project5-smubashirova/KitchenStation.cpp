/**
 * @file KitchenStation.cpp
 * @brief The KitchenStation class represents a cooking station in the kitchen.
 * 
 * The KitchenStation class includes attributes such as the station name, the list of dishes to prepare, and the current dish being prepared.
 * 
 * @date [11/14/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "KitchenStation.hpp"

/**
    * Default Constructor
    * @post: Initializes an empty kitchen station with default values.
*/
KitchenStation::KitchenStation() : station_name_(""), dishes_(), ingredients_stock_() {}

/**
    * Parameterized Constructor
    * @param station_name A string representing the station's name.
    * @post: Initializes a kitchen station with the given name.
*/
KitchenStation::KitchenStation(const std::string& station_name) 
    : station_name_(station_name), dishes_(), ingredients_stock_() {}

/**
    * Destructor
    * @post: Deallocates all dynamically allocated dishes in the station.
*/
KitchenStation::~KitchenStation() {
    // Loop through each dish in the station and delete it to free memory
    for (Dish* dish : dishes_) {
        delete dish;  //Free the memory allocated for each dish
    }
}

/**
    * Retrieves the name of the kitchen station.
    * @return: The name of the station.
*/
std::string KitchenStation::getName() const {
    return station_name_;
}

/**
    * Sets the name of the kitchen station.
    * @param name A string representing the new station name.
    * @post: Updates the station's name.
*/
void KitchenStation::setName(const std::string& name) {
    station_name_ = name;
}

/**
    * Retrieves the list of dishes assigned to the kitchen station.
    * @return A vector of pointers to Dish objects assigned to the station.
*/
std::vector<Dish*>& KitchenStation::getDishes(){
    return dishes_;
}

/**
    * Retrieves the ingredient stock available at the kitchen station.
    * @return A vector of Ingredient objects representing the station's ingredient stock.
*/
std::vector<Ingredient>& KitchenStation::getIngredientsStock(){
    return ingredients_stock_;
}

// Member Functions
/**
    * Assigns a dish to the station.
    * @param dish A pointer to a Dish object.
    * @post Adds the dish to the station's list of dishes if not already present.
    * @return True if the dish was added successfully; false otherwise.
*/
bool KitchenStation::assignDishToStation(Dish* dish) {
    // Loop through the existing dishes to check if the dish is already assigned
    for (Dish* d : dishes_) {
        if (d->getName() == dish->getName()) {
            return false; // Dish is already assigned
        }
    }
    dishes_.push_back(dish); // Add the dish to the list
    return true;
}

/**
    * Replenishes the station's ingredient stock.
    * @param ingredient An Ingredient object.
    * @post Adds the ingredient to the station's stock or updates the quantity if it already exists.
*/
void KitchenStation::replenishStationIngredients(const Ingredient& ingredient) {
    // Loop through the stock ingredients to check if the ingredient already exists
    for (auto& stock_ingredient : ingredients_stock_) {
        if (stock_ingredient.name == ingredient.name) {
            stock_ingredient.quantity += ingredient.quantity; // Update the quantity if ingredient exists
            return; // No need to add it again, exit the function
        }
    }
    ingredients_stock_.push_back(ingredient); // Add new ingredient if not found
}

/**
    * Checks if the station can complete an order for a specific dish.
    * @param dish_name A string representing the name of the dish.
    * @return True if the station has the dish assigned and all required ingredients are in stock; false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string& dish_name) const {
    // Loop through each dish to check if it matches the requested dish name
    for (const Dish* dish : dishes_) {
        if (dish->getName() == dish_name) {
            // Loop through each ingredient required for the dish
            for (const Ingredient& dish_ingredient : dish->getIngredients()) {
                bool ingredient_found = false;
                // Loop through each ingredient in stock
                for (const Ingredient& stock_ingredient : ingredients_stock_) {
                    if (stock_ingredient.name == dish_ingredient.name &&
                        stock_ingredient.quantity >= dish_ingredient.required_quantity) {
                        ingredient_found = true;
                        break; // No need to check further, move to next ingredient
                    }
                }
                if (!ingredient_found) {
                    return false; // Missing or insufficient ingredient
                }
            }
            return true; // All ingredients available
        }
    }
    return false; // Dish not assigned
}

/**
    * Prepares a dish if possible.
    * @param dish_name A string representing the name of the dish.
    * @post If the dish can be prepared, reduce the quantities of the used ingredients accordingly. If the stock ingredient is depleted to 0, remove the ingredient from the Kitchen Station.
    * @return True if the dish was prepared successfully; false otherwise.
*/
bool KitchenStation::prepareDish(const std::string& dish_name) {
    for (const Dish* dish : dishes_) {
        if (dish->getName() == dish_name) {
            for (const Ingredient& dish_ingredient : dish->getIngredients()) {
                bool ingredient_found = false;
                for (auto it = ingredients_stock_.begin(); it != ingredients_stock_.end(); ++it) {
                    if (it->name == dish_ingredient.name && it->quantity >= dish_ingredient.required_quantity) {
                        it->quantity -= dish_ingredient.required_quantity; // Deduct required quantity
                        ingredient_found = true; // Ingredient found and used
                        if (it->quantity == 0) {
                            ingredients_stock_.erase(it); // Remove if quantity is depleted
                        }
                        break;
                    }
                }
                if (!ingredient_found) {
                    return false; // Missing or insufficient ingredient
                }
            }
            return true; // Dish prepared successfully
        }
    }
    return false; // Dish not found
}