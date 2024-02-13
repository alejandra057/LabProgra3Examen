#include "invalidarateexception.h"
#include <iostream>
#include <exception>
#include <string>

class InvalidRateException : public std::exception {
private:
    int rate;

public:
    InvalidRateException(int rate) : rate(rate) {}

    const char* what() const noexcept override {
        static std::string message;
        message = "RATE " + std::to_string(rate) + " is not a valid number for a review";
        return message.c_str();
    }
};
