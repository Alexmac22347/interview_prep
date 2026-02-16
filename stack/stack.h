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
};
