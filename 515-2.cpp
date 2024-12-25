#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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
    vector<int> largestValues(TreeNode* root) {
        if (root == nullptr)
            return {};

        vector<int> ans;
        queue<TreeNode*> q{{root}};

        while (!q.empty()) {
            int mx = INT_MIN;
            for (int sz = q.size(); sz > 0; --sz) {
                TreeNode* node = q.front();
                q.pop();
                mx = max(mx, node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            ans.push_back(mx);
        }

        return ans;
    }
};

TreeNode* buildTreeFromVector(const vector<int>& values, int index = 0) {
    if (index >= values.size() || values[index] == INT_MIN) {
        return nullptr;
    }
    TreeNode* node = new TreeNode(values[index]);
    node->left = buildTreeFromVector(values, 2 * index + 1);
    node->right = buildTreeFromVector(values, 2 * index + 2);
    return node;
}

int main() {
    // Input vector
    vector<int> input = {1, 3, 2, 5, 3, INT_MIN, 9};

    // Create an instance of the Solution class
    Solution solution;

    // Build the tree from the vector
    TreeNode* root = buildTreeFromVector(input);

    // Get the largest values on each level
    vector<int> result = solution.largestValues(root);

    // Print the result
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
