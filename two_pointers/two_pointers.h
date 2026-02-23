#include <string>
#include <span>
#include <vector>

class TwoPointers {
    public:
        void runTests();
        std::vector<std::vector<int>> twoSumUnsorted(std::vector<int>& nums, int target, unsigned int skipIdx);

    private:
        bool isPalindrome(std::string s);
        std::vector<int> twoSum(std::span<int> numbers, int target);
        std::vector<std::vector<int>> threeSum(std::span<int> nums);
        int maxArea(std::vector<int>& heights);
        int trap(std::vector<int>& height);
};
