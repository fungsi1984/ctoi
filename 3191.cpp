#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                ans++;
                if (i + 1 >= n || i + 2 >= n)
                    return -1;
                nums[i + 1] = 1 - nums[i + 1];
                nums[i + 2] = 1 - nums[i + 2];
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {0, 1, 0, 1, 0};
    int result1 = sol.minOperations(nums1);
    cout << "Example 1: Minimum operations: " << result1 << endl; // Output: 3

    // Example 2
    vector<int> nums2 = {1, 1, 1, 1};
    int result2 = sol.minOperations(nums2);
    cout << "Example 2: Minimum operations: " << result2 << endl; // Output: 0

    // Example 3
    vector<int> nums3 = {0, 0, 0};
    int result3 = sol.minOperations(nums3);
    cout << "Example 3: Minimum operations: " << result3 << endl; // Output: 3

    // Example 4
    vector<int> nums4 = {1, 0, 1, 0, 1, 0, 1};
    int result4 = sol.minOperations(nums4);
    cout << "Example 4: Minimum operations: " << result4 << endl; // Output: 3

    return 0;
}
