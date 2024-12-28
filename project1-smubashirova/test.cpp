//  Author: Shokhsanam Mubashirova
//  Course: CSCI-235
//  Instructor: Prof. Wole Oyekoya
//  Date: 09/16/2024
//  Assignment: Project 1
//  Description: This program implements Dish class

#include "Dish.hpp"
#include <vector>
#include <iostream>

int main() {
    // Test default constructor
    Dish meal;

    // Mutators to set values
    meal.setName("UNKNOWN");
    meal.setIngredients({});
    meal.setPrepTime(30);
    meal.setPrice(9.99);
    meal.setCuisineType(Dish::OTHER);

    meal.display();
    
    //Test parameterized constructor
    std::vector<std::string> ingredients={"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"};
    Dish meal2("Pasta Carbonara", ingredients, 20, 12.50, Dish::ITALIAN);

    //Test Accessors
    std::string name=meal2.getName();
    std::vector<std::string>menu=meal2.getIngredients();
    int prep_time=meal2.getPrepTime();
    double price=meal2.getPrice();
    std::string cuisine_type=meal2.getCuisineType();

    //Mutators to set values
    meal2.setName("Pasta Carbonara");
    meal2.setIngredients(menu);
    meal2.setPrepTime(prep_time);
    meal2.setPrice(price);
    meal2.setCuisineType(Dish::ITALIAN);

    meal2.display();

    return 0;
}