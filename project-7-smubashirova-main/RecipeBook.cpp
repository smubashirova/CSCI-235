/**
 * @file RecipeBook.cpp
 * @brief This file contains the implementation of the RecipeBook class as a subclass of BinarySearchTree, which manages Recipe objects.
 * 
 * The RecipeBook class includes methods to manage objects, organize and retrieve recipes based on difficulty level. 
 * The implementation ensures that the recipe book is sorted by difficulty level.
 * 
 * @date [12/17/2024]
 * @author [Shokhsanam Mubashirova]
*/

#include "RecipeBook.hpp"

/**
    * Default constructor.
    * @post: Initializes name_ and description_ to empty strings, difficulty_level_ to 0, and mastered_ to false.
*/
Recipe::Recipe() : name_(""), difficulty_level_(0), description_(""), mastered_(false) {}

/**
    * Parameterized Constructor.
    * @param name The name of the recipe.
    * @param difficulty_level The difficulty level of the recipe.
    * @param description A brief description of the recipe.
    * @param mastered Indicates whether the recipe has been mastered (default is false).
    * @post: Initializes the Recipe with the provided values.
*/
Recipe::Recipe(const std::string &name, int difficulty_level, const std::string &description, bool mastered)
    : name_(name), difficulty_level_(difficulty_level), description_(description), mastered_(mastered) {}
    
//Operator Overloads
/**
    * Equality operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is equal to other’s name_; false otherwise.
*/
bool Recipe::operator==(const Recipe &other) const {
    return name_ == other.name_;
}

/**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically less than other's name_; false otherwise.
*/
bool Recipe::operator<(const Recipe &other) const {
    return name_ < other.name_;
}

/**
    * Greater-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically greater than other's name_; false otherwise.
*/
bool Recipe::operator>(const Recipe &other) const {
    return name_ > other.name_;
}

/**
    * Default Constructor.
    * @post: Initializes an empty RecipeBook.
*/
RecipeBook::RecipeBook() : BinarySearchTree<Recipe>() {} // Call the default constructor of the base class BinarySearchTree<Recipe>

/**
    * Parameterized Constructor.
    * @param filename A const reference to a string representing the name of a CSV file.
    * @post: The RecipeBook is populated with Recipes from the CSV file.
    * The file format is as follows:
    * name,difficulty_level,description,mastered
    * Ignore the first line. Each subsequent line represents a Recipe to be added to the RecipeBook.
*/
RecipeBook::RecipeBook(const std::string &filename) : BinarySearchTree<Recipe>() {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Ignore the first line (header)
    while (std::getline(file, line)) { // Read each line from the file
        std::stringstream ss(line); // Create a stringstream from the line
        std::string name, description, mastered_str;
        int difficulty_level;
        bool mastered;
        std::getline(ss, name, ','); //Extract the name
        ss >> difficulty_level; //Extract the difficulty level
        ss.ignore(); // Ignore the comma
        std::getline(ss, description, ','); //Extract the description
        std::getline(ss, mastered_str); //Extract the mastered status
        mastered = (mastered_str == "true");
        Recipe recipe(name, difficulty_level, description, mastered); // Create a Recipe object
        addRecipe(recipe); // Add the Recipe to the RecipeBook
    }
}

// Find a Recipe Function
/**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to a string representing the name of the Recipe.
    * @return A pointer to the node containing the Recipe with the given difficulty level, or nullptr if not found.
*/
Recipe* RecipeBook::findRecipe(const std::string &name) const {
    Recipe* foundRecipe = nullptr;
    // Define the lambda for inorder traversal
    auto visit = [&](const Recipe& r) {
        if (r.name_ == name) {
            foundRecipe = const_cast<Recipe*>(&r);  // Found, return non-const pointer
        }
    };
    // Perform inorder traversal to find the recipe
    inorderTraversal(visit);
    return foundRecipe; // Return the found recipe or nullptr
}

// Add a Recipe Function
/**
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult level).
    * @return: True if the Recipe was successfully added; false if a Recipe with the same name already exists.
*/
bool RecipeBook::addRecipe(const Recipe &recipe) {
    if (findRecipe(recipe.name_) != nullptr) {
        return false;  // Recipe already exists, cannot add it
    }
    BinarySearchTree<Recipe>::add(recipe);  // Add the recipe to the BST
    return true;
}

// Remove a Recipe Function
/**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
*/
bool RecipeBook::removeRecipe(const std::string &name) {
    Recipe* recipe = findRecipe(name); // Find the recipe by name
    if (recipe) { //If the recipe is found
        return BinarySearchTree<Recipe>::remove(*recipe); // Remove the recipe from the tree
    }
    return false; // Return false if the recipe was not found
}

// Clear Function
/**
    * Clears all Recipes from the tree.
    * @post: The tree is emptied, and all nodes are deallocated.
*/
void RecipeBook::clear() {
    while (!isEmpty()) { // While the tree is not empty
        remove(getRoot()->getItem()); // Remove the root item
    }
}

// Calculatemasterypoints Function
/**
    * Calculates the number of mastery points needed to master a Recipe.
    * @param name A const reference to a string representing the name of the Recipe.
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty levels must also be mastered.
    * @return: An integer representing the number of mastery points needed, or -1 if the Recipe is not found. If the recipe is already mastered, return 0.
    * Note: Mastery points are calculated as the number of unmastered Recipes in the tree with a lower difficulty level than the given Recipe. Add one if the Recipe is not mastered.
*/
int RecipeBook::calculateMasteryPoints(const std::string &name) const {
    // Locate the recipe by name
    Recipe* recipe = findRecipe(name);
    if (!recipe) return -1;  // Recipe not found
    if (recipe->mastered_) return 0;  // Recipe is already mastered
    int masteryPoints = 0;
    // Perform an inorder traversal to count unmastered recipes with lower difficulty levels
    auto visit = [&masteryPoints, &recipe](const Recipe& r) {
        if (r.difficulty_level_ < recipe->difficulty_level_ && !r.mastered_) {
            masteryPoints++;
        }
    };
    inorderTraversal(visit); // Traverse the tree in inorder
    return masteryPoints + 1;  // Add 1 for the current recipe
}

// Balance Function
/**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get sorted Recipes and rebuilding the tree.
*/
void RecipeBook::balance() {
    std::vector<Recipe> recipes; // Vector to store recipes in sorted order
    inorderTraversal([&recipes](const Recipe& r) { recipes.push_back(r); }); // Store recipes in inorder
    clear(); // Clear the current tree
    balanceHelper(recipes, 0, recipes.size() - 1); // Rebuild the tree in balanced form
}

void RecipeBook::balanceHelper(const std::vector<Recipe>& recipes, int start, int end) {
    if (start > end) return;  // Base case: no more elements to add
    int mid = start + (end - start) / 2;  // Prevent potential overflow
    addRecipe(recipes[mid]);  // Add the middle element
    balanceHelper(recipes, start, mid - 1);  // Recur for left subarray
    balanceHelper(recipes, mid + 1, end);    // Recur for right subarray
}

// preorderdisplay function
/**
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)
*/
void RecipeBook::preorderDisplay() const {
    // Perform preorder traversal and define the lambda to display each recipe
    preorderTraversal([this](const Recipe& r) {
        std::cout << "Name: " << r.name_ << "\n";
        std::cout << "Difficulty Level: " << r.difficulty_level_ << "\n";
        std::cout << "Description: " << r.description_ << "\n";
        std::cout << "Mastered: " << (r.mastered_ ? "Yes" : "No") << "\n\n";
    });
}

// Private traversal methods
void RecipeBook::inorderTraversal(std::function<void(const Recipe&)> visit) const {
    inorderHelper(getRoot(), visit); // Start the inorder traversal from the root
}

void RecipeBook::preorderTraversal(std::function<void(const Recipe&)> visit) const {
    preorderHelper(getRoot(), visit); // Start the preorder traversal from the root
}

// Inorder traversal helper (works with std::shared_ptr)
void RecipeBook::inorderHelper(std::shared_ptr<BinaryNode<Recipe>> node, std::function<void(const Recipe&)> visit) const {
    // Base case: if the node is null, return
    if (node == nullptr) return;
    inorderHelper(node->getLeftChildPtr(), visit);  // Traverse left subtree
    visit(node->getItem());  // Visit the current node
    inorderHelper(node->getRightChildPtr(), visit);  // Traverse right subtree
}

// Preorder traversal helper (works with std::shared_ptr)
void RecipeBook::preorderHelper(std::shared_ptr<BinaryNode<Recipe>> node, std::function<void(const Recipe&)> visit) const {
    if (node != nullptr) {
        visit(node->getItem());  // Visit the current node
        preorderHelper(node->getLeftChildPtr(), visit);  // Traverse left subtree
        preorderHelper(node->getRightChildPtr(), visit);  // Traverse right subtree
    }
}
