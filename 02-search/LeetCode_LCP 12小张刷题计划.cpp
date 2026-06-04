/*
 * @problem: 最小化每日刷题负担 (Minimize Daily Problem Load)
 * @category: 二分查找
 * @time_complexity: O(n log S)，S 为总耗时
 * @space_complexity: O(1)
 * @description:
 * 每天选择连续一段题，耗时最长的一题可以"求助"（不计入当天负担）。
 * 求在 m 天内完成所有题目的最小每日负担。
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDailyLoad(vector<int>& time, int m) {
        int n = time.size();
        if (m >= n) return 0;  // 每天一题，求助最长的那题，负担 = 0

        auto check = [&](int mid) -> bool {
            int days = 1;
            int curSum = 0, curMax = 0;
            for (int t : time) {
                curSum += t;
                curMax = max(curMax, t);
                if (curSum - curMax > mid) {
					days++;//做题时间超过mid了，换一天,进行切割
                    curSum = t;
                    curMax = t;
                }
            }
            return days <= m;
            };

        int l = 0, r = accumulate(time.begin(), time.end(), 0);
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }
};