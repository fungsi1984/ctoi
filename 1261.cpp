#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr) {}
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
};

// Function to convert vector with nulls to TreeNode
TreeNode* vectorToTree(vector<int*>& nums) { // Using int* to represent null
    if (nums.empty() || nums[0] == nullptr)
        return nullptr;

    TreeNode* root = new TreeNode(*nums[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nums.size()) {
        TreeNode* current = q.front();
        q.pop();

        // Add left child
        if (i < nums.size() && nums[i] != nullptr) {
            current->left = new TreeNode(*nums[i]);
            q.push(current->left);
        }
        i++;

        // Add right child
        if (i < nums.size() && nums[i] != nullptr) {
            current->right = new TreeNode(*nums[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
}

// Your FindElements class
class FindElements {
public:
    FindElements(TreeNode* root) { dfs(root, 0); }

    bool find(int target) { return vals.count(target); }

private:
    unordered_set<int> vals;

    void dfs(TreeNode* root, int val) {
        if (root == nullptr)
            return;

        root->val = val;
        vals.insert(val);
        dfs(root->left, val * 2 + 1);
        dfs(root->right, val * 2 + 2);
    }
};

// Function to clean up tree memory
void deleteTree(TreeNode* root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Example usage based on your new input

int main() {
    // Input: ["FindElements","find","find","find","find"]
    //        [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]

    // Step 1: Create tree from vector with nulls
    int val1 = -1, val2 = -1, val3 = -1, val4 = -1;
    vector<int*> treeValues = {&val1, nullptr, &val2, &val3, nullptr, &val4};
    // Represents: [-1,null,-1,-1,null,-1]

    TreeNode* root = vectorToTree(treeValues);

    // Step 2: Initialize FindElements
    FindElements* finder = new FindElements(root);

    // Step 3: Execute find operations
    cout << boolalpha;
    cout << "Find 2: " << finder->find(2) << endl; // true
    cout << "Find 3: " << finder->find(3) << endl; // false
    cout << "Find 4: " << finder->find(4) << endl; // false
    cout << "Find 5: " << finder->find(5) << endl; // true

    // Clean up
    delete finder;
    deleteTree(root);

    return 0;
}
