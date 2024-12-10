#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> isArraySpecial(vector<int> &nums,
                                vector<vector<int>> &queries) {
        vector<bool> ans;
        int id = 0;
        // parityIds[i] := the id of the parity group that nums[i] belongs to
        vector<int> parityIds = {id};

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] % 2 == nums[i - 1] % 2)
                ++id;
            parityIds.push_back(id);
        }

        for (const vector<int> &query : queries) {
            const int from = query[0];
            const int to = query[1];
            ans.push_back(parityIds[from] == parityIds[to]);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {2, 4, 6, 3, 5, 7};
    vector<vector<int>> queries = {{0, 2}, {1, 3}, {2, 5}};

    vector<bool> result = solution.isArraySpecial(nums, queries);

    for (bool res : result) {
        cout << (res ? "True" : "False") << endl;
    }

    return 0;
}
