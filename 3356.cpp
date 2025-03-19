#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> line(nums.size() + 1);
        int decrement = 0;
        int k = 0;

        for (int i = 0; i < nums.size(); ++i) {
            while (decrement + line[i] < nums[i]) {
                if (k == queries.size())
                    return -1;

                const int l = queries[k][0];
                const int r = queries[k][1];
                const int val = queries[k][2];
                ++k;

                // Only apply the query if it affects the current or future
                // elements
                if (r >= i) {
                    line[max(l, i)] += val;
                    line[r + 1] -= val;
                }
            }
            decrement += line[i];
        }

        return k;
    }
};

int main() {
    Solution solution;

    // Example input
    vector<int> nums = {3, 1, 4, 2};
    vector<vector<int>> queries = {
        {0, 2, 2}, // Decrement nums[0..2] by 2
        {1, 3, 1}, // Decrement nums[1..3] by 1
        {2, 3, 1}  // Decrement nums[2..3] by 1
    };

    int result = solution.minZeroArray(nums, queries);

    if (result == -1) {
        cout << "It is not possible to make the array zero using the given "
                "queries."
             << endl;
    } else {
        cout << "Minimum number of queries needed: " << result << endl;
    }

    return 0;
}
