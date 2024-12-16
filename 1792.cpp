#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
  double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    // (extra pass ratio, pass, total)
    priority_queue<tuple<double, int, int>> maxHeap;

    for (const vector<int>& c : classes) {
      const int pass = c[0];
      const int total = c[1];
      maxHeap.emplace(extraPassRatio(pass, total), pass, total);
    }

    for (int i = 0; i < extraStudents; ++i) {
      const auto [_, pass, total] = maxHeap.top();
      maxHeap.pop();
      maxHeap.emplace(extraPassRatio(pass + 1, total + 1), pass + 1, total + 1);
    }

    double ratioSum = 0;

    while (!maxHeap.empty()) {
      const auto [_, pass, total] = maxHeap.top();
      maxHeap.pop();
      ratioSum += pass / static_cast<double>(total);
    }

    return ratioSum / classes.size();
  }

private:
  // Returns the extra pass ratio if a brilliant student joins.
  double extraPassRatio(int pass, int total) {
    return (pass + 1) / static_cast<double>(total + 1) -
           pass / static_cast<double>(total);
  }
};

int main() {
  Solution solution;
  vector<vector<int>> classes = {{1, 2}, {3, 5}, {2, 2}};
  int extraStudents = 2;
  double result = solution.maxAverageRatio(classes, extraStudents);
  cout << "Maximum average pass ratio: " << result << endl;
  return 0;
}

