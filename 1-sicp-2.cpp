#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

class Solution {
private:
    // Helper function to find the complement in a map using const_iterator
    int findComplement(int complement, const std::unordered_map<int, int>& map) {
        std::unordered_map<int, int>::const_iterator it = map.find(complement);
        return it != map.end() ? it->second : -1; // -1 indicates not found
    }

    // Structure to hold the result of our two sum operation
    struct TwoSumResult {
        bool found = false;
        std::vector<int> indices;
        std::unordered_map<int, int> map;
    };

    // Function to find if there are two numbers in the vector that add up to target
    TwoSumResult findTwoSum(const std::vector<int>& nums, int target) {
        TwoSumResult result;
        result.map.reserve(nums.size());

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            int complementIndex = findComplement(complement, result.map);

            if (complementIndex != -1 && complementIndex != i) {
                result.found = true;
                result.indices.reserve(2);
                result.indices = {complementIndex, i};
                return result;  // Found a solution
            }

            // If not found, add this number to our map
            result.map[nums[i]] = i;
        }
        return result;
    }

public:
    // Main function to solve the two sum problem
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        TwoSumResult result = findTwoSum(nums, target);
        if (result.found) {
            return result.indices;
        } else {
            throw std::runtime_error("No two sum solution");
        }
    }
};

int main() {
    
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = Solution().twoSum(nums, target);

    if (!result.empty()) {
        std::cout << "Indices: " << result[0] << ", " << result[1] << std::endl;
    } else {
        std::cout << "No two sum solution" << std::endl;
    }

    return 0;
}