#include <string>
#include <iostream>
#include <stack>
#include <algorithm>

#include "stack.h"
#include "minstack.h"

static const char OPEN_PAR = '(';
static const char CLOSE_PAR = ')';
static const char OPEN_SQUARE = '[';
static const char CLOSE_SQUARE = ']';
static const char OPEN_SQIGGLE = '{';
static const char CLOSE_SQIGGLE = '}';

void Stack::runTests() {
    std::vector<std::string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    std::cout << evalRPN(tokens) << std::endl;
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

int Stack::evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> s;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];

        if (token == "+") {
            int x = s.top();
            s.pop();
            int y = s.top();
            s.pop();
            s.push(x+y);
        } else if (token == "-") {
            int x = s.top();
            s.pop();
            int y = s.top();
            s.pop();
            s.push(y-x);
        } else if (token == "/") {
            int x = s.top();
            s.pop();
            int y = s.top();
            s.pop();
            s.push(y/x);
        } else if (token == "*") {
            int x = s.top();
            s.pop();
            int y = s.top();
            s.pop();
            s.push(y*x);
        } else {
            s.push(std::stoi(token));
        }
    }

    if (s.size() != 1) {
        // uh oh
    }
    return s.top();;
}
