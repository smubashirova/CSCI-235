/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class, which represents an appetizer dish.
 * 
 * The Appetizer class includes methods to manage and present the details of a appetizer dish, including serving style, spiciness level and a flag indicating if the appetizer is vegetarian.
 * The implementation ensures that the appetizer dish flag vegetarian dishes correctly.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#include "Appetizer.hpp"
#include "Dish.hpp"

/**
  Default constructor.
  Default-initializes all private members.
*/
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}
   
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
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, ServingStyle serving_style, int spiciness_level, bool vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
    * @param serving_style The new serving style.
    * @post Sets the private member `serving_style_` to the value of the parameter.
**/
void Appetizer::setServingStyle(ServingStyle serving_style){
    serving_style_=serving_style;
}

/**
    *@return The serving style of the appetizer (as an enum).
*/
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}
    
/**
    * Sets the spiciness level of the appetizer.
    * @param spiciness_level An integer representing the spiciness level of the appetizer.
    * @post Sets the private member `spiciness_level_` to the value of the parameter.
*/
void Appetizer::setSpicinessLevel(int spiciness_level){
    spiciness_level_=spiciness_level;
}

/**
    * @return The spiciness level of the appetizer.
*/
int Appetizer::getSpicinessLevel() const{
    return spiciness_level_;
}

/**
    * Sets the vegetarian flag of the appetizer.
    * @param vegetarian A boolean indicating if the appetizer is vegetarian.
    * @post Sets the private member `vegetarian_` to the value of the parameter.
*/
void Appetizer::setVegetarian(bool vegetarian){
    vegetarian_=vegetarian;
}

/**
    * @return True if the appetizer is vegetarian, false otherwise.
*/
bool Appetizer::isVegetarian() const{
    return vegetarian_;
}