#include <iostream>
using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast = head, *slow = head;
        for (int i = 0; i < n; i++)
            fast = fast->next;
        if (!fast)
            return head->next;
        while (fast->next)
            fast = fast->next, slow = slow->next;
        slow->next = slow->next->next;
        return head;
    }
};

// Helper function to create a linked list
ListNode* createList(int arr[], int size) {
    if (size == 0)
        return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < size; i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print the linked list
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next)
            cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    // Example usage
    int arr[] = {1, 2, 3, 4, 5};
    int n = 2; // Remove 2nd node from the end (4)

    // Create the linked list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = createList(arr, 5);

    cout << "Original list: ";
    printList(head);

    // Remove nth node from end
    Solution solution;
    head = solution.removeNthFromEnd(head, n);

    cout << "After removing " << n << "th node from end: ";
    printList(head);

    // Clean up memory (not shown for brevity in real applications)
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
