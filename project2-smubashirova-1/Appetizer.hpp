/**
 * @file Appetizer.hpp
 * @brief This file contains the declaration of the Appetizer class, which represents an appetizer dish.
 * 
 * The Appetizer class includes attributes such as serving style, spiciness level and a flag indicating if the appetizer is vegetarian.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present the details of a dish.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#ifndef APPETIZER_HPP
#define APPETIZER_HPP

#include "Dish.hpp"
#include <iostream>
#include <string>
#include <vector>

class Appetizer: public Dish{
public:
    // CuisineType enum definition
    enum ServingStyle { PLATED, FAMILY_STYLE, BUFFET };

    /**
        * Default constructor.
        * Initializes all private members with default values
     */
    Appetizer();

    /**
        * Parameterized constructor.
        * @param name A reference to the name of the dish.
        * @param ingredients A reference to a list of ingredients (default is an empty list).
        * @param prep_time The preparation time in minutes (default is 0).
        * @param price The price of the dish (default is 0.0).
        * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
        * @param serving_style The new serving style.
        * @param spiciness_level An integer representing the spiciness level of the appetizer.
        * @param vegetarian A boolean indicating if the appetizer is vegetarian.
        * @post The private members are set to the values of the corresponding parameters.
    */
    Appetizer(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, ServingStyle serving_style, int spiciness_level, bool vegetarian);

    /**
        * @param serving_style The new serving style.
        * @post Sets the private member `serving_style_` to the value of the parameter.
    **/
    void setServingStyle(ServingStyle serving_style);

    /**
        *@return The serving style of the appetizer (as an enum).
    */
    ServingStyle getServingStyle() const;
    
    /**
        * Sets the spiciness level of the appetizer.
        * @param spiciness_level An integer representing the spiciness level of the appetizer.
        * @post Sets the private member `spiciness_level_` to the value of the parameter.
    */
    void setSpicinessLevel(int spiciness_level);

    /**
        * @return The spiciness level of the appetizer.
    */
    int getSpicinessLevel() const;

    /**
        * Sets the vegetarian flag of the appetizer.
        * @param vegetarian A boolean indicating if the appetizer is vegetarian.
        * @post Sets the private member `vegetarian_` to the value of the parameter.
    */
    void setVegetarian(bool vegetarian);

    /**
        * @return True if the appetizer is vegetarian, false otherwise.
    */
    bool isVegetarian() const;

private:
    //The serving style of the appetizer.
    ServingStyle serving_style_;
    //An integer representing the spiciness level of the appetizer on a scale of 1 to 10.
    int spiciness_level_;
    //A flag indicating if the appetizer is vegetarian.
    bool vegetarian_;
};

#endif //Appetizer_HPP
