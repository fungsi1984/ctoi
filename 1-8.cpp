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

class HashTable {
public:
    HashTable(int size) {
        buckets.resize(size, -1); // Initialize buckets with -1 (indicating empty)
        entries.reserve(size * 2); // Reserve memory for entries
        this->size = size;
        entryCount = 0;
    }

    ~HashTable() {
        // No need to free memory as vectors handle it
    }

    void insert(int key, int value) {
        unsigned int index = customHash(key, size);
        int entryIndex = buckets[index];
        while (entryIndex != -1) {
            if (entries[entryIndex].key == key) {
                entries[entryIndex].value = value; // Update the index for the key
                return;
            }
            entryIndex = entries[entryIndex].next;
        }
        // Insert new entry at the beginning of the list
        int newEntryIndex = entryCount++;
        entries.emplace_back(HashTableEntry{key, value, buckets[index]});
        buckets[index] = newEntryIndex;
    }

    int search(int key) {
        unsigned int index = customHash(key, size);
        int entryIndex = buckets[index];
        while (entryIndex != -1) {
            if (entries[entryIndex].key == key) {
                return entries[entryIndex].value; // Return the index if found
            }
            entryIndex = entries[entryIndex].next;
        }
        return -1; // Not found
    }

    HashTableEntry& operator[](int index) {
        return entries[index];
    }

private:
    vector<int> buckets; // Use a vector for contiguous memory allocation
    vector<HashTableEntry> entries; // Use a vector for contiguous memory allocation
    int size;
    int entryCount;

    inline unsigned int customHash(int key, int size) {
        return std::abs(key) % size; // Use abs to handle negative keys
    }
};

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        HashTable ht(size * 2); // Double the size to reduce collisions

        for (int i = 0; i < size; i++) {
            int complement = target - nums[i];
            int foundIndex = ht.search(complement);
            if (foundIndex != -1) { // If complement is found in hash table
                vector<int> result = {foundIndex, i};
                return result;
            }
            ht.insert(nums[i], i); // Insert current number with its index into hash table
        }

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

