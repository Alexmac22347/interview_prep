#include <vector>
#include <string>

class ArraysAndHashing {
    public:
        void runTests();

    private:
        static const char ENCODE_START = '#';
        static const unsigned int SUDOKU_BOARD_SIZE = 3;
        static const char SUDOKU_EMPTY_TILE_MARKER = '.';

        bool hasDuplicate(std::vector<int>& nums);
        bool isAnagram(std::string s, std::string t);
        std::vector<unsigned int> twoSum(std::vector<int>& num, int target);
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
        std::vector<int> topKFrequent(std::vector<int>& nums, int k);
        std::string encode(std::vector<std::string>& strs);
        std::vector<std::string> decode(std::string s);
        std::vector<int> productExceptSelf(std::vector<int>& sums);
        bool isValidSudoku(std::vector<std::vector<char>>& board);
        int longestConsecutive(std::vector<int>& nums);
};
