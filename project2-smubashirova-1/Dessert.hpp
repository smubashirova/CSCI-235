/**
 * @file Dessert.hpp
 * @brief This file contains the declaration of the Dessert class, which represents a dessert dish.
 * 
 * The Dessert class includes attributes such as flavor profile, sweetness level, a flag indicating if the dessert contains nuts.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present the details of a dessert dish.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#ifndef DESSERT_HPP
#define DESSERT_HPP

#include "Dish.hpp"
#include <iostream>
#include <string>
#include <vector>

class Dessert: public Dish {
public:
    // Describes the dominant flavor of the dessert.
    enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI};

    /**
     * Default constructor.
     * Initializes all private members with default values:
     */
    Dessert();

    /**
     * Parameterized constructor.
     * @param name A reference to the name of the dish.
     * @param ingredients A reference to a list of ingredients (default is an empty list).
     * @param prep_time The preparation time in minutes (default is 0).
     * @param price The price of the dish (default is 0.0).
     * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
     * @param flavor_profile The new flavor profile.
     * @param sweetness_level An integer representing the sweetness level of the dessert.
     * @param contains_nuts A boolean indicating if the dessert contains nuts.
     * @post The private members are set to the values of the corresponding parameters.
     */
    Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts);

   /**
    * Sets the flavor profile of the dessert.
    * @param flavor_profile The new flavor profile.
    * @post Sets the private member `flavor_profile_` to the value of the
    parameter.
    */
    void setFlavorProfile(FlavorProfile flavor_profile);

    /**
    * @return The flavor profile of the dessert (as an enum).
    */
    FlavorProfile getFlavorProfile() const;

    /**
    * Sets the sweetness level of the dessert.
    * @param sweetness_level An integer representing the sweetness level of
    the dessert.
    * @post Sets the private member `sweetness_level_` to the value of the
    parameter.
    */
    void setSweetnessLevel(int sweetness_level);

    /**
    * @return The sweetness level of the dessert.
    */
    int getSweetnessLevel() const;

    /**
    * Sets the contains_nuts flag of the dessert.
    * @param contains_nuts A boolean indicating if the dessert contains nuts.
    * @post Sets the private member `contains_nuts_` to the value of the parameter.
    */
    void setContainsNuts(bool contains_nuts);

    /**
    * @return True if the dessert contains nuts, false otherwise.
    */
    bool containsNuts() const;

private:
    FlavorProfile flavor_profile_;
    int sweetness_level_;
    bool contains_nuts_;
};

#endif // DESSERT_HPP
