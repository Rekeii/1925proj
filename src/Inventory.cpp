#include "Inventory.h"
#include <iostream>

Inventory::Inventory() {
    // Constructor implementation
}

bool Inventory::addProduct(const Product& product) {
    // Check if the product already exists
    for (const auto& existingProduct : products) {
        if (existingProduct.getProductID() == product.getProductID()) {
            std::cout << "Error: Product with ID " << product.getProductID() << " already exists." << std::endl;
            return false; // Product ID already exists
        }
    }

    // Add new product to the vector
    products.push_back(product);

    // Check if we need to maintain FIFO queue
    if (products.size() > 5) {
        // Remove the oldest product
        products.erase(products.begin());
    }

    // Sync to CouchDB
    if (!database.saveProduct(product)) {
        std::cout << "Error syncing product to CouchDB." << std::endl;
    }

    return true; // Successfully added
}


bool Inventory::removeProduct(const std::string& productID) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getProductID() == productID) {
            products.erase(it);
            
            // Remove the product from the database
            database.deleteProduct(productID);

            std::cout << "Successfully removed Product ID: " << productID << std::endl;
            return true;
        }
    }
    std::cout << "Error: Product ID not found for removal: " << productID << std::endl;
    return false;
}

bool Inventory::updateProduct(const std::string& productID, const Product& updatedProduct) {
    for (auto& existingProduct : products) {
        if (existingProduct.getProductID() == productID) {
            // Update the product fields
            existingProduct.setName(updatedProduct.getName());
            existingProduct.setCategory(updatedProduct.getCategory());
            existingProduct.setPrice(updatedProduct.getPrice());
            existingProduct.setStockQuantity(updatedProduct.getStockQuantity());
            existingProduct.setDescription(updatedProduct.getDescription());

            // Log successful update
            std::cout << "Successfully updated Product ID: " << productID << std::endl;

            // Update the product in the database
            database.updateProduct(productID, updatedProduct);

            // Log the current state of all products after the update
            const auto& allProducts = getAllProducts();
            for (const auto& product : allProducts) {
                std::cout << "Product ID: " << product.getProductID() 
                          << ", Name: " << product.getName() << std::endl;
            }
            return true; // Update successful
        }
    }
    std::cout << "Error: Product ID not found for update: " << productID << std::endl;
    return false; // Product not found
}

// Load products from the database into the local vector
void Inventory::loadProductsFromDatabase() {
    products = database.getAllProducts(); // Load products from the database into the local vector
}

