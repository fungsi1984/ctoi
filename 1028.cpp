#include <cctype>
#include <iostream>
#include <string>

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
    TreeNode* recoverFromPreorder(std::string traversal) {
        int i = 0;
        return recoverFromPreorder(traversal, 0, i);
    }

private:
    TreeNode* recoverFromPreorder(const std::string& traversal, int depth,
                                  int& i) {
        int nDashes = 0;
        while (i + nDashes < traversal.length() &&
               traversal[i + nDashes] == '-') {
            ++nDashes;
        }
        if (nDashes != depth) {
            return nullptr;
        }

        i += depth;
        const int start = i;
        while (i < traversal.length() && std::isdigit(traversal[i])) {
            ++i;
        }

        // Create the current node with its value
        TreeNode* node =
            new TreeNode(std::stoi(traversal.substr(start, i - start)));

        // Recursively build the left and right subtrees
        node->left = recoverFromPreorder(traversal, depth + 1, i);
        node->right = recoverFromPreorder(traversal, depth + 1, i);

        return node;
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
