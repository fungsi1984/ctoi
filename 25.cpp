#include <iostream>
#include <vector>
using namespace std;

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr)
            return nullptr;

        ListNode* tail = head;

        for (int i = 0; i < k; ++i) {
            if (tail == nullptr)
                return head;
            tail = tail->next;
        }

        ListNode* newHead = reverse(head, tail);
        head->next = reverseKGroup(tail, k);
        return newHead;
    }

    // Helper function to convert vector to linked list
    ListNode* vectorToList(const vector<int>& vec) {
        if (vec.empty())
            return nullptr;
        ListNode* head = new ListNode(vec[0]);
        ListNode* current = head;
        for (size_t i = 1; i < vec.size(); ++i) {
            current->next = new ListNode(vec[i]);
            current = current->next;
        }
        return head;
    }

private:
    ListNode* reverse(ListNode* head, ListNode* tail) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != tail) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

// Helper function to print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

int main() {
    Solution solution;
    vector<int> input = {1, 2, 3, 4, 5};
    int k = 2;

    // Convert vector to linked list
    ListNode* head = solution.vectorToList(input);

    // Reverse the linked list in groups of k
    ListNode* newHead = solution.reverseKGroup(head, k);

    // Print the reversed linked list
    printList(newHead);

    // Clean up memory
    while (newHead != nullptr) {
        ListNode* temp = newHead;
        newHead = newHead->next;
        delete temp;
    }

    return 0;
}
