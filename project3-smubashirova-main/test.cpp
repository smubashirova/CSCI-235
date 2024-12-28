//  Author: Shokhsanam Mubashirova
//  Course: CSCI-235
//  Instructor: Prof. Wole Oyekoya
//  Date: 10/15/2024
//  Assignment: Project 3
//  Description: This program tests the functionality of the Kitchen and Dish classes.

#include "Kitchen.hpp"
#include "Dish.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    // Create a kitchen object
    Kitchen kitchen;

    // Test newOrder: Adding first dish
    Dish dish1("Spaghetti", {"Pasta", "Tomato Sauce", "Meatballs"}, 45, 12.99, Dish::CuisineType::ITALIAN);
    if (kitchen.newOrder(dish1)) {
        std::cout << "newOrder: SUCCESS for Spaghetti" << std::endl;
    } else {
        std::cout << "newOrder: FAILURE for Spaghetti" << std::endl;
    }

    // Test newOrder: Adding another dish
    Dish dish2("Tacos", {"Tortilla", "Meat", "Cheese"}, 30, 9.99, Dish::CuisineType::MEXICAN);
    if (kitchen.newOrder(dish2)) {
        std::cout << "newOrder: SUCCESS for Tacos" << std::endl;
    } else {
        std::cout << "newOrder: FAILURE for Tacos" << std::endl;
    }

    // Test newOrder: Adding a vegetarian dish
    Dish dish3("Salad", {"Lettuce", "Tomato", "Cucumber"}, 10, 7.50, Dish::CuisineType::OTHER);
    if (kitchen.newOrder(dish3)) {
        std::cout << "newOrder: SUCCESS for Salad" << std::endl;
    } else {
        std::cout << "newOrder: FAILURE for Salad" << std::endl;
    }

    // Test serveDish: Removing a dish
    if (kitchen.serveDish(dish2)) {
        std::cout << "serveDish: SUCCESS for Tacos" << std::endl;
    } else {
        std::cout << "serveDish: FAILURE for Tacos" << std::endl;
    }

    // Test serveDish: Trying to remove a dish not in the kitchen
    if (kitchen.serveDish(dish2)) {
        std::cout << "serveDish: FAILURE (Tacos shouldn't be in the kitchen)" << std::endl;
    } else {
        std::cout << "serveDish: SUCCESS (Tacos already removed)" << std::endl;
    }

    // Test getPrepTimeSum: After adding two dishes and removing one
    int totalPrepTime = kitchen.getPrepTimeSum();
    std::cout << "Total Preparation Time: " << totalPrepTime << " minutes" << std::endl;

    // Test calculateAvgPrepTime: Average preparation time of remaining dishes
    int avgPrepTime = kitchen.calculateAvgPrepTime();
    std::cout << "Average Preparation Time: " << avgPrepTime << " minutes" << std::endl;

    // Test elaborateDishCount: Count elaborate dishes (dish with 5+ ingredients, prep time >= 60)
    int elaborateCount = kitchen.elaborateDishCount();
    std::cout << "Number of Elaborate Dishes: " << elaborateCount << std::endl;

    // Test calculateElaboratePercentage: Percentage of elaborate dishes
    double elaboratePercentage = kitchen.calculateElaboratePercentage();
    std::cout << std::fixed << std::setprecision(2) << "Percentage of Elaborate Dishes: " << elaboratePercentage << "%" << std::endl;

    // Test tallyCuisineTypes: Count of dishes by cuisine type
    int italianDishes = kitchen.tallyCuisineTypes("ITALIAN");
    std::cout << "Number of Italian Dishes: " << italianDishes << std::endl;

    int mexicanDishes = kitchen.tallyCuisineTypes("MEXICAN");
    std::cout << "Number of Mexican Dishes: " << mexicanDishes << std::endl;

    int otherDishes = kitchen.tallyCuisineTypes("OTHER");
    std::cout << "Number of Other Cuisine Dishes: " << otherDishes << std::endl;

    // Test releaseDishesBelowPrepTime: Remove dishes with prep time below 30
    int removedDishes = kitchen.releaseDishesBelowPrepTime(30);
    std::cout << "Number of Dishes Removed Below Prep Time: " << removedDishes << std::endl;

    // Test releaseDishesOfCuisineType: Remove all Italian dishes
    int removedCuisineDishes = kitchen.releaseDishesOfCuisineType("ITALIAN");
    std::cout << "Number of Italian Dishes Removed: " << removedCuisineDishes << std::endl;

    // Test kitchenReport: Generate a report of remaining dishes in the kitchen
    kitchen.kitchenReport();

    return 0;
}

