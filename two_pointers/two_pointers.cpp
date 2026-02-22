#include <span>
#include <string>
#include <locale>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "two_pointers.h"

void TwoPointers::runTests() {
    std::vector<int> numbers{-4,-1,-1,0,1,2};
    std::vector<std::vector<int>> ret = threeSum(numbers);
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
