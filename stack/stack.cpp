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
    std::vector<int> temps = {30, 38, 30, 36, 35, 40, 28};
    auto ret = dailyTemperatures(temps);
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

std::vector<int> Stack::dailyTemperatures(std::vector<int>& temperatures) {
    std::vector<int> ret(temperatures.size(), 0);

    // loop from left to write.
    // if the new number is greater than the one on the stack,
    // then pop the stack until we find a number greater.
    // for each item we pop from the stack, record the number of times
    // the stack was popped into the output array.
    // stack records idx, temperature
    //
    // [30, 38, 30, 36, 35, 40, 28]
    // s[<1,30>], ret[0, 0, 0, 0, 0, 0, 0]
    // s[<1,38>], ret[1, 0, 0, 0, 0, 0, 0,]
    // s[<1,38>, <2,30>]
    // s[<1,38>, <3,36>] ret[1,0,1, 0, 0, 0, 0]
    // s[<1,38>, <3,36>, <4,35>]
    std::stack<std::tuple<int,int>> s;
    for (unsigned int i = 0; i < temperatures.size(); i++) {
        if (s.empty()) {
            s.push(std::tuple<int,int>(i,temperatures[i]));
            continue;
        }

        while (!s.empty()
                && temperatures[i] > std::get<1>(s.top())) {
            int update_idx = std::get<0>(s.top());
            ret[update_idx] = i - update_idx;
            s.pop();
        }
        s.push(std::tuple<int,int>(i,temperatures[i]));
    }

    return ret;
}
