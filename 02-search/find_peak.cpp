/*
 * @problem: 寻找峰值 (Find Peak Element)
 * @category: 二分查找
 * @time_complexity: O(log n)
 * @space_complexity: O(1)
 * @description: 二分找峰值。如果 nums[mid] < nums[mid+1]，
 *               说明右侧一定有峰值，l = mid + 1；否则 r = mid。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] < nums[mid + 1])
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
};

int main() {
    Solution s;
    vector<int> nums = { 1,2,3,1 };
    cout << s.findPeakElement(nums) << endl;  // 2
    return 0;
}