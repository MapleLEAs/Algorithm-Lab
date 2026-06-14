/*
 * @problem: 搜索二维矩阵 (Search a 2D Matrix)
 * @category: 二分查找
 * @time_complexity: O(log(m*n))
 * @space_complexity: O(1)
 * @description: 每行递增，且下一行首元素 > 上一行尾元素。
 *               将二维坐标映射为一维下标，二分查找。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>> M, int target) {
        if (M.empty() || M[0].empty())return 0;
        int m = M.size(), n = M[0].size();
        int l = 0, r = m * n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int val = M[mid / n][mid % n];
            if (val == target)return true;
            else if (val < target) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> m = { {1,3,5,7},{10,11,16,20},{23,30,34,60} };
    Solution s;
    cout << s.searchMatrix(m, 3) << endl;   // 1
    cout << s.searchMatrix(m, 13) << endl;  // 0
    return 0;
}