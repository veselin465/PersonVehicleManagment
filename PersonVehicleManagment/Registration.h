#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <iostream>

class Registration{

private:
    char regNumber[9];
    std::size_t size_;
    bool isValid(const char* str);

public:

    Registration() = delete;

    Registration(const char* str);

    Registration& operator=(const char* str);

    Registration& operator=(const Registration& other);

    bool operator==(const char* str) const;

    bool operator==(const Registration& other) const;

    const char* getNumber() const;

};

#endif // REGISTRATION_H
