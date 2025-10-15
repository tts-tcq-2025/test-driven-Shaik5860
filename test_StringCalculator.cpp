#include "StringCalculator.hpp"
#include <cassert>
#include <iostream>

void test_empty_string_returns_zero() {
    StringCalculator calc;
    assert(calc.add("") == 0);
    std::cout << "✅ test_empty_string_returns_zero passed\n";
}

void test_single_number() {
    StringCalculator calc;
    assert(calc.add("1") == 1);
    std::cout << "✅ test_single_number passed\n";
}

void test_two_numbers() {
    StringCalculator calc;
    assert(calc.add("1,2") == 3);
    std::cout << "✅ test_two_numbers passed\n";
}

void test_newline_and_comma_mix() {
    StringCalculator calc;
    assert(calc.add("1\n2,3") == 6);
    std::cout << "✅ test_newline_and_comma_mix passed\n";
}

void test_custom_delimiter() {
    StringCalculator calc;
    assert(calc.add("//;\n1;2") == 3);
    std::cout << "✅ test_custom_delimiter passed\n";
}

void test_multi_length_delimiter() {
    StringCalculator calc;
    assert(calc.add("//[***]\n1***2***3") == 6);
    std::cout << "✅ test_multi_length_delimiter passed\n";
}

void test_ignore_large_numbers() {
    StringCalculator calc;
    assert(calc.add("2,1001") == 2);
    std::cout << "✅ test_ignore_large_numbers passed\n";
}

void test_negative_numbers_throw() {
    StringCalculator calc;
    try {
        calc.add("1,-2,3,-4");
    } catch (const std::invalid_argument &e) {
        std::string msg = e.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
        assert(msg.find("-2") != std::string::npos);
        assert(msg.find("-4") != std::string::npos);
        std::cout << "✅ test_negative_numbers_throw passed\n";
        return;
    }
    assert(false && "Expected exception not thrown");
}

void run_all_tests() {
    test_empty_string_returns_zero();
    test_single_number();
    test_two_numbers();
    test_newline_and_comma_mix();
    test_custom_delimiter();
    test_multi_length_delimiter();
    test_ignore_large_numbers();
    test_negative_numbers_throw();
    std::cout << "🎉 All tests passed successfully!\n";
}
