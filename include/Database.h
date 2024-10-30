#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "Product.h"

class Database {
public:
    Database(); 
    Database(const std::string& db_url, const std::string& username, const std::string& password);
    
    bool connect();
    bool saveProduct(const Product& product);
    Product getProductById(const std::string& productID);
    std::vector<Product> getAllProducts();
    bool updateProduct(const std::string& productID, const Product& updatedProduct);
    bool deleteProduct(const std::string& productID);

private:
    std::string db_url;
    std::string username;
    std::string password;

    // Helper function to perform HTTP requests
    std::string performRequest(const std::string& url, const std::string& method, const std::string& data = "");
};

#endif
