#include <functional> // For std::function
#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Define the recursive helper function using std::function
        std::function<ListNode*(ListNode*, ListNode*, int)> add =
            [&](ListNode* l1, ListNode* l2, int carry) -> ListNode* {
            // Base case: if both lists are empty and there's no carry, return
            // nullptr
            if (!l1 && !l2 && carry == 0) {
                return nullptr;
            }

            // Compute the sum of the current digits and the carry
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            auto node = new ListNode(
                sum % 10); // Create a new node with the digit value

            // Recursively compute the next node
            node->next =
                add(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr, sum / 10);
            return node;
        };

        // Start the recursion with an initial carry of 0
        return add(l1, l2, 0);
    }
};

// Helper function to print the linked list
void printList(ListNode* node) {
    while (node) {
        std::cout << node->val;
        if (node->next)
            std::cout << " -> ";
        node = node->next;
    }
    std::cout << std::endl;
}

// Example usage
int main() {
    // Create two linked lists: 2 -> 4 -> 3 and 5 -> 6 -> 4
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    // Add the two lists
    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);

    // Print the result: 7 -> 0 -> 8
    printList(result);

    // Clean up memory (optional, for completeness)
    while (result) {
        ListNode* temp = result;
        result = result->next;
        delete temp;
    }
    return 0;
}
