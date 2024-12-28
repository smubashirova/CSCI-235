/**
 * @file Kitchen.cpp
 * @brief This file contains the declaration of the Kitchen subclass of ArrayBag that stores Dish objects, stores pointers to Dish objects, implements a parameterized constructor and destructor. 
 * 
 * The Kitchen class includes attributes such as totalprep_time and countelaborate. 
 * It provides constructors, and unique methods, dietaryAdjustment, displayMenu.
 * 
 * @date [10/28/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "Kitchen.hpp"

// Constructor
/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {}

/**
 * Parameterized constructor.
 * @param filename The name of the input CSV file containing dish information.
 * @pre The CSV file must be properly formatted.
 * @post Initializes the kitchen by reading dishes from the CSV file and
 *       storing them as `Dish*`.
 */
Kitchen::Kitchen(const std::string& filename) {
    std::ifstream file(filename); // Open the file for reading

    // Skip the first line (assumed to be headers)
    std::string str;
    std::getline(file, str);
    
    // Process each line in the file
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line); // Create a string stream for the line
        std::string field;

        // Parse the CSV fields
        // Gets the dishtype
        std::getline(s, field, ',');
        std::string DishType = field;

        // Gets the name of the dish
        std::getline(s, field, ',');
        std::string name = field;

        // Gets the list of ingredients, separated by ';'
        std::getline(s, field, ',');
        std::vector<std::string> ingredients;
        std::istringstream ingredients_stream(field);
        std::string ingredient;
        while (std::getline(ingredients_stream, ingredient, ';')) {
            ingredients.push_back(ingredient); // Add each ingredient to vector
        }

        // Gets the prep time and converts it from string to integer
        std::getline(s, field, ',');
        int prep_time = std::stoi(field);

        // Gets the price and converts it from string to double
        std::getline(s, field, ',');
        double price = std::stod(field);

        // Gets the cuisine_type and maps it to the corresponding enum
        std::getline(s, field, ',');
        Dish::CuisineType cuisine_type;
        if (field == "ITALIAN") {
            cuisine_type = Dish::CuisineType::ITALIAN;
        } else if (field == "MEXICAN") {
            cuisine_type = Dish::CuisineType::MEXICAN;
        } else if (field == "CHINESE") {
            cuisine_type = Dish::CuisineType::CHINESE;
        } else if (field == "INDIAN") {
            cuisine_type = Dish::CuisineType::INDIAN;
        } else if (field == "AMERICAN") {
            cuisine_type = Dish::CuisineType::AMERICAN;
        } else if (field == "FRENCH") {
            cuisine_type = Dish::CuisineType::FRENCH;
        } else {
            cuisine_type = Dish::CuisineType::OTHER;
        }

        // Initialize a pointer to the specific dish type
        Dish* new_dish = nullptr;

        // Handle specific dish type based on DishType
        if (DishType == "APPETIZER") {
            // Gets the serving_style and maps it to the enum
            std::getline(s, field, ';');
            Appetizer::ServingStyle serving_style;
            if (field == "PLATED") {
                serving_style = Appetizer::ServingStyle::PLATED;
            } else if (field == "FAMILY_STYLE") {
                serving_style = Appetizer::ServingStyle::FAMILY_STYLE;
            } else {
                serving_style = Appetizer::ServingStyle::BUFFET;
            }

            // Gets the spiciness level and converts it from string to integer
            std::getline(s, field, ';');
            int spiciness_level = std::stoi(field);

            // Gets the vegetarian option and converts it to a boolean
            std::getline(s, field, ',');
            bool vegetarian = field == "true";

            // Create a new Appetizer object
            new_dish = new Appetizer(name, ingredients, prep_time, price, cuisine_type, serving_style, spiciness_level, vegetarian);

        } else if (DishType == "MAINCOURSE") {
            // Gets the cooking_method and maps it to the enum
            std::getline(s, field, ';');
            MainCourse::CookingMethod cooking_method;
            if (field == "GRILLED") {
                cooking_method = MainCourse::CookingMethod::GRILLED;
            } else if (field == "BAKED") {
                cooking_method = MainCourse::CookingMethod::BAKED;
            } else if (field == "BOILED") {
                cooking_method = MainCourse::CookingMethod::BOILED;
            } else if (field == "FRIED") {
                cooking_method = MainCourse::CookingMethod::FRIED;
            } else if (field == "STEAMED") {
                cooking_method = MainCourse::CookingMethod::STEAMED;
            } else {
                cooking_method = MainCourse::CookingMethod::RAW;
            }

            // Gets the type of protein used in the main course
            std::getline(s, field, ';');
            std::string protein_type = field;

            // Gets the side dishes, separated by '|' and parses each for name and category
            std::getline(s, field, ';');
            std::istringstream side_dishes_line(field);
            std::string side_dish_line;
            std::vector<MainCourse::SideDish> side_dishes;
            while (std::getline(side_dishes_line, side_dish_line, '|')) {
                size_t index = side_dish_line.find(':');
                if (index != std::string::npos) {
                    // Extract side dish name and category
                    std::string side_dish_name = side_dish_line.substr(0, index);
                    std::string side_dish_category = side_dish_line.substr(index + 1);

                    // Map the category to the enum
                    MainCourse::SideDish dish;
                    MainCourse::Category category;
                    if (side_dish_category == "GRAIN") {
                        category = MainCourse::Category::GRAIN;
                    } else if (side_dish_category == "PASTA") {
                        category = MainCourse::Category::PASTA;
                    } else if (side_dish_category == "LEGUME") {
                        category = MainCourse::Category::LEGUME;
                    } else if (side_dish_category == "BREAD") {
                        category = MainCourse::Category::BREAD;
                    } else if (side_dish_category == "SALAD") {
                        category = MainCourse::Category::SALAD;
                    } else if (side_dish_category == "SOUP") {
                        category = MainCourse::Category::SOUP;
                    } else if (side_dish_category == "STARCHES") {
                        category = MainCourse::Category::STARCHES;
                    } else {
                        category = MainCourse::Category::VEGETABLE;
                    }
                    dish.name = side_dish_name;
                    dish.category = category;
                    side_dishes.push_back(dish);
                }
            }

            // Gets whether the dish is gluten-free and converts it to boolean
            std::getline(s, field, ',');
            bool gluten_free = field == "true";

            // Create a new MainCourse object
            new_dish = new MainCourse(name, ingredients, prep_time, price, cuisine_type, cooking_method, protein_type, side_dishes, gluten_free);

        } else if (DishType == "DESSERT") {
            // Gets the flavor profile and maps it to the enum
            std::getline(s, field, ';');
            Dessert::FlavorProfile flavor_profile;
            if (field == "SWEET") {
                flavor_profile = Dessert::FlavorProfile::SWEET;
            } else if (field == "BITTER") {
                flavor_profile = Dessert::FlavorProfile::BITTER;
            } else if (field == "SOUR") {
                flavor_profile = Dessert::FlavorProfile::SOUR;
            } else if (field == "SALTY") {
                flavor_profile = Dessert::FlavorProfile::SALTY;
            } else {
                flavor_profile = Dessert::FlavorProfile::UMAMI;
            }

            // 15. Gets the sweetness level and converts it from string to integer
            std::getline(s, field, ';');
            int sweetness_level = std::stoi(field);

            // 16. Gets whether the dessert contains nuts and converts it to boolean
            std::getline(s, field, ',');
            bool contains_nuts = field == "true";

            // Create a new Dessert object
            new_dish = new Dessert(name, ingredients, prep_time, price, cuisine_type, flavor_profile, sweetness_level, contains_nuts);
        }

        // Add the dish to the kitchen if it was successfully created
        if (new_dish != nullptr) {
            this->newOrder(new_dish); // Add the dish to the kitchen's orders
        }
    }
    file.close(); // Close the file
}


/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
 `Dish` to the kitchen and updates the preparation time sum and elaborate
 dish count if the dish is elaborate.
 * @return : Returns true if a `Dish` was successfully added to the
 kitchen, false otherwise.
 Hint: Use the above definition of equality to help determine if a
 `Dish` is already in the kitchen.
 */
bool Kitchen::newOrder(Dish* new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += new_dish->getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}

/**
 * @param : A reference to a `Dish` leaving the kitchen.
 * @return : Returns true if a dish was successfully removed from the
 kitchen (i.e., items_), false otherwise.
 * @post : Removes the dish from the kitchen and updates the preparation
 time sum.
 If the `Dish` is elaborate, it also updates the elaborate count.
 */
bool Kitchen::serveDish(Dish* dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}

/**
 * @return : The integer sum of preparation times for all the dishes
 currently in the kitchen.
 */
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}

/**
 * @return : The average preparation time (int) of all the dishes in the
 kitchen. The lowest possible average prep time should be 0.
 * @post : Computes the average preparation time (double) of the kitchen
 rounded to the NEAREST integer.
 */
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}

/**
 * @return : The integer count of the eelaborate dishes in the kitchen.
 */
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
 kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 rounded up to 2 decimal places.
 */
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}

/**
 * @param : A reference to a string representing a cuisine type with a
 value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
 "FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the
 given cuisine type.
 If the argument string does not match one of the expected
 cuisine types, the tally is zero.
 NOTE: No pre-processing of the input string necessary, only
 uppercase input will match.
 */
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}

/**
 * @param : A reference to an integer representing the preparation time
 threshold of the dishes to be removed from
 the kitchen, with a default value of 0.
 * @post : Removes all dishes from the kitchen whose preparation time is
 less than the given time.
 If no time is given, removes all dishes from the kitchen. Ignore
 negative input.
 * @return : The number of dishes removed from the kitchen.
 */
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

/**
 * @param : A reference to a string representing a cuisine type with a
 value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
 "FRENCH", "OTHER"],
 or a default value of "ALL" if no cuisine type is given.
 * @post : Removes all dishes from the kitchen whose cuisine type matches
 the given type.
 If no cuisine type is given, removes all dishes from the kitchen.
 * @return : The number of dishes removed from the kitchen.
 NOTE: No pre-processing of the input string necessary, only
 uppercase input will match.
 If the input string does not match one of the expected cuisine
 types, do not remove any dishes.
 */
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

/**
 * @post : Outputs a report of the dishes currently in the kitchen in the
 form:
 "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
 {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
 AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
 Note that the average preparation time should be rounded to the
 NEAREST integer, and the
 percentage of elaborate dishes in the kitchen should be rounded
 to 2 decimal places.
        
    Example output:
    ITALIAN: 2
    MEXICAN: 3
    CHINESE: 2
    INDIAN: 1
    AMERICAN: 1
    FRENCH: 2
    OTHER: 2
    AVERAGE PREP TIME: 62
    ELABORATE: 53.85%
 */
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
 * Adjusts all dishes in the kitchen based on the specified dietary
 accommodation.
 * @param request A DietaryRequest structure specifying the dietary
 accommodations.
 * @post Calls the `dietaryAccommodations()` method on each dish in the
 kitchen to adjust them accordingly.
 */
void Kitchen::dietaryAdjustment(Dish::DietaryRequest& request){
    for (int i = 0; i < item_count_; i++){
        items_[i]->dietaryAccommodations(request);
    }
}

/**
 * Displays all dishes currently in the kitchen.
 * @post Calls the `display()` method of each dish.
 */
void Kitchen::displayMenu() const {
    for (int i = 0; i < item_count_; i++){
        items_[i]->display();
    }
}

/**
 * Destructor.
 * @post Deallocates all dynamically allocated dishes to prevent memory
  leaks.
 */
Kitchen::~Kitchen() {
    // Delete only the dishes up to item_count_
    for (int i = 0; i < item_count_; i++) {
        delete items_[i];
    }
}