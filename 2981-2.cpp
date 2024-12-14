#include <iostream>
#include <string>
#include <map>
using namespace std;

// Custom Pair class
class Pair {
public:
    char first;
    int second;

    Pair(char f, int s) : first(f), second(s) {}

    bool operator<(const Pair& other) const {
        if (first == other.first) {
            return second < other.second;
        }
        return first < other.first;
    }

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
};

class Solution {
public:
    int maximumLength(string& s) {
        // Create a map of Pair to store the count of all substrings.
        map<Pair, int> count;
        int substringLength = 0;
        for (int start = 0; start < s.length(); start++) {
            char character = s[start];
            substringLength = 0;
            for (int end = start; end < s.length(); end++) {
                // If the string is empty, or the current character is equal to
                // the previously added character, then add it to the map.
                // Otherwise, break the iteration.
                if (character == s[end]) {
                    substringLength++;
                    count[Pair(character, substringLength)]++;
                } else {
                    break;
                }
            }
        }

        // Create a variable ans to store the longest length of substring with
        // frequency at least 3.
        int ans = 0;
        for (auto i : count) {
            int len = i.first.second;
            if (i.second >= 3 && len > ans) ans = len;
        }
        if (ans == 0) return -1;
        return ans;
    }
};

int main() {
    Solution solution;
    string s = "aaabb";
    int result = solution.maximumLength(s);
    cout << "The maximum length of a substring that appears at least three times is: " << result << endl;
    return 0;
}

