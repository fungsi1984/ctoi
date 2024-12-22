#include <algorithm>
#include <iostream>
#include <vector>

// Definition of the IndexedQuery struct
struct IndexedQuery {
    int queryIndex;
    int a; // Alice's index
    int b; // Bob's index
};

class Solution {
public:
    // Similar to 2736. Maximum Sum Queries
    std::vector<int>
    leftmostBuildingQueries(std::vector<int> &heights,
                            std::vector<std::vector<int>> &queries) {
        std::vector<int> ans(queries.size(), -1);
        std::vector<int> stack;

        int heightsIndex = heights.size() - 1;
        for (const auto &query : getIndexedQueries(queries)) {
            if (query.a == query.b || heights[query.a] < heights[query.b]) {
                ans[query.queryIndex] = query.b;
            } else {
                while (heightsIndex > query.b) {
                    while (!stack.empty() &&
                           heights[stack.back()] <= heights[heightsIndex])
                        stack.pop_back();
                    stack.push_back(heightsIndex--);
                }
                auto it = std::upper_bound(
                    stack.rbegin(), stack.rend(), query.a,
                    [&](int a, int b) { return heights[a] < heights[b]; });
                if (it != stack.rend())
                    ans[query.queryIndex] = *it;
            }
        }

        return ans;
    }

private:
    std::vector<IndexedQuery>
    getIndexedQueries(const std::vector<std::vector<int>> &queries) {
        std::vector<IndexedQuery> indexedQueries;
        for (int i = 0; i < queries.size(); ++i) {
            // Ensure a <= b
            const int a = std::min(queries[i][0], queries[i][1]);
            const int b = std::max(queries[i][0], queries[i][1]);
            indexedQueries.push_back({i, a, b});
        }
        // Sort in descending order by 'b'
        std::sort(indexedQueries.begin(), indexedQueries.end(),
                  [](const IndexedQuery &a, const IndexedQuery &b) {
                      return a.b > b.b;
                  });
        return indexedQueries;
    }
};

int main() {
    Solution solution;
    std::vector<int> heights = {6, 4, 8, 5, 2, 7};
    std::vector<std::vector<int>> queries = {{0, 1}, {1, 2}, {2, 3}, {4, 5}};

    std::vector<int> result =
        solution.leftmostBuildingQueries(heights, queries);

    // Print result
    for (int i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
