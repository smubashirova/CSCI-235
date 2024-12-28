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
StationManager::StationManager() : LinkedList<KitchenStation*>() {}

/**
    * Destructor
    * @post: Deallocates all kitchen stations and clears the list.
*/
StationManager::~StationManager() {
    for (int i = 0; i < getLength(); i++) {
        delete getEntry(i); // Deallocating each KitchenStation object
    }
    clear(); // Clear the list to remove all nodes.
}

// Member Functions
/**
    * Adds a new station to the station manager.
    * @param station A pointer to a KitchenStation object.
    * @post: Inserts the station into the linked list.
    * @return: True if the station was successfully added; false otherwise.
*/
bool StationManager::addStation(KitchenStation* station) {
    if(station){
        insert(getLength(), station); // Add the station at the end of the list
        return true;
    }
    return false; //if the station pointer is null
}

/**
    * Removes a station from the station manager by name.
    * @param station_name A string representing the station's name.
    * @post: Removes the station from the list and deallocates it.
    * @return: True if the station was found and removed; false otherwise.
*/
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i); // Get the station pointer at the current index
        if (station->getName() == station_name) { //the station matches the name
            delete station; // Deallocate the memory for this station
            remove(i);  // Remove the station from the linked list
            return true;
        }
    }
    return false;  // Station with the given name was not found
}
 
/**
    * Finds a station in the station manager by name.
    * @param station_name A string representing the station's name.
    * @return: A pointer to the KitchenStation if found; nullptr otherwise.
*/
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    // Loop through the linked list using getNodeAt to get each node
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i);
        if (station->getName() == station_name) {
            return station; // Return the station if found
        }
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
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i);
        if (station->getName() == station_name) {
            remove(i);
            insert(0, station); // Insert it at the front of the list
            return true;
        }
    }
    return false;  // Station not found
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
    if (station1 && station2) { // If both stations are found
        for (auto* dish : station2->getDishes()) { // Add all dishes from station2 to station1
            station1->assignDishToStation(dish);
        }
        // Add all ingredients from station2 to station1
        for (const auto& ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        removeStation(station_name2);  // This already deallocates station2
        return true;
    }
    return false; //if either station was not found
}
  
/**
    * Assigns a dish to a specific station.
    * @param station_name A string representing the station's name.
    * @param dish A pointer to a Dish object.
    * @post: Assigns the dish to the specified station.
    * @return: True if the station was found and the dish was assigned; false otherwise.
*/
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) 
{
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish); // Assign the dish to the found station
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
    // Find the station by name
    KitchenStation* station = findStation(station_name);
    if (station) {
        // Replenish the ingredient stock at the specified station
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;  // Station not found
}

/**
    * Checks if any station in the station manager can complete an order for a specific dish.
    * @param dish_name A string representing the name of the dish.
    * @return: True if any station can complete the order; false otherwise.
*/
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    // Loop through all stations in the station manager
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i);
        if (station->canCompleteOrder(dish_name)) { // Check if the station can complete the order
            return true;
        }
    }
    // If no station can complete the dish
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
    // Loop through the stations to find the station with the specified name
    for (int i = 0; i < getLength(); ++i) {
        KitchenStation* station = getEntry(i);
        if (station->getName() == station_name) {
            // Check if the station can prepare the dish
            if (station->canCompleteOrder(dish_name)) {
                // Prepare the dish and reduce the quantities of the used ingredients
                return station->prepareDish(dish_name);
            }
            return false;  // Dish cannot be prepared due to insufficient ingredients
        }
    }
    return false;  // Station not found
}
 