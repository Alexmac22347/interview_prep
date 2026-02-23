#include <span>
#include <string>
#include <stack>
#include <locale>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "two_pointers.h"

void TwoPointers::runTests() {
    std::vector<int> heights{5,4,1,2};
    int ret = trap(heights);
    std::cout << ret << std::endl;
}

bool TwoPointers::isPalindrome(std::string s) {
    std::locale l = std::locale::classic();
    unsigned int l_pointer = 0;
    unsigned int r_pointer = s.size() - 1;
    for(;;) {
        while (l_pointer < s.size() && !std::isalnum(s[l_pointer]))
            l_pointer++;
        while (r_pointer > 0 && !std::isalnum(s[r_pointer]))
            r_pointer--;
        if (l_pointer >= r_pointer)
            break;
        if (std::tolower(s[l_pointer], l) != std::tolower(s[r_pointer], l))
            return false;

        l_pointer++;
        r_pointer--;
    }


    return true;
}

std::vector<int> TwoPointers::twoSum(std::span<int> numbers, int target) {
    // numbers is non-decreasing
    int idx1 = 0;
    int idx2 = numbers.size()-1;

    for(;;) {
        int sum = numbers[idx1]+numbers[idx2];
        if (sum == target) {
            return std::vector<int>{idx1,idx2};
        } else if (sum < target) {
            idx1++;
        } else {
            idx2--;
        }
        if (idx1 >= idx2) {
            return std::vector<int>();
        }
    }
}

std::vector<std::vector<int>> TwoPointers::threeSum(std::span<int> nums) {
    std::vector<std::vector<int>> ret;

    std::sort(nums.begin(), nums.end());

    for (unsigned int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0)
            break;

        if (i > 0 && nums[i-1] == nums[i])
            continue;

        unsigned int l = i+1;
        unsigned int r = nums.size()-1;
        while (l<r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
               ret.push_back({nums[i], nums[l], nums[r]});
               l++;
               r--;
               while (l < r && nums[l] == nums[l-1]) {
                    l++;
               }
            } else if (sum > 0) {
                r--;
            } else {
                l++;
            }
        }
    }
    return ret;
}

int TwoPointers::maxArea(std::vector<int>& heights) {
    int l = 0;
    int r = heights.size()-1;
    int curmax = 0;
    while (l<r) {
        int size = std::min(heights[l], heights[r]) * r-l;
        if (size > curmax)
            curmax = size;
        if (heights[l] < heights[r])
            l++;
        else
            r--;
    }
    return curmax;
}

int TwoPointers::trap(std::vector<int>& height) {
    // index, height
    std::stack<std::pair<int,int>> s;

    // from left to right, were going to build
    // a stack that contains the indices (and height)
    // of the edges of pools
    int maxheight = 0;
    for (unsigned int i = 0; i < height.size(); i++) {
        if (height[i] == 0)
            continue; // this aint gonna be a edge i can tell ya
        if (i > 0 && height[i] < height[i-1])
            continue; // if we just dropped down from something higher, this cant be an edge
        if (i < height.size()-1 && height[i] < height[i+1])
            continue; // likewise, if the next height is higher, this cant be an edge

        // lets remove the non boundaries from out stack.
        // we know its a boundary if we are taller than it,
        // __and there is something taller than it behind__.
        while (s.size() > 0
                && maxheight > s.top().second // without this, we might pop
                                      // an edge. this would cause us to
                                      // blindly pop the first and second
                                      // edge when  there is actually nothing
                                      // to the left to hold the water.
                                      //     *
                                      //   * *
                                      // * * *
                                      // ^^^^^
                && height[i] > s.top().second)
            s.pop();

        if (height[i] > maxheight)
            maxheight = height[i];

        s.push(std::pair<int,int>{i, height[i]});
    }

    if (s.size() <= 1)
        return 0;

    int total = 0;
    int rEdgeHeight = s.top().second;
    int rEdgeIdx = s.top().first;
    s.pop();
    while (s.size() > 0) {
        int poolHeight = std::min(s.top().second, rEdgeHeight);
        for (int i = rEdgeIdx-1; i > s.top().first; i--) {
            // in 4,3,1,2,
            // my algo will not detect 3 as an edge
            // and will keep 4 as the leftmost edge.
            // so we will calculate a negative height
            // since we use a height of 2, and take 2-3=-1
            // for index i=1.
            // im just going to skip these instead of fixing the algo
            if (poolHeight <= height[i])
                continue; // hack lol
            total += (poolHeight - height[i]);
        }

        rEdgeHeight = s.top().second;
        rEdgeIdx = s.top().first;
        s.pop();
    }
    return total;
}
