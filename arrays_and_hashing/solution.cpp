#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <cmath>

#include "solution.h"

void Solution::runTests() {
    std::vector<int> nums1{3,4,5,6};
    int target1 = 7;

    std::vector<int> nums2{4,5,6};
    int target2 = 10;

    std::vector<int> nums3{5,5};
    int target3 = 10;

    auto a = twoSum(nums1, target1);
    auto b = twoSum(nums2, target2);
    auto c = twoSum(nums3, target3);
}

bool Solution::hasDuplicate(std::vector<int>& nums) {
    std::set<int> s;
    for (int& num : nums) {
        if (s.find(num) == s.end()){
            s.insert(num);
        } else {
            return true;
        }
    }
    return false;
}

bool Solution::isAnagram(std::string s, std::string t) {
    if (s.length() != t.length()) {
        return false;
    }

    std::unordered_map<char, int> s_map;
    std::unordered_map<char, int> t_map;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s_map.find(s.at(i)) == s_map.end()) {
            s_map.insert({s.at(i), 0});
        }
        else {
            s_map[s.at(i)] = s_map[s.at(i)] + 1;
        }
        if (t_map.find(t.at(i)) == t_map.end()) {
            t_map.insert({t.at(i), 0});
        }
        else {
            t_map[s.at(i)] = t_map[s.at(i)] + 1;
        }
    }

    for (auto it : s_map) {
        if (t_map.find(it.first) == t_map.end()) {
            return false;
        } else if (t_map[it.first] != it.second) {
            return false;
        }
    }

    return true;
}

std::vector<unsigned int> Solution::twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, unsigned int> m;
    for (unsigned int i = 0; i < nums.size(); i++) {
        int diff = target - nums[i];
        if (m.find(diff) != m.end()) {
            return {m.at(diff), i};
        }
        else {
            m[nums[i]] = i;
        }
    }
    return std::vector<unsigned int>{};
}
