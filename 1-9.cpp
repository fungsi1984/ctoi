#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            if (map.find(complement) != map.end()) {
                std::vector<int> result = {i, map[complement]};
                std::sort(result.begin(), result.end());
                return result;
            }

            map[nums[i]] = i;
        }

        return {};
    }
};

int main() {
    Solution solution;
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = solution.twoSum(nums, target);

    for (int index : result) {
        std::cout << index << " ";
    }
    // Output: 0 1

    return 0;
}

