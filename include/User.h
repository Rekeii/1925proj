#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string role;

public:
    std::string getUsername() const;
    std::string getRole() const;
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setRole(const std::string& role);
    bool authenticate(const std::string& password) const;
};

#endif
