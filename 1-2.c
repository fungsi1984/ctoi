#include <stdio.h>
#include <stdlib.h>

typedef struct HashTableEntry {
    int key;
    int value;
    struct HashTableEntry* next;
} HashTableEntry;

typedef struct {
    HashTableEntry** buckets;
    int size;
} HashTable;

// Function to create a hash table
HashTable* createHashTable(int size) {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->buckets = calloc(size, sizeof(HashTableEntry*));
    ht->size = size;
    return ht;
}

// Hash function
unsigned int hash(int key, int size) {
    return abs(key) % size; // Use abs to handle negative keys
}

// Function to insert into the hash table
void insert(HashTable* ht, int key, int value) {
    unsigned int index = hash(key, ht->size);
    HashTableEntry* entry = ht->buckets[index];
    while (entry != NULL) {
        if (entry->key == key) {
            entry->value = value; // Update the index for the key
            return;
        }
        entry = entry->next;
    }
    // Insert new entry at the beginning of the list
    HashTableEntry* newEntry = malloc(sizeof(HashTableEntry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = ht->buckets[index];
    ht->buckets[index] = newEntry;
}

// Function to search in the hash table
int search(HashTable* ht, int key) {
    unsigned int index = hash(key, ht->size);
    HashTableEntry* entry = ht->buckets[index];
    while (entry != NULL) {
        if (entry->key == key) {
            return entry->value; // Return the index if found
        }
        entry = entry->next;
    }
    return -1; // Not found
}

// Function to free the hash table
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        HashTableEntry* entry = ht->buckets[i];
        while (entry != NULL) {
            HashTableEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

// Main function to find two indices that sum to target
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2; // Set return size to 2 since we expect two indices
    int* result = (int*)malloc(2 * sizeof(int));

    HashTable* ht = createHashTable(numsSize);

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int foundIndex = search(ht, complement);
        if (foundIndex != -1) { // If complement is found in hash table
            result[0] = foundIndex;
            result[1] = i;
            freeHashTable(ht); // Free hash table before returning
            return result;
        }
        insert(ht, nums[i], i); // Insert current number with its index into hash table
    }

    free(result); // Free allocated memory if no solution is found
    freeHashTable(ht); // Free hash table if no solution is found
    *returnSize = 0; // Set return size to 0 if no solution exists
    return NULL; // Return NULL if no solution exists
}

int main() {
    int nums[] = {0, 4, 3, 0};
    int target = 0;

    int returnSize;
    int* indices = twoSum(nums, sizeof(nums) / sizeof(nums[0]), target, &returnSize);

    if (indices != NULL && returnSize == 2) {
        printf("Indices: %d, %d\n", indices[0], indices[1]);
        free(indices); // Free allocated memory after use
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

