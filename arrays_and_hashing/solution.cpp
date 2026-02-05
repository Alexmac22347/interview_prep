#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <string_view>
#include <cctype>
#include <utility>

#include "solution.h"

void Solution::runTests() {
    //std::vector<std::string> message{""};
    //std::vector<std::string> message{};
    //std::vector<std::string> message{",,"};
    //std::vector<std::string> message{"hi"};
    std::vector<std::string> message{"####","message,",",,,,"};
    //std::vector<std::string> message{"mge,",",,,,"};

    std::string encoded = encode(message);
    std::cout << "encoded: " << encoded << std::endl;

    std::vector<std::string> decoded = decode(encoded);
    std::cout << "decoded message:" << std::endl;
    for (std::string& s : decoded) {
        std::cout << s << std::endl;
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

std::vector<int> Solution::topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> counts;

    for (int& num : nums) {
        if (counts.find(num) == counts.end()) {
            counts[num] = 1;
        } else {
            counts[num]++;
        }
    }

    // i hate sorting and i hate dragging in more
    // complex datatypes. to find the largest k counts:
    // find the max that is not in retval, and add it to retval,
    // until retval.length() == k
    std::vector<int> retval;
    for (int i = 0; i < k; i++) {
        int max = 0;
        int max_key = 0;
        for (auto& count : counts) {
            if (count.second > max) {
                max = count.second;
                max_key = count.first;
            }
        }

        retval.push_back(max_key);
        counts.erase(max_key);
    }

    return retval;
}

std::string Solution::encode(std::vector<std::string>& strs) {
    // prepend each string with [str_len]ENCODE_START
    // if ENCODE_START is in the string, escape it
    std::ostringstream ss;
    for (std::string& str : strs) {
        ss << str.length() << ENCODE_START;
        for (char c : str) {
            ss << c;
        }
    }

    return ss.str();
}

std::vector<std::string> Solution::decode(std::string s) {
    std::vector<std::string> retval;

    std::ostringstream num_ss;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (std::isdigit(s[i])) {
            num_ss << s[i];
        } else {
            int str_len = std::stoi(num_ss.str());
            try {
                std::string substr = s.substr(i+1, str_len);
                retval.push_back(std::move(substr));
                num_ss.str("");
                num_ss.clear();
                i += str_len;
            } catch (...) {
                // this is for neetcode
                // i don't care about error handling muahahah
                std::cout << "whoops" << std::endl;
                exit(-1);
            }
        }
    }

    return retval;
}
