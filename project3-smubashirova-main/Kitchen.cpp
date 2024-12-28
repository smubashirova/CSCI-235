/**
 * @file Kitchen.cpp
 * @brief This file contains the declaration of the Kitchen subclass of ArrayBag that stores Dish objects. 
 * 
 * The Kitchen class includes attributes such as totalprep_time and countelaborate. 
 * It provides constructors, and unique methods.
 * 
 * @date [10/15/2024]
 * @author [Shokhsanam Mubashirova]
 */

#include "Kitchen.hpp"
#include <vector>
#include <iomanip>

    /**
        * Default constructor.
        * Default-initializes all private members.
    */
    Kitchen::Kitchen() : totalprep_time(0), countelaborate(0) {}

    /**
        * Parameterized constructor.
        * @param totalprep_times An integer sum of the preparation times of all the dishes currently in the kitchen.
        * @param countelaborates An integer count of all of the elaborate dishes in the kitchen.
        * @param dishes A vector of Dish objects to initialize the kitchen.  
    */
    Kitchen::Kitchen(int totalprep_times, int countelaborates, const std::vector<Dish>& dishes)
       : totalprep_time(totalprep_times), countelaborate(countelaborates) {
       for (const auto& dish : dishes) {
              newOrder(dish); 
        }
    }

    /**
        * @param : A reference to a `Dish` being added to the kitchen.
        * @post : If the given `Dish` is not already in the kitchen, adds the `Dish` to the kitchen and updates the preparation time sum and elaborate dish count if the dish is elaborate.
        * @return : Returns true if a `Dish` was successfully added to the kitchen, false otherwise.
    */
    bool Kitchen::newOrder(const Dish& dish) {
        if (!contains(dish)) { 
            add(dish); 
            totalprep_time += dish.getPrepTime(); 
            if (isElaborate(dish)) {
                countelaborate++; 
            }
            return true;
        }
        return false;
    }

    /**
        * @param : A reference to a `Dish` leaving the kitchen.
        * @return : Returns true if a dish was successfully removed from the kitchen (i.e., items_), false otherwise.
        * @post : Removes the dish from the kitchen and updates the preparation time sum. If the `Dish` is elaborate, it also updates the elaborate count.
    */
    bool Kitchen::serveDish(const Dish& dish) {
        if (remove(dish)) { 
            totalprep_time -= dish.getPrepTime(); 
            if (isElaborate(dish)) {
                countelaborate--; 
            }
            return true;
        }
        return false;
    }

    /**
        * @return : The integer sum of preparation times for all the dishes currently in the kitchen.
    */
    int Kitchen::getPrepTimeSum() const {
        return totalprep_time;}

    /**
        * @return : The average preparation time (int) of all the dishes in the kitchen. The lowest possible average prep time should be 0.
        * @post : Computes the average preparation time (double) of the kitchen rounded to the NEAREST integer.
    */
    int Kitchen::calculateAvgPrepTime() const {
    int dishCount = getCurrentSize(); 
    return dishCount > 0 ? (totalprep_time + dishCount / 2) / dishCount : 0; // Rounded to nearest integer
    }
        
    /**
        * @return : The integer count of the elaborate dishes in the kitchen.
    */
    int Kitchen::elaborateDishCount() const {
        return countelaborate;
    }

    /**
        * @return : The percentage (double) of all the elaborate dishes in the kitchen. The lowest possible percentage should be 0%.
        * @post : Computes the percentage of elaborate dishes in the kitchen rounded up to 2 decimal places.
    */
    double Kitchen::calculateElaboratePercentage() const {
        int dishCount = getCurrentSize(); 
        if (dishCount > 0) {
            return std::round((static_cast<double>(countelaborate) / dishCount) * 10000.0) / 100.0; 
        } else {
            return 0.0; 
        }
    }

    /**
        * @param : A reference to a string representing a cuisine type with a value in ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"].
        * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type. If the argument string does not match one of the expected cuisine types, the tally is zero.
    */
    int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const {
        int count = 0;
        for (int i = 0; i < getCurrentSize(); i++) {
            if (items_[i].getCuisineType() == cuisine_type) { 
                count++;
            }
        }
        return count;
    }

    /**
        * @param : A reference to an integer representing the preparation time threshold of the dishes to be removed from the kitchen, with a default value of 0.
        * @post : Removes all dishes from the kitchen whose preparation time is less than the given time. If no time is given, removes all dishes from the kitchen. Ignore negative input.
        * @return : The number of dishes removed from the kitchen.
    */
    int Kitchen::releaseDishesBelowPrepTime(int prep_time_threshold) {
    int removedCount = 0;
    for (int i = getCurrentSize() - 1; i >= 0; i--) { // Iterate backward to avoid skipping elements
        if (items_[i].getPrepTime() < prep_time_threshold) {
            serveDish(items_[i]); // Remove the dish
            removedCount++;
        }
    }
    return removedCount;}

    /**
        * @param : A reference to a string representing a cuisine type with a value in ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"], or a default value of "ALL" if no cuisine type is given.
        * @post : Removes all dishes from the kitchen whose cuisine type matches the given type. If no cuisine type is given, removes all dishes from the kitchen.
        * @return : The number of dishes removed from the kitchen.
    */
    int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type) {
    int removedCount = 0;
    for (int i = getCurrentSize() - 1; i >= 0; i--) { // Iterate backward to avoid skipping elements
        if (cuisine_type == "ALL" || items_[i].getCuisineType() == cuisine_type) {
            serveDish(items_[i]); // Remove the dish
            removedCount++;
        }
    }
    return removedCount;}

    /**
        * @post : Outputs a report of the dishes currently in the kitchen in the form: "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:{x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
    */
    void Kitchen::kitchenReport() const {
        std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
        std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
        std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
        std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
        std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
        std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
        std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl;
        std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;

        double elaboratePercentage = calculateElaboratePercentage();
        std::cout << "ELABORATE DISHES: " << std::fixed << std::setprecision(2) 
                  << elaboratePercentage << "%" << std::endl;
    }

    /**
        * @param dish A reference to a Dish object
        * @return true if the dish is elaborate 
    */
    bool Kitchen::isElaborate(const Dish& dish) const {
        return (dish.getPrepTime() >= 60 && dish.getIngredients().size() >= 5);
    }
