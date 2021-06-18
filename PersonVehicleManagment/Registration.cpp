#include <iostream>
#include <string.h>
#include "Registration.h"

bool Registration::isValid(const char* str){

    if(str == nullptr){
        throw std::invalid_argument("Null pointer");
    }

    std::size_t size = 0;
    while(str[size++]){}
    size --;                // should not count '\0'

    if(size < 7 || size > 8){
        return false;
    }

    std::size_t index = 0;

    // is first symbol letter
    if(isalpha(str[index])){
        index++;
    }else{
        return false;
    }

    // if exist, is second symbol letter
    if(isalpha(str[index])){
        index++;
    }

    // are following 4 symbols digits
    for(std::size_t i = 0; i < 4; i++){
        if(!isdigit(str[index])){
            return false;
        }
        index++;
    }

    // are following 2 symbols letters
    for(std::size_t i = 0; i < 2; i++){
        if(isalpha(str[index])){
            index++;
        }else{
            return false;
        }
    }

    if(index != strlen(str)){
        return false;
    }

    return true;
}

Registration::Registration(const char* str){

    if(str == nullptr){
        throw std::invalid_argument("Null pointer");
    }

    *this = str;
}

Registration& Registration::operator=(const char* str){

    if(str == nullptr){
        throw std::invalid_argument("Null pointer");
    }

    if(isValid(str)){
        size_t size = 0;
        while(str[size++]){}
        size--;
        for(size_t j = 0; j < size; j++){
            regNumber[j] = str[j];
        }
        regNumber[size] = '\0';
        size_ = size;
    }else{
        throw std::invalid_argument("Invalid registration number.");
    }
    return *this;
}

Registration& Registration::operator=(const Registration& other){

    if(this == &other){
        return *this;
    }

    size_ = other.size_;

    for(size_t j = 0; j < size_; j++){
        regNumber[j] = other.regNumber[j];
    }
    regNumber[size_] = '\0';

    return *this;
}

bool Registration::operator==(const char* str) const{

    if(str == nullptr){
        throw std::invalid_argument("Null pointer");
    }

    size_t size = strlen(str);

    if(size_ != size){
        return false;
    }

    for(size_t i = 0; i < size; i++){
        if(str[i] != regNumber[i]){
            return false;
        }
    }

    return true;
}

bool Registration::operator==(const Registration& other) const{


    if(strlen(regNumber) != other.size_){
        return false;
    }

    for(size_t i = 0; i < size_; i++){
        if(regNumber[i] != other.regNumber[i]){
            return false;
        }
    }

    return true;
}

const char* Registration::getNumber() const{
    return regNumber;
}
