/*
 * 题目：盛最多水的容器
 * 标签：双指针 / 贪心
 * 时间复杂度：O(n)，空间复杂度：O(1)
 * 思路：左右指针初始指向两端，计算当前面积。
 *       每次移动较矮的一侧（因为移动高侧不会增加容量）。
 *       更新最大面积。
 */
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(vector<int>& height) {
	int l = 0, r = height.size() - 1,ans=0;
    while (l < r) {
        int area = (r - l) * min(height[l], height[r]);
        ans = max(ans, area);
        if (height[l] < height[r]) ++l;
        else --r;
    }
    return ans;
}