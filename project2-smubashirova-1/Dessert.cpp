/**
 * @file Dessert.cpp
 * @brief This file contains the implementation of the Dessert class, which represents a dessert dish.
 * 
 * The Dessert class includes methods to manage and present the details of a dessert dish, including flavor profile, sweetness level and a flag indicating if the dessert contains nuts.
 * The implementation ensures that the dessert dish contains nuts or not.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#include "Dessert.hpp"
#include "Dish.hpp"

// Default Constructor
Dessert::Dessert() : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

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
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts):
    Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts){}

 /**
    * Sets the flavor profile of the dessert.
    * @param flavor_profile The new flavor profile.
    * @post Sets the private member `flavor_profile_` to the value of the
    parameter.
    */
void Dessert::setFlavorProfile(FlavorProfile flavor_profile)
{
    flavor_profile_=flavor_profile;
}

/**
* @return The flavor profile of the dessert (as an enum).
*/
Dessert::FlavorProfile Dessert::getFlavorProfile() const{
    return flavor_profile_;
}

/**
* Sets the sweetness level of the dessert.
* @param sweetness_level An integer representing the sweetness level of the dessert.
* @post Sets the private member `sweetness_level_` to the value of the parameter.
*/
void Dessert::setSweetnessLevel(int sweetness_level)
{
    sweetness_level_=sweetness_level;
}

/**
* @return The sweetness level of the dessert.
*/
int Dessert::getSweetnessLevel() const
{
    return sweetness_level_;
}

/**
* Sets the contains_nuts flag of the dessert.
* @param contains_nuts A boolean indicating if the dessert contains nuts.
* @post Sets the private member `contains_nuts_` to the value of the parameter.
*/
void Dessert::setContainsNuts(bool contains_nuts)
{
    contains_nuts_=contains_nuts;
}

/**
* @return True if the dessert contains nuts, false otherwise.
*/
bool Dessert::containsNuts() const
{
    return contains_nuts_;
}
