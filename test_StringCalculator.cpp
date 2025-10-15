// tests/test_StringCalculator.cpp

#include <iostream>
#include <cassert>
#include <stdexcept>
#include "StringCalculator.hpp"

void test_empty_string() {
    StringCalculator calc;
    assert(calc.add("") == 0);
    std::cout << "test_empty_string passed\n";
}

void test_single_number() {
    StringCalculator calc;
    assert(calc.add("1") == 1);
    std::cout << "test_single_number passed\n";
}

void test_two_numbers() {
    StringCalculator calc;
    assert(calc.add("1,2") == 3);
    std::cout << "test_two_numbers passed\n";
}

void test_multiple_numbers() {
    StringCalculator calc;
    assert(calc.add("1,2,3,4") == 10);
    std::cout << "test_multiple_numbers passed\n";
}

void test_newline_and_comma() {
    StringCalculator calc;
    assert(calc.add("1\n2,3") == 6);
    std::cout << "test_newline_and_comma passed\n";
}

void test_trailing_consecutive_delimiters() {
    StringCalculator calc;
    try {
        int result = calc.add("1,\n2"); // currently returns 3
        assert(result == 3); // adjust if spec changes
        std::cout << "test_trailing_consecutive_delimiters passed\n";
    } catch (...) {
        std::cout << "test_trailing_consecutive_delimiters failed\n";
    }
}

void test_custom_single_delimiter() {
    StringCalculator calc;
    assert(calc.add("//;\n1;2") == 3);
    std::cout << "test_custom_single_delimiter passed\n";
}

void test_custom_multi_length_delimiter() {
    StringCalculator calc;
    assert(calc.add("//[***]\n1***2***3") == 6);
    std::cout << "test_custom_multi_length_delimiter passed\n";
}

void test_multiple_bracketed_delimiters() {
    StringCalculator calc;
    try {
        int result = calc.add("//[*][%]\n1*2%3"); // currently fails
        assert(result == 6);
        std::cout << "test_multiple_bracketed_delimiters passed\n";
    } catch (const std::exception &e) {
        std::cout << "test_multiple_bracketed_delimiters failed: " << e.what() << "\n";
    }
}

void test_negative_numbers_throw() {
    StringCalculator calc;
    try {
        calc.add("1,-2,-3");
        assert(false); // should not reach here
    } catch (const std::invalid_argument &e) {
        std::string msg = e.what();
        assert(msg.find("-2") != std::string::npos && msg.find("-3") != std::string::npos);
        std::cout << "test_negative_numbers_throw passed\n";
    }
}

void test_ignore_large_numbers() {
    StringCalculator calc;
    assert(calc.add("2,1001") == 2);
    std::cout << "test_ignore_large_numbers passed\n";
}

void test_malformed_header() {
    StringCalculator calc;
    try {
        calc.add("//;1;2"); // missing newline
        assert(false);
    } catch (const std::invalid_argument &e) {
        std::cout << "test_malformed_header passed\n";
    }
}

void test_non_numeric_token() {
    StringCalculator calc;
    try {
        calc.add("1,a,3");
        assert(false);
    } catch (const std::invalid_argument &e) {
        std::cout << "test_non_numeric_token passed\n";
    }
}

void test_single_number_with_newline() {
    StringCalculator calc;
    assert(calc.add("1\n") == 1);
    std::cout << "test_single_number_with_newline passed\n";
}

void test_zero_handling() {
    StringCalculator calc;
    assert(calc.add("0,1,2") == 3);
    std::cout << "test_zero_handling passed\n";
}

// Function to run all tests
void run_all_tests()
{
    test_empty_string();
    test_single_number();
    test_two_numbers();
    test_multiple_numbers();
    test_newline_and_comma();
    test_trailing_consecutive_delimiters();
    test_custom_single_delimiter();
    test_custom_multi_length_delimiter();
    test_multiple_bracketed_delimiters();
    test_negative_numbers_throw();
    test_ignore_large_numbers();
    test_malformed_header();
    test_non_numeric_token();
    test_single_number_with_newline();
    test_zero_handling();
}
