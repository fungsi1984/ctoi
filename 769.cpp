#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int ans = 0;
        int mx = INT_MIN;

        for (int i = 0; i < arr.size(); ++i) {
            mx = max(mx, arr[i]);
            if (mx == i)
                ++ans;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> arr = {4, 3, 2, 1, 0};
    int result = solution.maxChunksToSorted(arr);
    cout << "Maximum number of chunks: " << result << endl;
    return 0;
}

