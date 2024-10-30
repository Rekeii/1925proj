#include <napi.h>
#include "Product.h"
#include "Inventory.h"

// Assuming you have a global Inventory object
Inventory inventory;

Napi::Object CreateProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string productID = info[0].As<Napi::String>().Utf8Value();
    std::string name = info[1].As<Napi::String>().Utf8Value();
    std::string category = info[2].As<Napi::String>().Utf8Value();
    double price = info[3].As<Napi::Number>().DoubleValue();
    int stockQuantity = info[4].As<Napi::Number>().Int32Value();
    std::string description = info[5].As<Napi::String>().Utf8Value();

    Product product(productID, name, category, price, stockQuantity, description);
    if (!inventory.addProduct(product)) {
        Napi::Object errorObj = Napi::Object::New(env);
        errorObj.Set("error", Napi::String::New(env, "Product already exists"));
        return errorObj; // Return an error object
    }

    // Return success message
    Napi::Object result = Napi::Object::New(env);
    result.Set("message", "Product added successfully");
    return result;
}


Napi::Array GetAllProducts(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Assuming 'inventory' is an instance of your Inventory class
    const std::vector<Product>& products = inventory.getAllProducts(); // This should return the current products

    Napi::Array result = Napi::Array::New(env, products.size());

    for (size_t i = 0; i < products.size(); i++) {
        Napi::Object productObj = Napi::Object::New(env);
        productObj.Set("productID", products[i].getProductID());
        productObj.Set("name", products[i].getName());
        productObj.Set("category", products[i].getCategory());
        productObj.Set("price", products[i].getPrice());
        productObj.Set("stockQuantity", products[i].getStockQuantity());
        productObj.Set("description", products[i].getDescription());
        result.Set(i, productObj);
    }

    return result;
}



Napi::Object RemoveProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // Check if the correct number of arguments is provided
    if (info.Length() < 1) {
        Napi::Object errorObj = Napi::Object::New(env);
        errorObj.Set("error", Napi::String::New(env, "Product ID expected"));
        return errorObj;  // Return an error object
    }

    std::string productID = info[0].As<Napi::String>();
    bool success = inventory.removeProduct(productID);
    
    // Create an object to return the success status
    Napi::Object result = Napi::Object::New(env);
    result.Set("success", Napi::Boolean::New(env, success));
    return result;
}

Napi::Object UpdateProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Check if the correct number of arguments is provided
    if (info.Length() < 6) {
        Napi::Object errorObj = Napi::Object::New(env);
        errorObj.Set("error", Napi::String::New(env, "Invalid arguments"));
        return errorObj;  // Return an error object
    }

    std::string productID = info[0].As<Napi::String>();
    Product updatedProduct(
        productID,
        info[1].As<Napi::String>(),
        info[2].As<Napi::String>(),
        info[3].As<Napi::Number>().DoubleValue(), // Get the double value for price
        info[4].As<Napi::Number>().Int32Value(),  // Get the int value for stockQuantity
        info[5].As<Napi::String>()
    );

    bool success = inventory.updateProduct(productID, updatedProduct);
    
    // Create an object to return the success status
    Napi::Object result = Napi::Object::New(env);
    result.Set("success", Napi::Boolean::New(env, success));
    return result;
}




Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("createProduct", Napi::Function::New(env, CreateProduct));
    exports.Set("getAllProducts", Napi::Function::New(env, GetAllProducts));
    exports.Set("removeProduct", Napi::Function::New(env, RemoveProduct));
    exports.Set("updateProduct", Napi::Function::New(env, UpdateProduct));
    return exports;
}

NODE_API_MODULE(cpp_inventory, Init)
