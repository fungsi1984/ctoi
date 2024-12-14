
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> visited;

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums.at(i);
            if (visited.find(diff) != visited.end()) 
                return {visited.at(diff), 1};
            visited[nums.at(i)] = i;
        }

        return {-1, -1};
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

