#include <print>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }

    return {}; // This line should never be reached if the problem guarantees a solution
}

int main() {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    std::vector<int> result = twoSum(nums, target);

    if (!result.empty()) {
        auto [index1, index2] = result; // Structured binding
        std::print("Indices of the two numbers that add up to {} are: {} and {}\n", target, index1, index2);
    } else {
        std::print("No solution found.\n");
    }

    return 0;
}
