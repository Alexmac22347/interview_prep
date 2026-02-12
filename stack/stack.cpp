#include <string>
#include <iostream>
#include <stack>

#include "stack.h"

static const char OPEN_PAR = '(';
static const char CLOSE_PAR = ')';
static const char OPEN_SQUARE = '[';
static const char CLOSE_SQUARE = ']';
static const char OPEN_SQIGGLE = '{';
static const char CLOSE_SQIGGLE = '}';

void Stack::runTests() {
    std::string test_str1{"[[]]"};
    std::string test_str2{"[(]]"};
    std::string test_str3{"]"};
    std::string test_str4{"()()"};
    std::string test_str5{"()[()"};

    std::cout << test_str1 << ": " << validParentheses(test_str1) << std::endl;
    std::cout << test_str2 << ": " << validParentheses(test_str2) << std::endl;
    std::cout << test_str3 << ": " << validParentheses(test_str3) << std::endl;
    std::cout << test_str4 << ": " << validParentheses(test_str4) << std::endl;
    std::cout << test_str5 << ": " << validParentheses(test_str5) << std::endl;
}

bool Stack::validParentheses(std::string s) {
    std::stack<char> stack;
    for (unsigned int i = 0; i < s.length(); i++) {
        switch (s[i]) {
            case OPEN_PAR:
                stack.push(OPEN_PAR);
                continue;
            case CLOSE_PAR:
                if (stack.empty() || stack.top() != OPEN_PAR)
                    return false;
                stack.pop();
                continue;
            case OPEN_SQUARE:
                stack.push(OPEN_SQUARE);
                continue;
            case CLOSE_SQUARE:
                if (stack.empty() || stack.top() != OPEN_SQUARE)
                    return false;
                stack.pop();
                continue;
            case OPEN_SQIGGLE:
                stack.push(OPEN_SQIGGLE);
                continue;
            case CLOSE_SQIGGLE:
                if (stack.empty() || stack.top() != OPEN_SQIGGLE)
                    return false;
                stack.pop();
                continue;
            default:
                continue;
        }
    }
    if (stack.size() == 0) {
        return true;
    }
    return false;
}
