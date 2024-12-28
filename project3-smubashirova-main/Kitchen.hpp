/**
 * @file Kitchen.hpp
 * @brief This file contains the declaration of the Kitchen subclass of ArrayBag that stores Dish objects. 
 * 
 * The Kitchen class includes attributes such as totalprep_time and countelaborate. 
 * It provides constructors, and unique methods.
 * 
 * @date [10/15/2024]
 * @author [Shokhsanam Mubashirova]
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include <iostream>
#include <string>
#include <cmath>

class Kitchen: public ArrayBag <Dish> {
public:
    /**
        * Default constructor.
        * Default-initializes all private members.
        */
    Kitchen();

    /**
         * Parameterized constructor.
         * @param totalprep_times An integer sum of the preparation times of all the dishes currently in the kitchen.
         * @param countelaborates An integer count of all of the elaborate dishes in the kitchen.
         * @param dishes A vector of Dish objects to initialize the kitchen.
         
     */
    Kitchen(int totalprep_times, int countelaborates, const std::vector<Dish>& dishes = {});

    /**
        * @param : A reference to a `Dish` being added to the kitchen.
        * @post : If the given `Dish` is not already in the kitchen, adds the `Dish` to the kitchen and updates the preparation time sum and vegetarian dish count if the dish is vegetarian.
        * @return : Returns true if a `Dish` was successfully added to the kitchen, false otherwise.
    */
    bool newOrder(const Dish& dish);

    /**
        * @param : A reference to a `Dish` leaving the kitchen.
        * @return : Returns true if a dish was successfully removed from the kitchen (i.e., items_), false otherwise.
        * @post : Removes the dish from the kitchen and updates the preparation time sum. If the `Dish` is vegetarian, it also updates the vegetarian count.
    */
    bool serveDish(const Dish& dish);

    /**
        * @return : The integer sum of preparation times for all the dishes currently in the kitchen.
    */
    int getPrepTimeSum() const;

    /**
        * @return : The average preparation time (int) of all the dishes in the kitchen. The lowest possible average prep time should be 0.
        * @post : Computes the average preparation time (double) of the kitchen rounded to the NEAREST integer.
    */
    int calculateAvgPrepTime() const;

    /**
        * @return : The integer count of the elaborate dishes in the kitchen.
    */
    int elaborateDishCount() const;

    /**
        * @return : The percentage (double) of all the elaborate dishes in the kitchen. The lowest possible percentage should be 0%.
        * @post : Computes the percentage of elaborate dishes in the kitchen rounded up to 2 decimal places.
    */
    double calculateElaboratePercentage() const;

    /**
        * @param : A reference to a string representing a cuisine type with a value in ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"].
        * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type. If the argument string does not match one of the expected cuisine types, the tally is zero.
    */
    int tallyCuisineTypes(const std::string& cuisine_type) const;

    /**
        * @param : A reference to an integer representing the preparation time threshold of the dishes to be removed from the kitchen, with a default value of 0.
        * @post : Removes all dishes from the kitchen whose preparation time is less than the given time. If no time is given, removes all dishes from the kitchen. Ignore negative input.
        * @return : The number of dishes removed from the kitchen.
    */
    int releaseDishesBelowPrepTime(int prep_time = 0);

    /**
        * @param : A reference to a string representing a cuisine type with a value in ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"], or a default value of "ALL" if no cuisine type is given.
        * @post : Removes all dishes from the kitchen whose cuisine type matches the given type. If no cuisine type is given, removes all dishes from the kitchen.
        * @return : The number of dishes removed from the kitchen.
    */
   int releaseDishesOfCuisineType(const std::string& cuisine_type = "ALL");

    /**
        * @post : Outputs a report of the dishes currently in the kitchen in the form: "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:{x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n AVERAGE PREP TIME: {x}\nVEGETARIAN: {x}%\n"
    */
    void kitchenReport() const;
  
private:
    //An integer sum of the preparation times of all the dishes currently in the kitchen.
    int totalprep_time;
    //An integer count of all of the elaborate dishes in the kitchen.
    int countelaborate;
    // Helper function to determine if a dish is elaborate
    bool isElaborate(const Dish& dish) const;
};

#endif // KITCHEN_HPP
