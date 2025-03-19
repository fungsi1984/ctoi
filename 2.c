#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a new ListNode
struct ListNode* createNode(int val) {
    struct ListNode* newNode =
        (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to convert a vector (array) into a linked list
struct ListNode* vectorToList(int* arr, int size) {
    if (size == 0)
        return NULL; // If the array is empty, return NULL

    struct ListNode* head = createNode(arr[0]); // Create the head node
    struct ListNode* curr = head;

    for (int i = 1; i < size; i++) {
        curr->next = createNode(arr[i]); // Create a new node and link it
        curr = curr->next;
    }

    return head;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free the linked list
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// The addTwoNumbers function (as provided)
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
    dummyHead->val = 0;
    dummyHead->next = NULL;
    struct ListNode* curr = dummyHead;
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int x = (l1 != NULL) ? l1->val : 0;
        int y = (l2 != NULL) ? l2->val : 0;
        int sum = carry + x + y;
        carry = sum / 10;
        curr->next = malloc(sizeof(struct ListNode));
        curr->next->val = sum % 10;
        curr->next->next = NULL;
        curr = curr->next;
        if (l1 != NULL)
            l1 = l1->next;
        if (l2 != NULL)
            l2 = l2->next;
    }
    struct ListNode* result = dummyHead->next;
    free(dummyHead); // Free the memory allocated for dummyHead
    return result;
}

int main() {
    // Example 1: 342 + 465 = 807
    // Represented as (2 -> 4 -> 3) + (5 -> 6 -> 4)
    int arr1[] = {2, 4, 3}; // Represents the number 342
    int arr2[] = {5, 6, 4}; // Represents the number 465

    // Convert arrays to linked lists
    struct ListNode* l1 = vectorToList(arr1, 3);
    struct ListNode* l2 = vectorToList(arr2, 3);

    // Add the two linked lists
    struct ListNode* result = addTwoNumbers(l1, l2);

    // Print the result
    printf("Result: ");
    printList(result); // Output should be 7 -> 0 -> 8 -> NULL

    // Free the memory allocated for the lists
    freeList(l1);
    freeList(l2);
    freeList(result);

    return 0;
}
