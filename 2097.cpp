#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>>
    validArrangement(const std::vector<std::vector<int>> &pairs) {
        std::unordered_map<int, std::vector<int>> adjacencyList;
        std::unordered_map<int, int> inOutDegree;

        // Initialize degree counts and build adjacency list
        for (const auto &pair : pairs) {
            int u = pair[0];
            int v = pair[1];
            adjacencyList[u].push_back(v);
            if (inOutDegree.find(u) == inOutDegree.end()) {
                inOutDegree[u] = 0;
            }
            if (inOutDegree.find(v) == inOutDegree.end()) {
                inOutDegree[v] = 0;
            }
        }

        // Update in/out degrees
        for (const auto &pair : pairs) {
            int u = pair[0];
            int v = pair[1];
            inOutDegree[u]++; // out-degree
            inOutDegree[v]--; // in-degree
        }

        // Find starting node (head)
        int startNode = pairs[0][0];
        for (const auto &entry : inOutDegree) {
            if (entry.second == 1) {
                startNode = entry.first;
                break;
            }
        }

        std::vector<int> path;
        std::stack<int> nodeStack;
        nodeStack.push(startNode);

        while (!nodeStack.empty()) {
            int currentNode = nodeStack.top();
            if (adjacencyList[currentNode].empty()) {
                path.push_back(nodeStack.top());
                nodeStack.pop();
            } else {
                int nextNode = adjacencyList[currentNode].back();
                adjacencyList[currentNode].pop_back();
                nodeStack.push(nextNode);
            }
        }

        std::vector<std::vector<int>> arrangement;
        arrangement.reserve(path.size() - 1);

        for (size_t i = path.size() - 1; i > 0; --i) {
            arrangement.push_back({path[i], path[i - 1]});
        }

        return arrangement;
    }
};

int main() {
    std::vector<std::vector<int>> pairs = {{1, 2}, {2, 3}, {3, 1}};
    Solution solution;
    std::vector<std::vector<int>> result = solution.validArrangement(pairs);

    for (const auto &pair : result) {
        std::cout << "[" << pair[0] << ", " << pair[1] << "]" << std::endl;
    }

    return 0;
}
