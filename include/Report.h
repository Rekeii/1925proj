#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include "Product.h"

class Report {
public:
    std::string generateDailyReport(const std::vector<Product>& products);
    std::string generateMonthlyReport(const std::vector<Product>& products);
    std::string generateAllTimeReport(const std::vector<Product>& products);
    double calculateTotalRevenue(const std::vector<Product>& products);
};

#endif
