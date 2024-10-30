#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Product.h"
#include "Database.h"

class Inventory {
private:
    std::vector<Product> products;
    Database database;

public:
    Inventory();
    bool addProduct(const Product& product);
    bool removeProduct(const std::string& productID);
    bool updateProduct(const std::string& productID, const Product& updatedProduct);
    Product* searchProductByID(const std::string& productID);
    std::vector<Product> searchProductsByCategory(const std::string& category);
    void displayAllProducts() const;
    int getTotalInventoryCount() const;
    double getTotalInventoryValue() const;
    const std::vector<Product>& getAllProducts() const;

    // Helper function to maintain FIFO structure
    void maintainFIFO();
    void loadProductsFromDatabase();

};

#endif
