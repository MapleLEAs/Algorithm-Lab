/*
 * @problem: 快速排序 (Quick Sort)
 * @category: 排序
 * @time_complexity: O(n log n)
 * @space_complexity: O(log n)
 * @description: 分治法选取基准值，左右分区递归排序
 */

#include <iostream>
#include <vector>
using namespace std;


int partition(vector<int>& arr, int left, int right) {
	int mid = left + (right - left) / 2;
	if (arr[mid] < arr[left])   swap(arr[mid], arr[left]);   // 保证 left <= mid
	if (arr[right] < arr[left])  swap(arr[right], arr[left]);  // 保证 left <= right
	if (arr[mid] < arr[right])  swap(arr[mid], arr[right]);  // 保证 right >= mid
	
	int i = left - 1;
	int pivot = arr[right];
	for (int j = left; j < right; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[right]);
	return i + 1;
}

void quickSort(vector<int>& arr, int left, int right) {
	if (left < right) {
		int pos = partition(arr, left, right);
		quickSort(arr, left, pos - 1);
		quickSort(arr, pos + 1, right);
	}
}

int main() {
	vector<int> arr = { 3, 6, 8, 10, 1, 2, 1 };
	quickSort(arr, 0, arr.size() - 1);
	for (int num : arr) {
		cout<< num << " ";
	}
	return 0;
}