#include "User.h"

// Get the username
std::string User::getUsername() const {
    return username;
}

// Get the user role
std::string User::getRole() const {
    return role;
}

// Set the username
void User::setUsername(const std::string& username) {
    this->username = username;
}

// Set the password
void User::setPassword(const std::string& password) {
    this->password = password;
}

// Set the role
void User::setRole(const std::string& role) {
    this->role = role;
}

// Authenticate the user by comparing the provided password
bool User::authenticate(const std::string& password) const {
    return this->password == password; // Simple password check
}
