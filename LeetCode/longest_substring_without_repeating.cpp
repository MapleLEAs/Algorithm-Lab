/*
 * 题目：无重复字符的最长子串
 * 标签：滑动窗口 / 哈希表
 * 时间复杂度：O(n)，空间复杂度：O(字符集大小)
 * 思路：右指针扩展窗口，遇到重复字符时移动左指针缩小窗口，
 *       用哈希集合维护窗口内字符，每步更新最长长度。
 */
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstring(string s) {
	unordered_set<char> st;
	int l = 0, ans = 0;
	for (int i = 0;i < s.size();++i) {
		while (st.count(s[i])) {
			st.erase(s[left++]);
		}
		st.insert(s[i]);
		ans = max(ans, i - left + 1);
	}
	return ans;
}