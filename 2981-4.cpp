#include <iostream>
#include <map>
#include <string>
using namespace std;
class Solution {
public:
    int maximumLength(string &s) {
        // Use std::pair instead of custom struct
        map<pair<char, int>, int> count;
        int substringLength = 0;
        for (int start = 0; start < s.length(); start++) {
            char character = s[start];
            substringLength = 0;
            for (int end = start; end < s.length(); end++) {
                if (character == s[end]) {
                    substringLength++;
                    count[{character,
                           substringLength}]++; // Use initializer list for pair
                } else {
                    break;
                }
            }
        }

        int ans = 0;
        for (const auto &i : count) { // Use const auto& for efficiency
            int len = i.first.second;
            if (i.second >= 3 && len > ans)
                ans = len;
        }
        if (ans == 0)
            return -1;
        return ans;
    }
};

int main() {
    Solution solution;
    string s = "aaabb";
    int result = solution.maximumLength(s);
    cout << "The maximum length of a substring that appears at least three "
            "times is: "
         << result << endl;
    return 0;
}
