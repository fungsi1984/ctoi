#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        auto findPair = [](const vector<int>& nums, int target, auto lookupFn) -> vector<int> {
            unordered_map<int, int> numMap;
            for (size_t index = 0; index < nums.size(); ++index) {
                auto result = lookupFn(numMap, target - nums[index], index);
                if (result.has_value()) { // Correct check!
                    return result.value(); // Access the value
                }
                numMap[nums[index]] = index;
            }
            return {};
        };

        auto lookup = [](const unordered_map<int, int>& map, int complement, int currentIndex) -> optional<vector<int>> {
            if (map.count(complement)) {
                return vector<int>{map.at(complement), currentIndex};
            }
            return nullopt;
        };

        return findPair(nums, target, lookup);
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