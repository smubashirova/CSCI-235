/**
 * @file StationManager.cpp
 * @brief The Station Manager class will inherit from the LinkedList<KitchenStation*> template.
 * 
 * The Station Manager class will include methods to manage and present the details of the kitchen stations.
 * @date [11/14/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "StationManager.hpp"
#include <iostream>
#include <string>

/**
    * Default Constructor
    * @post: Initializes an empty station manager.
*/
StationManager::StationManager() {}

// Member Functions
/**
    * Adds a new station to the station manager.
    * @param station A pointer to a KitchenStation object.
    * @post: Inserts the station into the linked list.
*/
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

/**
    * Removes a station from the station manager by name.
    * @param station_name A string representing the station's name.
    * @post: Removes the station from the list and deallocates it.
    * @return: True if the station was found and removed; false otherwise.
*/
bool StationManager::removeStation(const std::string& station_name) {
    // Iterate through each item in the station manager
    for (int i = 0; i < item_count_; i++) {
        // Check if the name of the station at the current index matches the input name
        if (getEntry(i)->getName() == station_name) {
            return remove(i);  // Remove the station at the found index
        }
    }
    return false;  // Station not found
}

/**
    * Finds a station in the station manager by name.
    * @param station_name A string representing the station's name.
    * @return: A pointer to the KitchenStation if found; nullptr otherwise.
*/
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();  // Start from the head node
    while (searchptr != nullptr) {
        // Check if the name of the station in the current node matches the input name
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();  // Return the station if found
        }
        searchptr = searchptr->getNext();  // Move to the next node
    }
    return nullptr;  // Station not found
}

/**
    * Moves a specified station to the front of the station manager list.
    * @param station_name A string representing the station's name.
    * @post: The station is moved to the front of the list if it exists.
    * @return: True if the station was found and moved; false otherwise.
*/
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}

// helper function to get index of a station by name
int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

/**
    * Merges the dishes and ingredients of two specified stations.
    * @param station_name1 The name of the first station.
    * @param station_name2 The name of the second station.
    * @post: The second station is removed from the list, and its contents are added to the first station.
    * @return: True if both stations were found and merged; false otherwise.
*/
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

/**
    * Assigns a dish to a specific station.
    * @param station_name A string representing the station's name.
    * @param dish A pointer to a Dish object.
    * @post: Assigns the dish to the specified station.
    * @return: True if the station was found and the dish was assigned; false otherwise.
*/
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

/**
    * Replenishes an ingredient at a specific station.
    * @param station_name A string representing the station's name.
    * @param ingredient An Ingredient object.
    * @post: Replenishes the ingredient stock at the specified station.
    * @return: True if the station was found and the ingredient was replenished; false otherwise.
*/
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

/**
    * Checks if any station in the station manager can complete an order for a specific dish.
    * @param dish_name A string representing the name of the dish.
    * @return: True if any station can complete the order; false otherwise.
*/
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

/**
    * Prepares a dish at a specific station if possible.
    * @param station_name A string representing the station's name.
    * @param dish_name A string representing the name of the dish.
    * @post: If the dish can be prepared, reduces the quantities of the used ingredients at the station.
    * @return: True if the dish was prepared successfully; false otherwise.
*/
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

// Accessors and Mutators
/**
    * Retrieves the current dish preparation queue.
    * @return A copy of the queue containing pointers to Dish objects.
    * @post: The dish preparation queue is returned unchanged.
*/
std::queue<Dish*> StationManager::getDishQueue() const{
    // Return a copy of the dish preparation queue
    return dish_queue_;
}

/**
    * Retrieves the list of backup ingredients.
    * @return A vector containing Ingredient objects representing backup supplies.
    * @post: The list of backup ingredients is returned unchanged.
*/
std::vector<Ingredient> StationManager::getBackupIngredients() const{
    // Return a copy of the backup ingredients vector
    return backup_ingredients_;
}

/**
    * Sets the current dish preparation queue.
    * @param dish_queue A queue containing pointers to Dish objects.
    * @pre: The dish_queue contains valid pointers to dynamically allocated Dish objects.
    * @post: The dish preparation queue is replaced with the provided queue.
*/
void StationManager::setDishQueue(const std::queue<Dish*>&dish_queue){
    // Replace the current dish preparation queue with the provided queue
    dish_queue_ = dish_queue;
}

/**
    * Adds a dish to the preparation queue without dietary accommodations.
    * @param dish A pointer to a dynamically allocated Dish object.
    * @pre: The dish pointer is not null.
    * @post: The dish is added to the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish) {
    if (dish) {
        // Add the dish to the end of the preparation queue
        dish_queue_.push(dish);
    }
}
    
/**
    * Adds a dish to the preparation queue with dietary accommodations.
    * @param dish A pointer to a dynamically allocated Dish object.
    * @param request A DietaryRequest object specifying dietary accommodations.
    * @pre: The dish pointer is not null.
    * @post: The dish is adjusted for dietary accommodations and added to the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish, Dish::DietaryRequest request) {
    if (dish) {
        // Apply dietary accommodations to the dish
        dish->dietaryAccommodations(request);

        // Add the dish to the queue
        dish_queue_.push(dish);
    }
}

/**
    * Prepares the next dish in the queue if possible.
    * @pre: The dish queue is not empty.
    * @post: The dish is processed and removed from the queue.
    * If the dish cannot be prepared, it stays in the queue
    * @return: True if the dish was prepared successfully; false otherwise.
*/
bool StationManager::prepareNextDish() {
    if (dish_queue_.empty()) {
        return false;  // The dish queue is empty
    }

    Dish* next_dish = dish_queue_.front();  // Get the next dish in the queue

    // Attempt to prepare the dish at any station
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i);  // Get the station at the current index
        // Check if the station can handle the dish
        if (station->canCompleteOrder(next_dish->getName())) {
            // Attempt to prepare the dish
            if (station->prepareDish(next_dish->getName())) {
                dish_queue_.pop();  // Remove the dish from the queue
                return true;  // Dish was prepared successfully
            }
        }
    }
    return false;  // Dish could not be prepared
}  

/**
    * Displays all dishes in the preparation queue.
    * @pre: None.
    * @post: Outputs the names of the dishes in the queue in order (each name is on its own line).
*/
void StationManager::displayDishQueue() const {
    std::queue<Dish*> temp_queue = dish_queue_;  // Create a copy of the dish queue

    while (!temp_queue.empty()) {
        // Get the dish at the front of the temporary queue
        Dish* dish = temp_queue.front();
        std::cout << dish->getName() << std::endl;  // Output the name of the dish
        temp_queue.pop();  // Remove the dish from the temporary queue
    }  
}

/**
    * Clears all dishes from the preparation queue.
    * @pre: None.
    * @post: The dish queue is emptied and all allocated memory is freed.
*/
void StationManager::clearDishQueue() {
    // Continue until the dish queue is empty
    while (!dish_queue_.empty()) {
        Dish* dish = dish_queue_.front();  // Get the dish at the front of the queue
        delete dish;  // Free the allocated memory for the dish
        dish_queue_.pop();  // Remove the dish from the queue
    }
}

/**
 * Replenishes a specific ingredient at a given station from the backup ingredients stock by a specified quantity.
 * @param station_name A string representing the name of the station.
 * @param ingredient_name A string representing the name of the ingredient to replenish.
 * @param quantity An integer representing the amount to replenish.
 * @pre None.
 * @post If the ingredient is found in the backup ingredients stock and has sufficient quantity, it is added to the station's ingredient stock by the specified amount, and the function returns true.
 * The quantity of the ingredient in the backup stock is decreased by the specified amount.
 * If the ingredient in backup stock is depleted (quantity becomes zero), it is removed from the backup stock.
 * If the ingredient does not have sufficient quantity in backup stock, or the ingredient or station is not found, returns false.
 * @return True if the ingredient was replenished from backup; false otherwise.
*/
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity) {
    KitchenStation* station = findStation(station_name);  // Find the station by name
    if (!station) {
        return false; // Station not found
    }
    // Iterate through the backup ingredients to find the specified ingredient
    for (auto it = backup_ingredients_.begin(); it != backup_ingredients_.end(); it++) {
        // ingredient matches
        if (it->name == ingredient_name) {
            // there is enough quantity in the backup stock
            if (it->quantity >= quantity) {
                // Replenish the station's ingredient stock
                Ingredient replenished_ingredient = *it;
                replenished_ingredient.quantity = quantity;
                station->replenishStationIngredients(replenished_ingredient);

                // Decrease the quantity in the backup stock
                it->quantity -= quantity;

                // Remove the ingredient from backup stock if depleted
                if (it->quantity == 0) {
                    backup_ingredients_.erase(it);
                }
                return true; // Successfully replenished
            } else {
                return false; // Not enough quantity in backup stock
            }
        }
    }
    return false; // Ingredient not found in backup stock
}

/**
    * Sets the backup ingredients stock with the provided list of ingredients.
    * @param ingredients A vector of Ingredient objects to set as the backup stock.
    * @pre None.
    * @post The backup_ingredients_ vector is replaced with the provided ingredients.
    * @return True if the ingredients were added; false otherwise.
*/
bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients) {
    // Replace the current backup ingredients with the provided list
    backup_ingredients_ = ingredients;
    return true; // Ingredients were added
}

/**
    * Adds a single ingredient to the backup ingredients stock.
    * @param ingredient An Ingredient object to add to the backup stock.
    * @pre None.
    * @post If the ingredient already exists in the backup stock, its quantity is increased by the ingredient's quantity.
    * If the ingredient does not exist, it is added to the backup stock.
    * @return True if the ingredient was added; false otherwise.
*/
bool StationManager::addBackupIngredient(const Ingredient& ingredient) {
    for (auto& backup_ingredient : backup_ingredients_) {
        if (backup_ingredient.name == ingredient.name) {
            backup_ingredient.quantity += ingredient.quantity;  // Increase quantity if ingredient exists
            return true;  // Ingredient was added
        }
    }
    backup_ingredients_.push_back(ingredient);  // Add new ingredient if it doesn't exist
    return true;  // Ingredient was added
}

/**
    * Empties the backup ingredients vector
    * @post The backup_ingredients_ private member variable is empty.
*/
void StationManager::clearBackupIngredients(){
    // Clear all elements from the backup ingredients vector
    backup_ingredients_.clear();
}

/**
    * Processes all dishes in the queue and displays detailed results.
    * @pre: None.
    * @post: All dishes are processed, and detailed information is displayed (as per the format in the specifications), including station replenishments and preparation results.
    * If a dish cannot be prepared even after replenishing ingredients, it stays in the queue in its original order...
    * i.e. if multiple dishes cannot be prepared, they will remain in the queue in the same order
*/
void StationManager::processAllDishes() {
    std::queue<Dish*> temp_queue; // Temporary queue for unprepared dishes

    // Process each dish in the main queue
    while (!dish_queue_.empty()) {
        Dish* dishToPrepare = dish_queue_.front(); // Get the dish at the front of the queue.
        bool prepared = false;                    // Track if the dish was successfully prepared.

        // Check if the dish is valid
        if (!dishToPrepare || dishToPrepare->getName().empty()) {
            dish_queue_.pop();  // Remove invalid dish from the queue
            continue;   // Skip to the next dish
        }
        std::cout << "PREPARING DISH: " << dishToPrepare->getName() << std::endl;

        // Iterate through all kitchen stations to find one that can prepare the dish
        for (int i = 0; i < getLength(); i++) {
            KitchenStation* station = getEntry(i);  // Get the current station
            // Check if the station is valid
            if (!station || station->getName().empty()) {
                continue;  // Skip invalid station
            }
            std::cout << station->getName() << " attempting to prepare " << dishToPrepare->getName() << "..." << std::endl;

            // Check if the station has the dish
            bool dishAvailable = false;
            for (Dish* item : station->getDishes()) {
                if (item->getName() == dishToPrepare->getName()) {
                    dishAvailable = true;  // Dish is available at this station
                    break;
                }
            }
            if (!dishAvailable) {
                std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
                continue;  // Move to the next station if dish is not available
            }

            // Check if the station can complete the order
            if (!station->canCompleteOrder(dishToPrepare->getName())) {
                std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;

                bool replenished = true;  // Track if ingredients were successfully replenished
                // Iterate over the ingredients needed for the dish and replenish as necessary
                for (const Ingredient& ingredient : dishToPrepare->getIngredients()) {
                    bool ingredientFound = false;  // Track if the ingredient is found in stock
                    int requiredQuantity = ingredient.required_quantity;  // Quantity needed
                    int availableQuantity = 0;  // Quantity available in stock

                    // Check if the ingredient exists in the station's stock and how much is available
                    for (Ingredient& stockIngredient : station->getIngredientsStock()) {
                        if (ingredient.name == stockIngredient.name) {
                            availableQuantity = stockIngredient.quantity;  // Update available quantity
                            ingredientFound = true;  // Ingredient found in stock
                            break;
                        }
                    }

                    if (ingredientFound) {
                        // If the available quantity is less than required, calculate the difference
                        int diff = requiredQuantity - availableQuantity;
                        if (diff > 0) { // Replenish the missing quantity from backup 
                            if (!replenishStationIngredientFromBackup(station->getName(), ingredient.name, diff)) {
                                replenished = false;
                                break;
                            }
                        }
                    } else {
                        // If the ingredient is not found at all, replenish the full required quantity
                        if (!replenishStationIngredientFromBackup(station->getName(), ingredient.name, requiredQuantity)) {
                            replenished = false;  // Replenishment failed
                            break;
                        }
                    }
                }
                if (replenished) {
                    std::cout << station->getName() << ": Ingredients replenished." << std::endl;
                } else {
                    std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dishToPrepare->getName() << "." << std::endl;
                    continue; // Move to the next station
                }
            }

            // Attempt to prepare the dish after replenishment
            if (station->prepareDish(dishToPrepare->getName())) {
                std::cout << station->getName() << ": Successfully prepared " << dishToPrepare->getName() << "." << std::endl;
                prepared = true;  // Dish was successfully prepared
                break;
            } else {
                std::cout << station->getName() << ": Unable to prepare " << dishToPrepare->getName() << "." << std::endl;
            }
        }
        if (!prepared) {
            std::cout << dishToPrepare->getName() << " was not prepared." << std::endl;
            temp_queue.push(dishToPrepare); // Requeue the unprepared dish
        }
        dish_queue_.pop();  // Remove the dish from the main queue
        std::cout << std::endl;
    }
    dish_queue_ = temp_queue; // Replace the original queue with the new one
    std::cout << "\nAll dishes have been processed." << std::endl;
}
