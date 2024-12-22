#include <iostream>
#include <vector>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (root) {
            dfs(root->left, root->right, true);
        }
        return root;
    }

private:
    void dfs(TreeNode* left, TreeNode* right, bool isOddLevel) {
        if (!left) {
            return;
        }

        if (isOddLevel) {
            std::swap(left->val, right->val);
        }

        if (left->left && right->right) {
            dfs(left->left, right->right, !isOddLevel);
        }
        if (left->right && right->left) {
            dfs(left->right, right->left, !isOddLevel);
        }
    }

public:
    static TreeNode* vecToTree(const std::vector<int>& values) {
        if (values.empty()) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(values[0]);
        std::queue<TreeNode*> queue;
        queue.push(root);

        int i = 1;
        while (i < values.size()) {
            TreeNode* parent = queue.front();
            queue.pop();

            if (i < values.size()) {
                parent->left = new TreeNode(values[i]);
                queue.push(parent->left);
                i++;
            }

            if (i < values.size()) {
                parent->right = new TreeNode(values[i]);
                queue.push(parent->right);
                i++;
            }
        }

        return root;
    }

    static std::vector<int> treeToVec(TreeNode* root) {
        std::vector<int> result;
        std::queue<TreeNode*> queue;

        if (root) {
            queue.push(root);
        }

        while (!queue.empty()) {
            TreeNode* node = queue.front();
            queue.pop();
            result.push_back(node->val);
            if (node->left) {
                queue.push(node->left);
            }
            if (node->right) {
                queue.push(node->right);
            }
        }

        return result;
    }
};

int main() {
    // Example usage
    std::vector<int> values = {2, 3, 5, 8, 13, 21, 34};
    TreeNode* root = Solution::vecToTree(values);

    Solution solution;
    TreeNode* reversedRoot = solution.reverseOddLevels(root);
    std::vector<int> output = Solution::treeToVec(reversedRoot);

    // Print the input and output in the desired format
    std::cout << "Input: root = [";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i < values.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    std::cout << "Output: [";
    for (size_t i = 0; i < output.size(); ++i) {
        std::cout << output[i];
        if (i < output.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}

