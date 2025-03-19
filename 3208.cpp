#include <iostream>
#include <vector>

auto optimizeIO = []() {
    std::ios::sync_with_stdio(false); // Disable sync with C standard I/O
    std::cin.tie(nullptr);            // Untie cin from cout
    std::cout.tie(nullptr);           // Untie cout from cin
    return nullptr;
}();

class Solution {
public:
    int numberOfAlternatingGroups(std::vector<int>& colors, int k) {
        const int n = colors.size();
        int ans = 0;
        int alternating = 1;

        for (int i = 0; i < n + k - 2; ++i) {
            alternating =
                colors[i % n] == colors[(i - 1 + n) % n] ? 1 : alternating + 1;
            if (alternating >= k)
                ++ans;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    std::vector<int> colors = {1, 2, 1, 2, 1, 3, 3, 2};
    int k = 3;

    int result = solution.numberOfAlternatingGroups(colors, k);
    std::cout << "Number of alternating groups: " << result << std::endl;

    return 0;
}
