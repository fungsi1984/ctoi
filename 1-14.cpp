#include <iostream>
#include <vector>
#include <unordered_map>
#include <print> // Include the print header for std::print

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.contains(complement)) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {}; // Return an empty vector if no solution is found
}

int main() {
    std::vector<int> nums = {2, 7, 11, 15, 100};
    int target = 115;
    std::vector<int> result = twoSum(nums, target);

    if (!result.empty()) {
        std::print("Indices: {}, {}\n", result[0], result[1]);
    } else {
        std::print("No two sum solution\n");
    }

    return 0;
}
