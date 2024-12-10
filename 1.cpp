#include <iostream>
#include <vector>
#include <unordered_map>

struct NumEntry {
    int value;
    size_t index;
};

class Solution {
public:
    std::vector<int> two_sum(const std::vector<int>& nums, int target) {
        // Create an unordered_map to store each number and its index.
        std::unordered_map<int, size_t> num_map;

        // Create a vector of NumEntry structs
        std::vector<NumEntry> entries;
        for (size_t i = 0; i < nums.size(); ++i) {
            entries.push_back({nums[i], i});
        }

        // Iterate through the entries.
        for (const auto& entry : entries) {
            int complement = target - entry.value;

            // Check if the complement exists in the map.
            auto it = num_map.find(complement);
            if (it != num_map.end()) {
                // If found, return the indices of the two numbers.
                return {static_cast<int>(it->second), static_cast<int>(entry.index)};
            }

            // Store the current number and its index in the map.
            num_map[entry.value] = entry.index;
        }

        // Return an empty vector if no solution is found (should not happen according to problem statement).
        return {};
    }
};

int main() {
    Solution solution;
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    std::vector<int> result = solution.two_sum(nums, target);

    // Output the result
    std::cout << "[" << result[0] << ", " << result[1] << "]" << std::endl; // Output: [0, 1]
    
    return 0;
}

