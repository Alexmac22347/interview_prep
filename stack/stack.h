#include <string>
#include <vector>

class Stack {
    public:
        void runTests();

    private:
        bool validParentheses(std::string s);
        bool minStack(std::string s);
        int evalRPN(std::vector<std::string>& tokens);
        std::vector<int> dailyTemperatures(std::vector<int>& temperatures);
        bool isPartOfFleet(int fleet_start, int fleet_speed, \
            int car_pos, int car_speed, int target);
        int carFleet(int target, std::vector<int>& position, std::vector<int>& speed);
        int largestRectangleArea(std::vector<int>& heights);
};
