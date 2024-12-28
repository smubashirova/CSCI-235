/**
 * @file Dish.hpp
 * @brief This file contains the declaration of the Dish class, which represents a dish in a virtual bistro simulation.
 * 
 * The Dish class includes attributes such as name, ingredients, preparation time, price, and cuisine type.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a dish.
 * 
 * @date [11/14/2024]
 * @author [Shokhsanam Mubashirova]
*/

#ifndef DISH_HPP
#define DISH_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

/**
    * Struct representing an ingredient.
*/
struct Ingredient {
    std::string name; // Name of the ingredient
    int quantity;   // Quantity in stock
    int required_quantity;  // Quantity required for a dish
    double price;   // Price per unit

//Default constructor
    Ingredient();

//Parameterized constructor
    Ingredient(const std::string& name, int quantity, int required_quantity, double price);
};

class Dish {
public:
    // CuisineType enum definition
    enum CuisineType { ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER };

    /** 
     * Structure to store dietary accommodation details.
    */
    struct DietaryRequest {
        //Indicates if the dish is vegetarian, vegan, gluten-free, nut-free, low-sodium and low sugar.
        bool vegetarian;
        bool vegan;
        bool gluten_free;
        bool nut_free;
        bool low_sodium;
        bool low_sugar;
    }; 
    
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
    Dish(const std::string& name, const std::vector<Ingredient>& ingredients = std::vector<Ingredient>(), int prep_time = 0, double price = 0.0, CuisineType cuisine_type = CuisineType::OTHER);

    // Accessors
    /**
     * @return The name of the dish.
    */
    std::string getName() const;

    /**
     * @return The list of ingredients used in the dish.
    */
    std::vector<Ingredient> getIngredients() const;

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
    void setIngredients(const std::vector<Ingredient>& ingredients);

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

    /**
        @param : A const reference to the right-hand side of the `==` operator.
        @return : Returns true if the right-hand side dish is "equal", false otherwise. Two dishes are equal if they have the same name, same cuisine type, same preparation time, and the same price.
    */
    bool operator==(const Dish & rhs)const;

    /**
        @param : A const reference to the right-hand side of the `!=` operator.
        @return : Returns true if the right-hand side dish is NOT "equal" (`!=`), false otherwise. Two dishes are NOT equal if any of their name, cuisine type, preparation time, or price are not equal.
    */
    bool operator!=(const Dish & rhs)const;
    
private:
    std::string name_;
    std::vector<Ingredient> ingredients_;  //List of required ingredients
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
