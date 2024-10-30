#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string productID;
    std::string name;
    std::string category;
    double price;
    int stockQuantity;
    std::string description;

public:
    Product();
    Product(const std::string& productID, const std::string& name, const std::string& category, 
            double price, int stockQuantity, const std::string& description);
    
    std::string getProductID() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStockQuantity() const;
    std::string getDescription() const;

    void setProductID(const std::string& productID);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setPrice(double price);
    void setStockQuantity(int stockQuantity);
    void setDescription(const std::string& description);

    void updateStock(int delta);
    std::string toString() const;
};

#endif
