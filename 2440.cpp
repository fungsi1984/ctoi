#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

class Solution {
private:
    int dfs(vector<int>& nums, vector<vector<int>>& adj, int u, int target, int parent) {
        int sum = nums[u];
        for (int v : adj[u]) {
            if (v != parent) {
                sum += dfs(nums, adj, v, target, u);
                if (sum > target) return numeric_limits<int>::max(); // Use numeric_limits
            }
        }
        return (sum == target) ? 0 : sum;
    }

public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        for (int components = n; components >= 1; --components) {
            if (totalSum % components == 0) {
                int target = totalSum / components;
                if (dfs(nums, adj, 0, target, -1) == 0) {
                    return components - 1;
                }
            }
        }
        return 0;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {6, 2, 2, 2, 6};
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {1, 3}, {3, 4}};
    cout << "Example 1: " << sol.componentValue(nums1, edges1) << endl; // Output: 2

    // Example 2
    vector<int> nums2 = {1, 2, 1, 2, 1};
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {0, 3}, {3, 4}};
    cout << "Example 2: " << sol.componentValue(nums2, edges2) << endl; // Output: 6

    // Example 3
    vector<int> nums3 = {1, 2, 3, 4, 5};
    vector<vector<int>> edges3 = {{0, 1}, {1, 2}, {0, 3}, {3, 4}};
    cout << "Example 3: " << sol.componentValue(nums3, edges3) << endl; // Output: 2

    // Example 4
    vector<int> nums4 = {6, 2, 2, 2, 6};
    vector<vector<int>> edges4 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}};
    cout << "Example 4: " << sol.componentValue(nums4, edges4) << endl; // Output: 1

    // Example 5
    vector<int> nums5 = {6, 2, 2, 2, 6};
    vector<vector<int>> edges5 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    cout << "Example 5: " << sol.componentValue(nums5, edges5) << endl; // Output: 2

    return 0;
}
