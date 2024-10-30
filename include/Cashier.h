#ifndef CASHIER_H
#define CASHIER_H

#include <vector>
#include "Product.h"
#include "Database.h"

class Cashier {
private:
    std::vector<Product> products;
    Database database;

public:
    bool addProduct(const Product& product);
    bool removeProduct(const std::string& productID);
    bool updateProduct(const std::string& productID, const Product& updatedProduct);
    Product* searchProductByID(const std::string& productID);
    std::vector<Product> searchProductsByCategory(const std::string& category);
    void displayAllProducts() const;
    int getTotalInventoryCount() const;
    double getTotalInventoryValue() const;
    const std::vector<Product>& getAllProducts() const;
};

#endif
