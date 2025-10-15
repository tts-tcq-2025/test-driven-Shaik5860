#include "StringCalculator.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <regex>

// --- Helper: Split string by multiple delimiters ---
static std::vector<std::string> split(const std::string &s, const std::string &delimPattern) {
    std::vector<std::string> tokens;
    std::regex regex(delimPattern);
    std::sregex_token_iterator it(s.begin(), s.end(), regex, -1);
    std::sregex_token_iterator end;
    for (; it != end; ++it) {
        if (!it->str().empty())
            tokens.push_back(it->str());
    }
    return tokens;
}

// --- Extract custom delimiter if present ---
std::string StringCalculator::parseDelimiter(std::string &input) const {
    std::string defaultDelimiter = "[,\n]";
    if (input.rfind("//", 0) == 0) { // starts with //
        size_t newlinePos = input.find('\n');
        if (newlinePos == std::string::npos)
            throw std::invalid_argument("Invalid custom delimiter format");

        std::string header = input.substr(2, newlinePos - 2);
        input = input.substr(newlinePos + 1); // strip header

        // Handle multi-length delimiters in square brackets
        if (header.size() >= 2 && header.front() == '[' && header.back() == ']') {
            header = header.substr(1, header.size() - 2); // remove []
            return std::regex_replace(header, std::regex(R"([\^\$\.\|\?\*\+\(\)\[\{\\])"), R"(\\$&)"); // escape regex
        }

        // Single char delimiter
        return std::regex_replace(header, std::regex(R"([\^\$\.\|\?\*\+\(\)\[\{\\])"), R"(\\$&)");
    }
    return defaultDelimiter;
}

// --- Compute total sum ---
int StringCalculator::computeSum(const std::string &input, const std::string &delimiter) const {
    auto numbers = split(input, delimiter);
    int sum = 0;
    std::vector<int> negatives;

    for (const auto &numStr : numbers) {
        if (numStr.empty()) continue;
        int num = std::stoi(numStr);
        if (num < 0) negatives.push_back(num);
        if (num <= 1000) sum += num;
    }

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << negatives[i];
        }
        throw std::invalid_argument(oss.str());
    }

    return sum;
}

// --- Main add() ---
int StringCalculator::add(const std::string &numbers) const {
    if (numbers.empty()) return 0;

    std::string input = numbers;
    std::string delimiter = parseDelimiter(input);
    return computeSum(input, delimiter);
}
