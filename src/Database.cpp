#include "Database.h"
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>

Database::Database() : db_url("default_url"), username("default_user"), password("default_pass") {
    // Initialize with default values
}

// Constructor to initialize database URL and credentials
Database::Database(const std::string& db_url, const std::string& username, const std::string& password)
    : db_url(db_url), username(username), password(password) {}

// Connect to the database (you can add connection checks if needed)
bool Database::connect() {
    // This function can be used to check if the database is accessible.
    // For now, we'll just return true.
    return true;
}

// Helper function to perform HTTP requests
std::string Database::performRequest(const std::string& url, const std::string& method, const std::string& data) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (username + ":" + password).c_str());
        
        // Set the HTTP method
        if (method == "POST") {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        } else if (method == "PUT") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        } else if (method == "DELETE") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        } else if (method == "GET") {
            // No extra options needed for GET
        }

        // Capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }
    return readBuffer;
}

// Save a product to CouchDB
bool Database::saveProduct(const Product& product) {
    Json::Value jsonData;
    jsonData["productID"] = product.getProductID();
    jsonData["name"] = product.getName();
    jsonData["category"] = product.getCategory();
    jsonData["price"] = product.getPrice();
    jsonData["stockQuantity"] = product.getStockQuantity();
    jsonData["description"] = product.getDescription();

    Json::StreamWriterBuilder writer;
    std::string data = Json::writeString(writer, jsonData);
    std::string url = db_url + "/products"; // Update to your CouchDB endpoint

    std::string response = performRequest(url, "POST", data);
    return !response.empty(); // Return true if the response is valid
}

// Get a product by its ID from CouchDB
Product Database::getProductById(const std::string& productID) {
    std::string url = db_url + "/products/" + productID; // Update to your CouchDB endpoint
    std::string response = performRequest(url, "GET", "");

    // Parse the JSON response
    Json::CharReaderBuilder reader;
    Json::Value jsonResponse;
    std::istringstream s(response);
    std::string errs;

    if (Json::parseFromStream(reader, s, &jsonResponse, &errs)) {
        return Product(
            jsonResponse["productID"].asString(),
            jsonResponse["name"].asString(),
            jsonResponse["category"].asString(),
            jsonResponse["price"].asDouble(),
            jsonResponse["stockQuantity"].asInt(),
            jsonResponse["description"].asString()
        );
    }
    return Product(); // Return a default Product if parsing fails
}

// Get all products from CouchDB
std::vector<Product> Database::getAllProducts() {
    std::string url = db_url + "/products"; // Update to your CouchDB endpoint
    std::string response = performRequest(url, "GET", "");

    std::vector<Product> products;
    Json::CharReaderBuilder reader;
    Json::Value jsonResponse;
    std::istringstream s(response);
    std::string errs;

    if (Json::parseFromStream(reader, s, &jsonResponse, &errs)) {
        for (const auto& item : jsonResponse) {
            products.emplace_back(
                item["productID"].asString(),
                item["name"].asString(),
                item["category"].asString(),
                item["price"].asDouble(),
                item["stockQuantity"].asInt(),
                item["description"].asString()
            );
        }
    }
    return products;
}

// Update a product in CouchDB
bool Database::updateProduct(const std::string& productID, const Product& updatedProduct) {
    Json::Value jsonData;
    jsonData["productID"] = updatedProduct.getProductID();
    jsonData["name"] = updatedProduct.getName();
    jsonData["category"] = updatedProduct.getCategory();
    jsonData["price"] = updatedProduct.getPrice();
    jsonData["stockQuantity"] = updatedProduct.getStockQuantity();
    jsonData["description"] = updatedProduct.getDescription();

    Json::StreamWriterBuilder writer;
    std::string data = Json::writeString(writer, jsonData);
    std::string url = db_url + "/products/" + productID; // Update to your CouchDB endpoint

    std::string response = performRequest(url, "PUT", data);
    return !response.empty(); // Return true if the response is valid
}

// Delete a product from CouchDB
bool Database::deleteProduct(const std::string& productID) {
    std::string url = db_url + "/products/" + productID; // Update to your CouchDB endpoint
    std::string response = performRequest(url, "DELETE", "");
    return !response.empty(); // Return true if the response is valid
}
