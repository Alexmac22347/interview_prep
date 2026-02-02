#include <vector>
#include <string>

class Solution {
    public:
        void runTests();

    private:
        bool hasDuplicate(std::vector<int>& nums);
        bool isAnagram(std::string s, std::string t);
        std::vector<unsigned int> twoSum(std::vector<int>& num, int target);
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
};
