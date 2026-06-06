/*
 * @problem: 搜索旋转排序数组 (Search in Rotated Sorted Array)
 * @category: 二分查找
 * @time_complexity: O(log n)
 * @space_complexity: O(1)
 * @description: 旋转点将数组分成两段有序区间，
 *               判断 target 在左半段还是右半段，调整二分边界。
 */

#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;

            if (nums[l] <= nums[mid]) {  // 左半有序
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            else {  // 右半有序
                if (nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<int> nums = { 4,5,6,7,0,1,2 };
    cout << s.search(nums, 0) << endl;  // 4
    cout << s.search(nums, 3) << endl;  // -1
    return 0;
}