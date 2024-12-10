#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

struct HashTableEntry {
    int key;
    int value;
    int next; // Use an index instead of a pointer
};

struct HashTable {
    vector<int> buckets; // Use a vector for contiguous memory allocation
    vector<HashTableEntry> entries; // Use a vector for contiguous memory allocation
    int size;
    int entryCount;
};

// Function to create a hash table
inline HashTable* createHashTable(int size) {
    HashTable* ht = new HashTable;
    ht->buckets.resize(size, -1); // Initialize buckets with -1 (indicating empty)
    ht->entries.resize(size * 2); // Preallocate memory for entries
    ht->size = size;
    ht->entryCount = 0;
    return ht;
}

// Custom hash function
inline unsigned int customHash(int key, int size) {
    return std::abs(key) % size; // Use abs to handle negative keys
}

// Function to insert into the hash table
inline void insert(HashTable* ht, int key, int value) {
    unsigned int index = customHash(key, ht->size);
    int entryIndex = ht->buckets[index];
    while (entryIndex != -1) {
        if (ht->entries[entryIndex].key == key) {
            ht->entries[entryIndex].value = value; // Update the index for the key
            return;
        }
        entryIndex = ht->entries[entryIndex].next;
    }
    // Insert new entry at the beginning of the list
    int newEntryIndex = ht->entryCount++;
    ht->entries[newEntryIndex].key = key;
    ht->entries[newEntryIndex].value = value;
    ht->entries[newEntryIndex].next = ht->buckets[index];
    ht->buckets[index] = newEntryIndex;
}

// Function to search in the hash table
inline int search(HashTable* ht, int key) {
    unsigned int index = customHash(key, ht->size);
    int entryIndex = ht->buckets[index];
    while (entryIndex != -1) {
        if (ht->entries[entryIndex].key == key) {
            return ht->entries[entryIndex].value; // Return the index if found
        }
        entryIndex = ht->entries[entryIndex].next;
    }
    return -1; // Not found
}

// Function to free the hash table
inline void freeHashTable(HashTable* ht) {
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

