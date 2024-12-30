#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr) {}
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        std::vector<ListNode*> nodes; // Temporary vector to store nodes
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            carry = sum / 10;
            nodes.push_back(
                new ListNode(sum % 10)); // Store the new node in the vector
        }

        // Build the final linked list from the vector
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        for (ListNode* node : nodes) {
            current->next = node;
            current = current->next;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead; // Clean up the dummy head
        return result;
    }
};

// Helper functions for testing
ListNode* toLinkedList(const std::vector<int>& vec) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* current = dummyHead;
    for (int val : vec) {
        current->next = new ListNode(val);
        current = current->next;
    }
    ListNode* result = dummyHead->next;
    delete dummyHead; // Clean up the dummy head
    return result;
}

std::vector<int> toVector(ListNode* list) {
    std::vector<int> vec;
    while (list != nullptr) {
        vec.push_back(list->val);
        list = list->next;
    }
    return vec;
}

int main() {
    ListNode* l1 = toLinkedList({2, 4, 3});
    ListNode* l2 = toLinkedList({5, 6, 4});
    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);
    std::vector<int> resultVec = toVector(result);

    for (int val : resultVec) {
        std::cout << val << " ";
    }
    std::cout << std::endl; // Output should be 7 0 8

    // Clean up memory
    while (l1 != nullptr) {
        ListNode* temp = l1;
        l1 = l1->next;
        delete temp;
    }
    while (l2 != nullptr) {
        ListNode* temp = l2;
        l2 = l2->next;
        delete temp;
    }
    while (result != nullptr) {
        ListNode* temp = result;
        result = result->next;
        delete temp;
    }

    return 0;
}