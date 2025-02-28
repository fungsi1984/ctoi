#include <cctype>
#include <iostream>
#include <string>
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
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right) {}
};

class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        vector<TreeNode*> stack;
        int i = 0;
        while (i < traversal.length()) {
            int level = 0, val = 0;
            while (traversal[i] == '-') {
                i++;
                level++;
            }
            while (i < traversal.length() && traversal[i] != '-') {
                val = val * 10 + traversal[i] - '0';
                i++;
            }

            TreeNode* node = new TreeNode(val);
            while (stack.size() > level)
                stack.pop_back();
            if (!stack.empty()) {
                if (!stack.back()->left)
                    stack.back()->left = node;
                else
                    stack.back()->right = node;
            }
            stack.push_back(node);
        }
        return stack[0];
    }
};
// Helper function to print the tree in preorder traversal
void printPreorder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->val << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

int main() {
    Solution solution;
    std::string traversal = "1-2--3--4-5--6--7";
    TreeNode* root = solution.recoverFromPreorder(traversal);

    // Print the tree in preorder traversal
    printPreorder(root);

    // Clean up the allocated memory
    // Note: In a real-world scenario, you should implement a function to delete
    // the tree nodes to avoid memory leaks.

    return 0;
}
