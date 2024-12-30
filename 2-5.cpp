#include <iostream>
#include <optional>
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
        ListNode* head = nullptr; // Head of the result linked list
        ListNode* curr = nullptr; // Current node in the result linked list
        int carry = 0;

        while (l1 || l2 || carry) {
            // Use std::optional to safely handle nullptr
            std::optional<int> val1 =
                l1 ? std::optional<int>(l1->val) : std::nullopt;
            std::optional<int> val2 =
                l2 ? std::optional<int>(l2->val) : std::nullopt;

            // Calculate the sum of the current digits and the carry
            int sum = carry;
            if (val1.has_value())
                sum += val1.value();
            if (val2.has_value())
                sum += val2.value();

            // Create a new node for the result
            ListNode* newNode = new ListNode(sum % 10);
            if (!head) {
                head = newNode; // Set head if it's the first node
            } else {
                curr->next = newNode; // Link the new node to the result list
            }
            curr = newNode; // Move the current pointer to the new node

            // Update the carry
            carry = sum / 10;

            // Move to the next nodes (if they exist)
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        return head;
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
    while (list) {
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
    while (l1) {
        ListNode* temp = l1;
        l1 = l1->next;
        delete temp;
    }
    while (l2) {
        ListNode* temp = l2;
        l2 = l2->next;
        delete temp;
    }
    while (result) {
        ListNode* temp = result;
        result = result->next;
        delete temp;
    }

    return 0;
}