#include <functional> // Include for std::function
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // Create a hash map to store the value and its index
        std::unordered_map<int, int> num_map;

        // Define a std::function to represent the lambda
        std::function<std::vector<int>()> findIndices =
            [&]() -> std::vector<int> {
            for (int i = 0; i < nums.size(); i++) {
                int complement = target - nums[i];
                if (num_map.find(complement) != num_map.end()) {
                    return {num_map[complement], i};
                }
                num_map[nums[i]] = i;
            }
            return {}; // Return an empty vector if no solution is found
        };

        // Call the std::function and return the result
        return findIndices();
    }
};

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    Solution sol;
    vector<int> result = sol.twoSum(nums, target);
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return 0;
}