#include <stack>

class MinStack {
public:
    MinStack();
    void push(int val);
    void pop();
    int top();
    int getMin();
private:
    std::stack<int> _s;
    std::stack<int> _min_s;
};
