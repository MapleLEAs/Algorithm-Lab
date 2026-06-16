/*
 * 题目：在旋转排序数组中搜索
 * 标签：二分查找
 * 时间复杂度：O(log n)，空间复杂度：O(1)
 * 思路：每次取 mid，判断哪一半是有序的。
 *       如果左边有序，判断 target 是否在左边范围内，决定去哪边。
 *       如果右边有序，同理。
 */
#include <vector>
using namespace std;

int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;

        // 左半部分有序
        if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && target < nums[mid]) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        // 右半部分有序
        else {
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