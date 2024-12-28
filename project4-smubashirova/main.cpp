/**
 * @file test.cpp
 * @brief This file contains the initialization of the Appetizer, MainCourse, and Dessert classes.
 * 
 *  The test.cpp ensures that all objects created, are thoroughly tested, to ensure that all functions are working properly wiht no errors.
 * 
 * @date [10/19/2024]
 * @author [Sam Lin]
 */
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include "Kitchen.hpp"
#include <iostream>
#include <iomanip>
int main(){
    std::cout << "------------Testing Appetizer------------" << std::endl;
    // Test case 1: Appetizer Parameterized constructor
    Appetizer appetizerOne("AA", {"Meat", "Chicken", "Fish", "Beef", "Wheat", "Flour", "Pasta", "Barley"}, 5, 10.00, Dish::CuisineType::ITALIAN, Appetizer::ServingStyle::PLATED, 8, false);
    Appetizer::DietaryRequest request1;
    request1.vegetarian = true;
    request1.low_sodium = true;
    request1.gluten_free = true;
    appetizerOne.display();
    appetizerOne.dietaryAccommodations(request1);
    std::cout << "------After Request: ------" << std::endl;
    appetizerOne.display();
    std::cout << "------------Testing MainCourse------------" << std::endl;
    // Test case 2: MainCourse Parameterized constructor
    MainCourse::SideDish sideDishOne;
    sideDishOne.name = "Rice";
    sideDishOne.category = MainCourse::Category::STARCHES;
    MainCourse::SideDish sideDishTwo;
    sideDishTwo.name = "Beans";
    sideDishTwo.category = MainCourse::Category::VEGETABLE;
    std::vector<MainCourse::SideDish> side_dishes;
    side_dishes.push_back(sideDishOne);
    side_dishes.push_back(sideDishTwo);
    MainCourse mainOne("MA", {"Meat", "Chicken", "Fish", "Milk", "Cheese", "A", "Pasta", "Barley"}, 5, 10.00, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::GRILLED, "BEEF", side_dishes, false);
    MainCourse::DietaryRequest request2;
    request2.vegetarian = true;
    request2.vegan = true;
    request2.gluten_free = true;
    mainOne.display();
    mainOne.dietaryAccommodations(request2);
    std::cout << "------After Request: ------" << std::endl;
    mainOne.display();
    
    std::cout << "------------Testing Dessert------------" << std::endl;
    // Test case 3: Dessert Parameterized constructor
    Dessert dessertOne("DA", {"AB", "CD", "Almonds", "Beef", "Walnuts", "Milk", "Eggs", "Cheese", "Barley"}, 5, 10.00, Dish::CuisineType::ITALIAN, Dessert::FlavorProfile::SWEET, 5, false);
    Dessert::DietaryRequest request3;
    request3.nut_free = true;
    request3.low_sugar = true;
    request3.vegan = true;
    dessertOne.display();
    dessertOne.dietaryAccommodations(request3);
    std::cout << "------After Request: ------" << std::endl;
    dessertOne.display();
    std::cout << "------------Kitchen------------" << std::endl;
    Kitchen kitchen("Dishes.csv");
    std::cout << "Number Dishes: " << kitchen.getCurrentSize() << std::endl;
    std::cout << "------------DisplayMenu------------" << std::endl;
    kitchen.displayMenu();
    return 0;
}