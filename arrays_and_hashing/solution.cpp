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
    std::vector<int> nums{2,20,4,10,3,4,5};

    int longestSeq = longestConsecutive(nums);
    std::cout << "longestSeq: " << longestSeq << std::endl;
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

std::vector<int> Solution::productExceptSelf(std::vector<int>& nums) {
    std::vector<int> retval;
    if (nums.size() == 0) {
        return retval;
    }

    std::vector<int> prefix(nums.size());
    std::vector<int> suffix(nums.size());

    prefix[0] = nums[0];
    suffix[nums.size()-1] = nums[nums.size()-1];

    for (unsigned int i = 1; i < nums.size(); i++) {
        prefix[i] = prefix[i-1]*nums[i];
    }
    for (int i = nums.size()-2; i >= 0; i--) {
        suffix[i] = nums[i]*suffix[i+1];
    }

    for (unsigned int i = 0; i < nums.size(); i++) {
        if (i == 0) {
            retval.push_back(suffix[i+1]);
        } else if (i == nums.size()-1) {
            retval.push_back(prefix[i-1]);
        } else {
            retval.push_back(prefix[i-1]*suffix[i+1]);
        }
    }

    return retval;
}

bool Solution::isValidSudoku(std::vector<std::vector<char>>& board) {
    /*
     * Not sure if its the optimal solution, but im going to use a "hashmap"
     * ie a list of 10 bools to keep track of which numbers we've seen.
     * a number just hashes to itself, ie the number is the index in the array.
     * I'll loop through each row. Then loop through each column. Then through
     * each 3x3 box.
     * I wonder if theres a way I can combine certain checks. Because I am looking
     * at each tile 3 times (once checking the rows, then columns, then boxes).
     * I mean 3 is a constant though so it doesnt matter much.
     */
    bool seen_numbers[10] = {false};

    // for each row, check for dups
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[i].size(); j++) {
            char board_char = board[i][j];
            if (board_char == SUDOKU_EMPTY_TILE_MARKER) {
                continue;
            }
            unsigned int board_num = board_char - '0';
            if (seen_numbers[board_num]) {
                return false;
            }
            seen_numbers[board_num] = true;
        }
        std::fill(std::begin(seen_numbers), std::end(seen_numbers), false);
    }

    // for each column, check for dups
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[i].size(); j++) {
            char board_char = board[j][i];
            if (board_char == SUDOKU_EMPTY_TILE_MARKER) {
                continue;
            }
            unsigned int board_num = board_char - '0';
            if (seen_numbers[board_num]) {
                return false;
            }
            seen_numbers[board_num] = true;
        }
        std::fill(std::begin(seen_numbers), std::end(seen_numbers), false);
    }

    // for each box, check for dups
    // loop through each box
    for (unsigned int i = 0; i < board.size(); i += SUDOKU_BOARD_SIZE) {
        for (unsigned int j = 0; j < board[i].size(); j += SUDOKU_BOARD_SIZE) {
            // loop inside the box
            for (unsigned int b_i = i; b_i < i+SUDOKU_BOARD_SIZE; b_i++) {
                for (unsigned int b_j = j; b_j < j+SUDOKU_BOARD_SIZE; b_j++) {
                    char board_char = board[b_i][b_j];
                    if (board_char == SUDOKU_EMPTY_TILE_MARKER) {
                        continue;
                    }
                    unsigned int board_num = board_char - '0';
                    if (seen_numbers[board_num]) {
                        return false;
                    }
                    seen_numbers[board_num] = true;
                }
            }
            std::fill(std::begin(seen_numbers), std::end(seen_numbers), false);
        }
    }
    return true;
}

int Solution::longestConsecutive(std::vector<int>& nums) {
    // this holds any ints that are the start of a sequence
    // and the length of said sequence
    std::unordered_map<int, int> starts;
    // nums in a set for constant lookup.
    std::set<int> nums_set(nums.begin(), nums.end());
    for (unsigned int i = 0; i < nums.size(); i++) {
        if (nums_set.find(nums[i]-1) == nums_set.end()) {
            // if this is a start of a sequence, lets find out
            // how long it is.
            starts[nums[i]] = 1;
            int j = nums[i] + 1;
            while(nums_set.find(j) != nums_set.end()) {
                j++;
                starts[nums[i]] += 1;
            }
        } else {
            continue;
        }
    }

    int max_seq_length = 0;
    for (auto seq : starts) {
        if (seq.second > max_seq_length) {
            max_seq_length = seq.second;
        }
    }
    return max_seq_length;
}
