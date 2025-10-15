#ifndef STRING_CALCULATOR_HPP
#define STRING_CALCULATOR_HPP

#include <string>

class StringCalculator {
public:
    // Main function: add numbers given as a formatted string
    int add(const std::string &numbers) const;

private:
    // Helper functions (each small, low complexity)
    std::string parseDelimiter(std::string &input) const;
    int computeSum(const std::string &input, const std::string &delimiter) const;
};

#endif
