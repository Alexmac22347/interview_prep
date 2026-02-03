#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#include "solution.h"

void Solution::runTests() {
    //std::vector<std::string> message{""};
    //std::vector<std::string> message{",,"};
    //std::vector<std::string> message{"hi"};
    std::vector<std::string> message{",test","message,",",,,,"};
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
    if (strs.size() == 0) {
        return "";
    }
    // use ENCODE_SEPARATOR to separate strings.
    // if ENCODE_SEPARATOR appears in strs, prepend
    // escape character 
    std::ostringstream ss;
    for (unsigned int i = 0; i < strs.size(); i++) {
        for (char c : strs[i]) {
            if (c == ENCODE_SEPARATOR) {
                ss << ENCODE_ESCAPE;
            }
            ss << c;
        }

        // do not add a comma after the last string
        if (i != strs.size()-1) {
            ss << ENCODE_SEPARATOR;
        }
    }

    return ss.str();
}

std::vector<std::string> Solution::decode(std::string s) {
    std::vector<std::string> retval;
    if (s == "") {
        retval.push_back("");
        return retval;
    }
    std::ostringstream ss;
    
    for (unsigned int i = 0; i <= s.size(); ) {
        if (i == s.size() \
                // edge case where s is completely empty
                && s.size() > 0) {
            retval.push_back(ss.str());
            break;
        }
        if  (s[i] == ENCODE_ESCAPE \
                && i+1 < s.size() \
                && s[i+1] == ENCODE_SEPARATOR) {
            ss << ENCODE_SEPARATOR;
            i+=2;
        } else if (s[i] == ENCODE_SEPARATOR) {
            retval.push_back(ss.str());
            ss.str("");
            ss.clear();
            i++;
        } else {
            ss << s[i];
            i++;
        }
    }

    return retval;
}
