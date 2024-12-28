/**
 * @file MainCourse.hpp
 * @brief This file contains the declaration of the MainCourse class, which represents a main course dish.
 * 
 * The MainCourse class includes attributes such as cooking method, protein type, side dishes and a flag indicating if the main course is gluten free. 
 * It provides constructors, accessor and mutator functions, and a display function to manage and present the details of a main course dish.
 * 
 * @date [09/30/2024]
 * @author [Shokhsanam Mubashirova]
 */

#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP

#include "Dish.hpp"
#include <string>
#include <vector>

class MainCourse : public Dish {
public:
    // Enum describing the method used to cook the main course
    enum CookingMethod { GRILLED, BAKED, FRIED, STEAMED, RAW };
    enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };

    // Struct representing a side dish
    struct SideDish {
        std::string name;
        Category category;
    };

    /**
        * Default constructor.
        * Initializes all private members with default values:
    */
    MainCourse();

    /**
        * Parameterized constructor.
        * @param name A reference to the name of the dish.
        * @param ingredients A reference to a list of ingredients (default is an empty list).
        * @param prep_time The preparation time in minutes (default is 0).
        * @param price The price of the dish (default is 0.0).
        * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
        * @param cooking_method The new cooking method.
        * @param protein_type A string representing the type of protein.
        * @param side_dish A SideDish struct containing the name and category of the side dish.
        * @param gluten_free A boolean indicating if the main course is gluten-free.
        * @post The private members are set to the values of the corresponding parameters.
    */
    MainCourse(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, CookingMethod cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, bool gluten_free);

    /**
        * Sets the cooking method of the main course.
        * @param cooking_method The new cooking method.
        * @post Sets the private member `cooking_method_` to the value of the parameter.
    */
    void setCookingMethod(CookingMethod cooking_method);

    /**
        * @return The cooking method of the main course (as an enum).
    */
    CookingMethod getCookingMethod() const;

    /**
        * Sets the type of protein in the main course.
        * @param protein_type A string representing the type of protein.
        * @post Sets the private member `protein_type_` to the value of the parameter.
    */
    void setProteinType(const std::string& protein_type);

    /**
        * @return The type of protein in the main course.
    */
    std::string getProteinType() const;

    /**
        * Adds a side dish to the main course.
        * @param side_dish A SideDish struct containing the name and category of the side dish.
        * @post Adds the side dish to the `side_dishes_` vector.
    */
    void addSideDish(const SideDish& side_dishes);

    /**
        * @return A vector of SideDish structs representing the side dishes served with the main course.
    */
    std::vector<SideDish> getSideDishes() const;

    /**
        * Sets the gluten-free flag of the main course.
        * @param gluten_free A boolean indicating if the main course is gluten-free
        * @post Sets the private member `gluten_free_` to the value of the parameter
    */
    void setGlutenFree(bool gluten_free);

    /**
        * @return True if the main course is gluten-free, false otherwise.
    */
    bool isGlutenFree() const;

private:
    //The cooking method used for the main course.
    CookingMethod cooking_method_;
    //A string representing the type of protein used in the main course.
    std::string protein_type_;
    //A vector containing SideDish structs representing the side dishes served with the main course.
    std::vector<SideDish> side_dishes_;
    //A flag indicating if the main course is gluten-free.
    bool gluten_free_;
};

#endif // MAINCOURSE_HPP
