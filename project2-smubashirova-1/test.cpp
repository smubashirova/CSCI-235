//  Author: Shokhsanam Mubashirova
//  Course: CSCI-235
//  Instructor: Prof. Wole Oyekoya
//  Date: 09/30/2024
//  Assignment: Project 2
//  Description: This program implements subclasses

#include "Appetizer.hpp"
#include "Dessert.hpp"
#include "MainCourse.hpp"
#include "Dish.hpp"
#include <iostream>

int main() {

    Appetizer meal ;
    meal.setName("UNKNOWN");
    meal.setIngredients({}); 
    meal.setPrepTime(0); 
    meal.setPrice(0.00); 
    meal.setCuisineType(Dish::CuisineType::OTHER); 
    meal.setSpicinessLevel(7);
    meal.setServingStyle(Appetizer::FAMILY_STYLE);
    meal.setVegetarian(true);

    // Test the Appetizer methods
    std::cout << "Dish Name: " << meal.getName() << "\n";
    std::cout << "Ingredients: ";
    for (const auto& ingredient : meal.getIngredients()) {
        std::cout << ingredient << " ";
    }
    std::cout << "\nPreparation Time: " << meal.getPrepTime() << " mins\n";
    std::cout << "Price: $" << meal.getPrice() << "\n";
    std::cout << "Cuisine Type: " << (meal.getCuisineType() == Dish::CuisineType::OTHER ? "OTHER" : "ITALIAN") << "\n";
    std::cout << "Spiciness Level: " << meal.getSpicinessLevel() << "\n";
    std::cout << "Serving Style: " << (meal.getServingStyle() == Appetizer::FAMILY_STYLE ? "Family Style" : "Other") << "\n";
    std::cout << "Vegetarian: " << (meal.isVegetarian() ? "Yes" : "No") << "\n";
    meal.display();
    
    MainCourse dish; 
    dish.setName("Grilled Chicken"); 
    dish.setIngredients({"Chicken", "Olive Oil", "Garlic", "Rosemary"}); 
    dish.setPrepTime(30); 
    dish.setPrice(18.99); 
    dish.setCuisineType(Dish::CuisineType::AMERICAN);
    dish.setCookingMethod(MainCourse::GRILLED);
    dish.setProteinType("Chicken");
    dish.addSideDish({"Mashed Potatoes", MainCourse::STARCHES, "Green Beans", MainCourse::VEGETABLE});
    dish.setGlutenFree(true);
    
    // Test the MainCourse methods
    std::cout << "Dish Name: " << dish.getName() << "\n";
    std::cout << "Ingredients: ";
    for (const auto& ingredient : dish.getIngredients()) {
        std::cout << ingredient << " ";
    }
    std::cout << "\nPreparation Time: " << dish.getPrepTime() << " mins\n";
    std::cout << "Price: $" << dish.getPrice() << "\n";
    std::cout << "Cuisine: " << (dish.getCuisineType() == Dish::CuisineType::AMERICAN ? "AMERICAN" : "OTHER") << "\n";
    std::cout << "Cooking Method: " << (dish.getCookingMethod() == MainCourse::GRILLED ? "GRILLED" : "OTHER") << "\n";
    std::cout << "Protein Type: " << dish.getProteinType() << "\n";
    std::cout << "Side Dishes: ";
    for (const auto& side : dish.getSideDishes()) {
        std::cout << side.getName() << " (" << (side.getCategory() == MainCourse::STARCHES ? "Starches" : "Vegetables") << ") ";
    }
    std::cout << "\nGluten-Free: " << (dish.isGlutenFree() ? "Yes" : "No") << "\n";
    dish.display();

    Dessert sweet;
    sweet.setName("Chocolate Cake");
    sweet.setIngredients({"Flour", "Sugar", "Cocoa Powder", "Eggs"}); 
    sweet.setPrepTime(45);
    sweet.setPrice(7.99); 
    sweet.setCuisineType(Dish::CuisineType::FRENCH); 
    sweet.setFlavorProfile(Dessert::SWEET); 
    sweet.setSweetnessLevel(9); 
    sweet.setContainsNuts(false); 

    // Test the Dessert methods
    std::cout << "\nDessert Details:\n";
    std::cout << "Name: " << sweet.getName() << "\n";
    std::cout << "Ingredients: ";
    for (const auto& ingredient : sweet.getIngredients()) {
        std::cout << ingredient << " ";
    }
    std::cout << "\nPreparation Time: " << sweet.getPrepTime() << " mins\n";
    std::cout << "Price: $" << sweet.getPrice() << "\n";
    std::cout << "Cuisine: " << (sweet.getCuisineType() == Dish::CuisineType::FRENCH ? "FRENCH" : "OTHER") << "\n";
    std::cout << "Flavor Profile: " << (sweet.getFlavorProfile() == Dessert::SWEET ? "SWEET" : "OTHER") << "\n";
    std::cout << "Sweetness Level: " << sweet.getSweetnessLevel() << "\n";
    std::cout << "Contains Nuts: " << (sweet.containsNuts() ? "Yes" : "No") << "\n";
    sweet.display();

    return 0;
}


