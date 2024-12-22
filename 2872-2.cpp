#include <iostream>
#include <vector>
#include <deque>

using namespace std;
using i64 = long long;

class Solution {
public:
    int max_k_divisible_components(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int ans = 0;
        dfs(graph, 0, -1, values, k, ans);
        return ans;
    }

private:
    i64 dfs(const vector<vector<int>>& graph, int u, int prev, const vector<int>& values, int k, int& ans) {
        i64 tree_sum = values[u];

        for (int v : graph[u]) {
            if (v != prev) {
                tree_sum += dfs(graph, v, u, values, k, ans);
            }
        }

        if (tree_sum % k == 0) {
            ans++;
        }
        return tree_sum;
    }
};

int main() {
    int n = 5;
    vector<vector<int>> edges = {{0, 2}, {1, 2}, {1, 3}, {2, 4}};
    vector<int> values = {1, 8, 1, 4, 4};
    int k = 6;

    // DFS Solution
    Solution sol;
    int result_dfs = sol.max_k_divisible_components(n, edges, values, k);
    cout << "DFS Result: " << result_dfs << endl; // Output: 2

    // BFS Solution (Corrected)
    vector<vector<int>> graph_bfs(n); // Separate graph for BFS (good practice)
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        graph_bfs[u].push_back(v);
        graph_bfs[v].push_back(u);
    }

    int ans_bfs = 0;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int component_sum = 0; // Reset for each component!
            deque<int> stack;
            stack.push_back(i);
            visited[i] = true;

            while (!stack.empty()) {
                int u = stack.front();
                stack.pop_front();
                component_sum += values[u];
                for (int v : graph_bfs[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        stack.push_back(v);
                    }
                }
            }

            if (component_sum % k == 0) {
                ans_bfs++;
            }
        }
    }

    cout << "BFS Result: " << ans_bfs << endl; // Output: 2

    return 0;
}
