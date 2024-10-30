#include "Report.h"
#include <iostream>
#include <sstream>
#include <ctime>

// Generate a daily report (dummy implementation for demonstration)
std::string Report::generateDailyReport(const std::vector<Product>& products) {
    std::ostringstream report;
    report << "Daily Report\n";
    report << "====================\n";
    
    for (const auto& product : products) {
        report << "Product ID: " << product.getProductID() 
               << ", Name: " << product.getName() 
               << ", Quantity Sold: " << product.getStockQuantity() 
               << ", Total Revenue: " << (product.getPrice() * product.getStockQuantity()) 
               << "\n";
    }
    report << "====================\n";
    return report.str();
}

// Generate a monthly report (dummy implementation for demonstration)
std::string Report::generateMonthlyReport(const std::vector<Product>& products) {
    std::ostringstream report;
    report << "Monthly Report\n";
    report << "====================\n";

    for (const auto& product : products) {
        report << "Product ID: " << product.getProductID() 
               << ", Name: " << product.getName() 
               << ", Total Revenue: " << (product.getPrice() * product.getStockQuantity()) 
               << "\n";
    }
    report << "====================\n";
    return report.str();
}

// Generate an all-time report (dummy implementation for demonstration)
std::string Report::generateAllTimeReport(const std::vector<Product>& products) {
    std::ostringstream report;
    report << "All-Time Report\n";
    report << "====================\n";

    for (const auto& product : products) {
        report << "Product ID: " << product.getProductID() 
               << ", Name: " << product.getName() 
               << ", Total Revenue: " << (product.getPrice() * product.getStockQuantity()) 
               << "\n";
    }
    report << "====================\n";
    return report.str();
}

// Calculate total revenue from all products
double Report::calculateTotalRevenue(const std::vector<Product>& products) {
    double totalRevenue = 0.0;
    for (const auto& product : products) {
        totalRevenue += product.getPrice() * product.getStockQuantity();
    }
    return totalRevenue;
}
