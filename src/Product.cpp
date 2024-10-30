#include "Product.h"

Product::Product() : productID(""), name(""), category(""), price(0.0), stockQuantity(0), description("") {}

Product::Product(const std::string& productID, const std::string& name, const std::string& category, 
                 double price, int stockQuantity, const std::string& description) 
    : productID(productID), name(name), category(category), price(price), stockQuantity(stockQuantity), description(description) {}

std::string Product::getProductID() const { return productID; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStockQuantity() const { return stockQuantity; }
std::string Product::getDescription() const { return description; }

void Product::setProductID(const std::string& productID) { this->productID = productID; }
void Product::setName(const std::string& name) { this->name = name; }
void Product::setCategory(const std::string& category) { this->category = category; }
void Product::setPrice(double price) { this->price = price; }
void Product::setStockQuantity(int stockQuantity) { this->stockQuantity = stockQuantity; }
void Product::setDescription(const std::string& description) { this->description = description; }

void Product::updateStock(int delta) { stockQuantity += delta; }

std::string Product::toString() const {
    return "Product ID: " + productID + "\nName: " + name + "\nCategory: " + category + 
           "\nPrice: " + std::to_string(price) + "\nStock Quantity: " + std::to_string(stockQuantity) + 
           "\nDescription: " + description;
}
