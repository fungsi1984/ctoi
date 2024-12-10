#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

struct HashTableEntry {
    int key;
    int value;
    HashTableEntry* next;
};

struct HashTable {
    HashTableEntry** buckets;
    int size;
    int entryCount;
    HashTableEntry* entries;
};

// Function to create a hash table
inline HashTable* createHashTable(int size) {
    HashTable* ht = new HashTable;
    ht->buckets = new HashTableEntry*[size]();
    ht->size = size;
    ht->entryCount = 0;
    ht->entries = new HashTableEntry[size]; // Preallocate memory for entries
    return ht;
}

// Custom hash function
inline unsigned int customHash(int key, int size) {
    return std::abs(key) % size; // Use abs to handle negative keys
}

// Function to insert into the hash table
inline void insert(HashTable* ht, int key, int value) {
    unsigned int index = customHash(key, ht->size);
    HashTableEntry* entry = ht->buckets[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            entry->value = value; // Update the index for the key
            return;
        }
        entry = entry->next;
    }
    // Insert new entry at the beginning of the list
    HashTableEntry* newEntry = &ht->entries[ht->entryCount++];
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = ht->buckets[index];
    ht->buckets[index] = newEntry;
}

// Function to search in the hash table
inline int search(HashTable* ht, int key) {
    unsigned int index = customHash(key, ht->size);
    HashTableEntry* entry = ht->buckets[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value; // Return the index if found
        }
        entry = entry->next;
    }
    return -1; // Not found
}

// Function to free the hash table
inline void freeHashTable(HashTable* ht) {
    delete[] ht->buckets;
    delete[] ht->entries;
    delete ht;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        HashTable* ht = createHashTable(size * 2); // Double the size to reduce collisions

        for (int i = 0; i < size; i++) {
            int complement = target - nums[i];
            int foundIndex = search(ht, complement);
            if (foundIndex != -1) { // If complement is found in hash table
                vector<int> result = {foundIndex, i};
                freeHashTable(ht); // Free hash table before returning
                return result;
            }
            insert(ht, nums[i], i); // Insert current number with its index into hash table
        }

        freeHashTable(ht); // Free hash table if no solution is found
        return {}; // Return an empty vector if no solution exists
    }
};

int main() {
    Solution solution;
    vector<int> nums = {0, 4, 3, 0};
    int target = 0;

    vector<int> indices = solution.twoSum(nums, target);

    if (!indices.empty()) {
        cout << "Indices: " << indices[0] << ", " << indices[1] << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}

