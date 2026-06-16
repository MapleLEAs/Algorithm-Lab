/*
 * 题目：跳跃游戏 II
 * 标签：贪心 / 动态规划
 * 时间复杂度：O(n)，空间复杂度：O(1)
 * 思路：维护当前步数能到达的最远位置 curEnd，
 *       以及下一步能到达的最远位置 curFarthest。
 *       走到 curEnd 时步数 +1，更新 curEnd = curFarthest。
 */
#include <vector>
#include <algorithm>
using namespace std;

int jump(vector<int>& nums) {
	int step = 0, cur = 0, curfast = 0;
	for (int i = 0;i < nums.size();++i) {
		curfast = max(curfast, i + nums[i]);
		if (i == cur) {
			step++;
			cur = curfast;
		}
	}
	return step;
}