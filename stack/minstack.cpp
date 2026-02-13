#include "minstack.h"

#include <stack>

MinStack::MinStack() {
}

void MinStack::push(int val) {
    _s.push(val);

    if (_min_s.size() == 0) {
        _min_s.push(val);
    } else {
        int cur_min = _min_s.top();
        if (val < cur_min) {
            _min_s.push(val);
        } else {
            _min_s.push(cur_min);
        }
    }
}

void MinStack::pop() {
    _s.pop();
    _min_s.pop();
}

int MinStack::top() {
    return _s.top();
}

int MinStack::getMin() {
    return _min_s.top();
}
