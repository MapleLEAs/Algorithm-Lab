/*
 * @problem: 在排序数组中找元素的第一个和最后一个位置 (Find First and Last Position)
 * @category: 二分查找
 * @time_complexity: O(log n)
 * @space_complexity: O(1)
 * @description: 两次二分，一次找左边界，一次找右边界。
 *               找左边界：找到 target 后继续向左缩；右边界同理。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = leftBound(nums, target);
        if (l == -1) return { -1, -1 };
        return { l, rightBound(nums, target) };
    }
private:
    int leftBound(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1,ans=-1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= target) {
                r = mid -1;
                if (nums[mid] == target) ans = mid;
            }else(nums[mid] > target) {
                l = mid +1;
            }
        }
		return ans;
    }

    int rightBound(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target) {
                l = mid + 1;
				if (nums[mid] == target) ans = mid;
            }
            else {
                r = mid - 1;
            }
        }
		return ans;
    }

};
int main() {
    Solution s;
    vector<int> nums = { 5,7,7,8,8,10 };
    auto res = s.searchRange(nums, 8);
    cout << res[0] << " " << res[1] << endl;  // 3 4
    return 0;
}