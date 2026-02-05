#include <vector>
#include <string>

class Solution {
    public:
        void runTests();

    private:
        static const char ENCODE_START = '#';

        bool hasDuplicate(std::vector<int>& nums);
        bool isAnagram(std::string s, std::string t);
        std::vector<unsigned int> twoSum(std::vector<int>& num, int target);
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
        std::vector<int> topKFrequent(std::vector<int>& nums, int k);
        std::string encode(std::vector<std::string>& strs);
        std::vector<std::string> decode(std::string s);
        std::vector<int> productExceptSelf(std::vector<int>& sums);
};
