# Algorithm-Lab：数据结构与算法系统仓库

> 全手写底层数据结构 + 经典算法C++17实现，覆盖LeetCode高频题型。
> Python脚本自动化生成目录索引与复杂度统计。

## 仓库定位

- 面试导向：所有代码都是**可直接跑通的.cpp文件**，每题标注时空复杂度
- 工程化：用Python脚本自动扫描全部源文件，生成README目录表格
- 持续更新：每次刷完一道题，就commit一次，持续积累

## 分类导航

### 1. 基础数据结构（手写实现）
- 单向/双向链表、循环链表
- 栈（数组/链表两种实现）
- 队列（普通队列、循环队列）
- 二叉搜索树、AVL树、红黑树
- 哈希表（拉链法/开放寻址法）

### 2. 经典算法分类

| 分类 | 内容 |
|------|------|
| **排序** | 快速排序、归并排序、堆排序、希尔排序、插入排序 |
| **查找** | 二分查找、KMP字符串匹配 |
| **图论** | Dijkstra、Floyd-Warshall、拓扑排序（BFS/DFS） |
| **动态规划** | 背包系列、最长子序列、编辑距离 |
| **回溯/贪心** | 全排列、N皇后、区间调度 |

### 3. 工程化配套
- 每题文件顶部注释：题目、思路、时间/空间复杂度
- `tools/gen_readme.py`：自动扫描所有文件，更新README中的题目索引表格
- 使用：每次新增题解后，运行脚本即可自动同步目录

## 项目结构

```
Algorithm-Lab/
├─ 01-sort/          排序算法
├─ 02-search/        查找算法
├─ 03-linked-list/   链表
├─ 04-stack-queue/   栈、队列
├─ 05-tree/          各类树结构
├─ 06-graph/         图论
├─ 07-dp/            动态规划
├─ LeetCode/         日常刷题专区
├─ tools/            Python自动化脚本
└─ README.md
```

## Python自动化脚本说明

脚本功能：
- 扫描指定目录下所有.cpp文件
- 提取文件名、题号、核心算法、复杂度
- 自动更新README中的题目索引表格

运行方式：
```bash
python3 tools/gen_readme.py
```

## 📋 题目索引

<!-- PROBLEM_TABLE_START -->
| # | 题目 | 分类 | 时间复杂度 | 空间复杂度 | 文件路径 |
|---|------|------|-----------|-----------|---------|
| 1 | 快速排序 (Quick Sort) | 排序 | O(n log n) | O(log n) | `01-sort/quick_sort.cpp` |
| 2 | 3399. 字符相同的最短子字符串 II (Shortest Substring With Same Character II) | 二分搜索 | O(n log n) | O(1) | `02-search/LeetCode_3399.cpp` |
| 3 | 最小稳定子数组长度 (Min Stable Subarray Length) | 二分查找 | O(n * log n * log V)，V 为数组最大值 | O(log V) | `02-search/LeetCode_3605数字的最小稳定因子.cpp` |
| 4 | 最小化每日刷题负担 (Minimize Daily Problem Load) | 二分查找 | O(n log S)，S 为总耗时 | O(1) | `02-search/LeetCode_LCP 12小张刷题计划.cpp` |
| 5 | 反转链表 (Reverse Linked List) | 链表 | O(n) | O(1) | `03-linked-list/linked-list.cpp` |
| 6 | 二叉树的前序遍历 (Binary Tree Preorder Traversal) | 树 | O(n) | O(h)，h 为树高 | `05-tree/treepreorder.cpp` |
| 7 | 最长公共子序列 (Longest Common Subsequence) | 动态规划 | O(m * n) | O(m * n) | `07-dp/dplcs.cpp` |

<!-- PROBLEM_TABLE_END -->