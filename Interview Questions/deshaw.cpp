//https://leetcode.com/discuss/post/7300021/deshaw-smts-hackerrank-coding-test-2025-3zm0z/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    // Helper function: Checks if it's possible to schedule all jobs 
    // such that every job executes on or before 'limit_day'.
    bool canFinish(int n, const vector<vector<int>>& executionDays, const vector<long long>& costs, int limit_day) {
        vector<pair<int, long long>> tasks; // Stores {deadline, cost}
        tasks.reserve(n);

        for (int i = 0; i < n; ++i) {
            // We need to find the largest available execution day for algorithm i that is <= limit_day.
            // Since executionDays[i] is sorted, we can use upper_bound to find the first day > limit_day,
            // then step back one position to get the largest day <= limit_day.
            
            const auto& days = executionDays[i];
            auto it = upper_bound(days.begin(), days.end(), limit_day);
            
            // If the iterator is at the beginning, it means all available days are > limit_day.
            // So, this algorithm cannot be executed within the limit.
            if (it == days.begin()) {
                return false;
            }
            
            // Pick the latest possible day (greedy choice)
            int deadline = *prev(it);
            tasks.push_back({deadline, costs[i]});
        }

        // Standard scheduling check: Sort tasks by deadline (Earliest Deadline First)
        sort(tasks.begin(), tasks.end());

        long long current_time = 0;
        for (const auto& task : tasks) {
            current_time += task.second; // Add training + execution time
            if (current_time > task.first) {
                return false; // Time required exceeds the deadline
            }
        }

        return true;
    }

    int minDaysToExecute(int n, int m, vector<vector<int>>& executionDays, vector<int>& trainingTime) {
        // Pre-processing
        vector<long long> costs(n);
        vector<int> all_possible_limits;
        
        for (int i = 0; i < n; ++i) {
            // Cost = Training days + 1 day for execution
            costs[i] = (long long)trainingTime[i] + 1;
                        
            // Collect all possible days to binary search over the answer space
            for (int day : executionDays[i]) {
                all_possible_limits.push_back(day);
            }
        }

        // Sort and remove duplicates from potential answers to speed up binary search
        sort(all_possible_limits.begin(), all_possible_limits.end());
        all_possible_limits.erase(unique(all_possible_limits.begin(), all_possible_limits.end()), all_possible_limits.end());

        // Binary Search on the Answer (over the index of sorted unique days)
        int low = 0;
        int high = all_possible_limits.size() - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int limit = all_possible_limits[mid];

            if (canFinish(n, executionDays, costs, limit)) {
                ans = limit;    // This limit works, try to find a smaller one
                high = mid - 1;
            } else {
                low = mid + 1;  // This limit is too tight, need more time
            }
        }

        return ans;
    }
};

// Driver code to test
int main() {
    Solution sol;
    
    // Example from image
    int n = 3, m = 2;
    vector<vector<int>> executionDays = {{3, 9}, {4, 7}, {1, 5}};
    vector<int> trainingTime = {1, 1, 4};

    cout << "Minimum days needed: " << sol.minDaysToExecute(n, m, executionDays, trainingTime) << endl;
    
    // Test case with high constraints (conceptual)
    // N=10^5, TrainingTime large
    
    return 0;
}