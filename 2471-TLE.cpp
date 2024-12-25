#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
};

class Solution {
private:
    // Helper function to count the minimum number of swaps to sort an array
    int countSwaps(const std::vector<int>& vals,
                   const std::vector<int>& sorted_vals) {
        int n = vals.size();
        std::vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (sorted_vals[j] == vals[i]) {
                    pos[i] = j;
                    break;
                }
            }
        }

        std::vector<bool> visited(n, false);
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int cycle_size = 0;
                int current = i;
                while (!visited[current]) {
                    visited[current] = true;
                    current = pos[current];
                    cycle_size += 1;
                }
                if (cycle_size > 1) {
                    ans += cycle_size - 1;
                }
            }
        }

        return ans;
    }

public:
    int minimumOperations(TreeNode* root) {
        int ans = 0;
        std::queue<TreeNode*> q;
        if (root)
            q.push(root);

        while (!q.empty()) {
            int level_size = q.size();
            std::vector<int> vals;

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                vals.push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            std::vector<int> sorted_vals = vals;
            std::sort(sorted_vals.begin(), sorted_vals.end());

            ans += countSwaps(vals, sorted_vals);
        }

        return ans;
    }
};

// Recursive function to convert vector to tree structure
TreeNode* buildTree(const std::vector<int>& nums) {
    if (nums.empty() || nums[0] == -1) {
        return nullptr;
    }

    auto build = [&](auto&& build, const std::vector<int>& nums,
                     int index) -> TreeNode* {
        if (index >= static_cast<int>(nums.size()) || nums[index] == -1) {
            return nullptr;
        }

        TreeNode* node = new TreeNode(nums[index]);
        node->left = build(build, nums, 2 * index + 1);
        node->right = build(build, nums, 2 * index + 2);

        return node;
    };

    return build(build, nums, 0);
}

int main() {
    std::vector<int> root_vec = {1,  4,  3,  7, 6,  8,  5, -1,
                                 -1, -1, -1, 9, -1, 10, -1};
    TreeNode* root = buildTree(root_vec);
    Solution sol;
    std::cout << "Minimum operations: " << sol.minimumOperations(root)
              << std::endl;
    return 0;
}
