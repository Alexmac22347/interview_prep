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
    //std::vector<int> rects = {3,6,5,7,4,8,1,0};
    std::vector<int> rects = {7,1,7,2,2,4};
    int largestRect = largestRectangleArea(rects);
    std::cout << largestRect << std::endl;
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

bool Stack::isPartOfFleet(int fleet_pos, int fleet_speed, \
        int car_pos, int car_speed, int target) {
    if (car_speed <= fleet_speed) {
        return false;
    }

    int fleet_remaining_dist = target - fleet_pos;
    int car_remaining_dist = target - car_pos;
    // ugh, so actuall we compare the real times it takes.
    // i was thinking as time being a discrete tick, so
    // a car taking 2.33, and a car taking 2.66 both reach at the
    // same time and form a fleet but after looking at the solution
    // apparently this is not true, and time is continuous
    double time_remaining_until_fleet_reaches_end = \
        (fleet_remaining_dist * 1.0) / fleet_speed;
    double time_remaining_until_car_reaches_end = \
        (car_remaining_dist * 1.0) / car_speed;
    return time_remaining_until_car_reaches_end
        <= time_remaining_until_fleet_reaches_end;
}

int Stack::carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
    std::vector<std::pair<int,int>> position_and_speeds;
    for (unsigned int i = 0; i < position.size(); i++) {
        position_and_speeds.emplace_back(std::pair<int,int>(position[i], speed[i]));
    }

    std::sort(position_and_speeds.begin(), position_and_speeds.end(),
            [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

    int num_fleets = 1;
    int fleet_pos = position_and_speeds.front().first;
    int fleet_speed = position_and_speeds.front().second;

    // we start from the furthest car and assume that is the first fleet.
    // we then look at the car behind it, and either add it to
    // that fleet and then look at the next car, or if it doesnt catch
    // up in time, we consider the car behind as a new fleet, and the
    // continue looking behind.
    for (unsigned int i = 1; i < position_and_speeds.size(); i++) {
        int car_pos = position_and_speeds[i].first;
        int car_speed = position_and_speeds[i].second;;
        if (isPartOfFleet(
                    fleet_pos,
                    fleet_speed,
                    car_pos,
                    car_speed,
                    target)) {
            continue;
        } else {
            // this car didnt catch up.
            // its part of a new fleet and we will
            // now compare this car to the one before it.
            num_fleets++;
            fleet_pos = car_pos;
            fleet_speed = car_speed;
        }
    }

    return num_fleets;
}

int Stack::largestRectangleArea(std::vector<int>& heights) {
    /*
     * Use a stack to keep track of the
     * heights that we are extending to the right.
     * if we reach a bar that is lower than stack.top(),
     * we're done extending that bar and can pop it.
     * whenever we pop it, we should calculate its area
     * and see if it beat the curmax.
     * we can keep popping until the stack is either empty,
     * or we reach a height that is lower.
     *
     * as we go through the heights,
     * we add onto the stack
     * the current height, and its index extended out to the left.
     * it's start index is the index of the last thing we popped
     * from the stack.
     *
     * at the end, whatever is left in the stack represents rectangles
     * that go all the way to the right. pop everything in the stack
     * and see if they but curmax.
     *
     * example [7,1,7,2,2,4]
     *
     * .   .
     * .   .
     * .   .
     * .   .     .
     * .   .     .
     * .   . . . .
     * . . . . . .
     * 0 1 2 3 4 5
     *
     * curmax=0
     * 0. stack <0,7>, calculated_height=7 -> curmax=7 // nothing in stack, so just
     *                          // push the current height/index
     * 1. stack <0,1>, curmax=7 // smaller than stack.top ->
     *                          // pop stack.top and calculate height.
     *                          // set new curmax if greater.
     *                          // since curheight < stack.top,
     *                          // we can push <stack.top.index, curheight>
     * 2. stack <0,1>, <2,7> curmax=7 calculated_height=7
     * 3. stack <0,1>, <2,2> curmax=7 calculated_height=4
     * 4. stack <0,1>, <2,2> curmax=7 calculated_height=6
     * 5. stack <0,1>, <2,2>, <5,4> curmax=7 calculated_height=4
     *
     * go throught the remaining stack and calculate heights.
     * i dont feel like writing this part its pretty simple though.
     */
    int curmax = 0;
    // <idx, height>
    std::stack<std::pair<int,int>> s;

    for (unsigned int i = 0; i < heights.size(); i++) {
        int curheight = heights.at(i);

        int start_idx = i;
        while (!s.empty() && s.top().second > curheight) {
            std::pair<int,int> idx_height = s.top();
            s.pop();
            start_idx = idx_height.first;
            int size = (i-idx_height.first) * idx_height.second;
            if (size > curmax) {
                curmax = size;
            }
        }

        s.push(std::pair<int,int>(start_idx, curheight));
    }

    while (!s.empty()) {
        std::pair<int,int> idx_height = s.top();
        s.pop();
        int width = heights.size() - idx_height.first;
        int size = (width * idx_height.second);
        if (size > curmax) {
            curmax = size;
        }
    }

    return curmax;
}
