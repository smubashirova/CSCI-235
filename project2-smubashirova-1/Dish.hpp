/**
 * @file Dish.hpp
 * @brief This file contains the declaration of the Dish class, which represents a dish in a virtual bistro simulation.
 * 
 * The Dish class includes attributes such as name, ingredients, preparation time, price, and cuisine type.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a dish.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#ifndef DISH_HPP
#define DISH_HPP

#include <string>
#include <vector>

class Dish {
public:
    // CuisineType enum definition
    enum class CuisineType { ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER };

    // Constructors
    /**
     * Default constructor.
     * Initializes all private members with default values:
     * - name: "UNKNOWN"
     * - ingredients: Empty list
     * - prep_time: 0
     * - price: 0.0
     * - cuisine_type: OTHER
     */
    Dish();

    /**
     * Parameterized constructor.
     * @param name A reference to the name of the dish.
     * @param ingredients A reference to a list of ingredients (default is an empty list).
     * @param prep_time The preparation time in minutes (default is 0).
     * @param price The price of the dish (default is 0.0).
     * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
     * @post The private members are set to the values of the corresponding parameters.
     */
    Dish(const std::string& name, const std::vector<std::string>& ingredients = {}, int prep_time = 0, double price = 0.0, CuisineType cuisine_type = CuisineType::OTHER);

    // Accessors
    /**
     * @return The name of the dish.
     */
    std::string getName() const;

    /**
     * @return The list of ingredients used in the dish.
     */
    std::vector<std::string> getIngredients() const;

    /**
     * @return The preparation time in minutes.
     */
    int getPrepTime() const;

    /**
     * @return The price of the dish.
     */
    double getPrice() const;

    /**
     * @return The cuisine type of the dish in string form.
     */
    std::string getCuisineType() const;

    // Mutators
    /**
     * Sets the name of the dish.
     * @param name A reference to the new name of the dish.
     * @post Sets the private member `name_` to the value of the parameter. If the name contains non-alphabetic characters, it is set to "UNKNOWN".
     */
    void setName(const std::string& name);

    /**
     * Sets the list of ingredients.
     * @param ingredients A reference to the new list of ingredients.
     * @post Sets the private member `ingredients_` to the value of the parameter.
     */
    void setIngredients(const std::vector<std::string>& ingredients);

    /**
     * Sets the preparation time.
     * @param prep_time The new preparation time in minutes.
     * @post Sets the private member `prep_time_` to the value of the parameter.
     */
    void setPrepTime(const int& prep_time);

    /**
     * Sets the price of the dish.
     * @param price The new price of the dish.
     * @post Sets the private member `price_` to the value of the parameter.
     */
    void setPrice(const double& price);

    /**
     * Sets the cuisine type of the dish.
     * @param cuisine_type The new cuisine type of the dish (a CuisineType enum).
     * @post Sets the private member `cuisine_type_` to the value of the parameter.
     */
    void setCuisineType(const CuisineType& cuisine_type);

    // Display function
    /**
     * Displays the details of the dish.
     * @post Outputs the dish's details, including name, ingredients, preparation time, price, and cuisine type, to the standard output.
     * The information must be displayed in the following format:
     *
     * Dish Name: [Name of the dish]
     * Ingredients: [Comma-separated list of ingredients]
     * Preparation Time: [Preparation time] minutes
     * Price: $[Price, formatted to two decimal places]
     * Cuisine Type: [Cuisine type]
     */
    void display() const;

private:
    std::string name_;
    std::vector<std::string> ingredients_;
    int prep_time_;
    double price_;
    CuisineType cuisine_type_;

    // Helper function to check if the name is valid
    /**
     * Checks if the name is valid.
     * @param name The name to be validated.
     * @return True if the name contains only alphabetic characters and spaces; false otherwise.
     */
    bool isValidName(const std::string& name) const;
};

#endif // DISH_HPP
