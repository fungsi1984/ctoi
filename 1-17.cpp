#include <concepts>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

// Define the Addable concept
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

class Solution {
public:
    auto twoSum(std::vector<int>& nums, int target) -> std::vector<int> {
        std::unordered_map<int, int> num_map;

        // Custom enumerate view using zip and iota
        auto enumerate = [](auto&& range) {
            return std::views::zip(
                std::views::iota(0), // Generate indices starting from 0
                range                // The original range
            );
        };

        // Lambda to find indices, constrained by the Addable concept
        auto find_indices = [&]<Addable T>(const std::vector<T>& nums,
                                           T target) -> std::vector<int> {
            for (auto&& [i, num] : enumerate(nums)) {
                T complement = target - num;
                if (num_map.contains(complement)) {
                    return {num_map[complement], static_cast<int>(i)};
                }
                num_map[num] = static_cast<int>(i);
            }
            return {}; // Just in case, though the problem guarantees a solution
        };

        // Call the constrained lambda
        return find_indices(nums, target);
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    auto result = sol.twoSum(nums, target);
    std::cout << "Indices: [" << result[0] << ", " << result[1] << "]\n";
    return 0;
}
