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
    int getValueSafe(ListNode* node) {
        if (node == nullptr)
            return 0;
        return node->val;
    }

    ListNode* getNextNodeSafe(ListNode* node) {
        if (node == nullptr)
            return nullptr;
        return node->next;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head{};
        ListNode* curr{};
        int carry{0};
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int digitSum{getValueSafe(l1) + getValueSafe(l2) + carry};
            int digit {digitSum % 10};

            ListNode* tmp{new ListNode(digit)};
            if (head == nullptr) {
                head = tmp;
                curr = tmp;
            } else {
                curr->next = tmp;
                curr = tmp;
            }

            carry = digitSum / 10;

            l1 = getNextNodeSafe(l1);
            l2 = getNextNodeSafe(l2);
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