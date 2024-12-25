#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

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
public:
    int minimumOperations(TreeNode* root) {
        int ans = 0;
        queue<TreeNode*> q{{root}};

        // e.g. vals = [7, 6, 8, 5]
        // [2, 1, 3, 0]: Initialize the ids based on the order of vals.
        // [3, 1, 2, 0]: Swap 2 with 3, so 2 is in the right place (i ==
        // ids[i]). [0, 1, 2, 3]: Swap 3 with 0, so 3 is in the right place.
        while (!q.empty()) {
            vector<int> vals;
            vector<int> ids(q.size());
            for (int sz = q.size(); sz > 0; --sz) {
                TreeNode* node = q.front();
                q.pop();
                vals.push_back(node->val);
                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
            }
            iota(ids.begin(), ids.end(), 0);
            ranges::sort(ids,
                         [&vals](int i, int j) { return vals[i] < vals[j]; });
            for (int i = 0; i < ids.size(); ++i)
                for (; ids[i] != i; ++ans)
                    swap(ids[i], ids[ids[i]]);
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
