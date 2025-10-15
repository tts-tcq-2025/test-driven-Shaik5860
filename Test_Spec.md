# StringCalculator Test Specification

| Tests | Requirement | Input | Expected Outcome | Notes / Coverage |
|-------|------------|---------|-------|-----------------|-----------------|
| 1 | Empty string returns 0 | `""` | `0` | Minimal failing test in TDD; covers `if(numbers.empty())` |
| 2 | Single number | `"1"` | `1` | Covers single number path |
| 3 | Two numbers, comma separator | `"1,2"` | `3` | Default delimiter ',' |
| 4 | Unknown amount of numbers | `"1,2,3,4"` | `10` | Loop through numbers |
| 5 | Handle new lines as delimiter | `"1\n2,3"` | `6` | Covers `[,\n]` split regex |
| 6 | Trailing/consecutive delimiters | `"1,\n2"` | `3` (spec-dependent) | Edge case; branch for empty tokens |
| 7 | Custom single-character delimiter | `"//;\n1;2"` | `3` | Parses header, overrides default delimiter |
| 8 | Custom multi-character delimiter | `"//[***]\n1***2***3"` | `6` | Bracketed delimiter parsing |
| 9 | Multiple bracketed delimiters | `"//[*][%]\n1*2%3"` | `6` (**currently fails**) | Multi-delimiter parsing; branch not covered yet |
| 10 | Negative numbers throw exception | `"1,-2,-3"` | Exception: `"negatives not allowed: -2, -3"` | Covers `if(num < 0)` true & false paths |
| 11 | Numbers >1000 ignored | `"2,1001"` | `2` | Covers `if(num <= 1000)` branch |
| 12 | Malformed header (missing newline) | `"//;1;2"` | Exception `"Invalid custom delimiter format"` | Branch not covered without test |
| 13 | Non-numeric token | `"1,a,3"` | Exception from `std::stoi` | Tests invalid token handling |
| 14 | Single number with newline | `"1\n"` | `1` | Edge case with trailing newline |
| 15 | Zero handling | `"0,1,2"` | `3` | Covers zero in sum |

