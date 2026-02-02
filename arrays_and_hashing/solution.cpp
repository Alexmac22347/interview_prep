#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#include "solution.h"

void Solution::runTests() {
    std::vector<std::string> anagrams = {"act", "cat", "tops", "stop", "hat", "cat", "pots"};

    auto a = groupAnagrams(anagrams);

    for (auto anagram_list : a) {
        std::cout << "group:" << std::endl;
        for (auto s : anagram_list) {
            std::cout << s << ", ";
        }
        std::cout << std::endl;
    }
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
    
    int s_count[26] = {0};
    int t_count[26] = {0};

    for (unsigned int i = 0; i < s.length(); i++) {
        s_count[s[i] - 'a']++;
        t_count[t[i] - 'a']++;
    }

    for (unsigned int i = 0; i < 26; i++) {
        if (s_count[i] != t_count[i]) {
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

std::vector<
    std::vector<
        std::string>> Solution::groupAnagrams(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> retval;
    // anagram "id" (sorted anagram) to list of matching anagrams
    std::unordered_map<std::string, std::vector<std::string>> anagrams;

    for (std::string& str : strs) {
       std::string id = std::string(str);
       std::sort(id.begin(), id.end());
       anagrams[id].push_back(str);
    }

    for (auto it : anagrams) {
        retval.push_back(it.second);
    }

    return retval;
}
