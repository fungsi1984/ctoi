
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
        ListNode* dummyHead = new ListNode(0);
        ListNode* p = l1;
        ListNode* q = l2;
        ListNode* curr = dummyHead;
        int carry = 0;

        while (p != nullptr || q != nullptr) {
            int x = (p != nullptr) ? p->val : 0;
            int y = (q != nullptr) ? q->val : 0;
            int sum = carry + x + y;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            if (p != nullptr)
                p = p->next;
            if (q != nullptr)
                q = q->next;
        }

        if (carry > 0) {
            curr->next = new ListNode(carry);
        }

        return dummyHead->next;
    }
};

ListNode* vectorToListNode(const std::vector<int>& vec) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* curr = dummyHead;
    for (int val : vec) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    return dummyHead->next;
}

// Helper function to print the linked list (for testing purposes)
void printList(ListNode* node) {
    while (node != nullptr) {
        std::cout << node->val;
        if (node->next != nullptr) {
            std::cout << " -> ";
        }
        node = node->next;
    }
    std::cout << std::endl;
}

int main() {
    Solution solution;

    std::vector<int> l1 = {2, 4, 3};
    std::vector<int> l2 = {5, 6, 4};

    ListNode* list1 = vectorToListNode(l1);
    ListNode* list2 = vectorToListNode(l2);

    ListNode* result = solution.addTwoNumbers(list1, list2);

    printList(result); // Output: 7 -> 0 -> 8

    return 0;
}
