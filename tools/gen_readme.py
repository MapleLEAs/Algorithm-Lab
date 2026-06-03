#!/usr/bin/env python3
"""
自动扫描 Algorithm-Lab 仓库中所有 .cpp 文件，
1. 将 LeetCode/ 下的题目按 @category 自动分类到对应目录
2. 提取题目标注信息，生成/更新 README.md 中的题目索引表格
"""

import os
import re
import shutil
from pathlib import Path

# ==================== 配置区 ====================

# 扫描的目录
SCAN_DIRS = [
    "01-sort",
    "02-search",
    "03-linked-list",
    "04-stack-queue",
    "05-tree",
    "06-graph",
    "07-dp",
    "LeetCode"
]

# @category 到目录名的映射（支持模糊匹配）
CATEGORY_TO_DIR = {
    "排序": "01-sort",
    "sort": "01-sort",
    "查找": "02-search",
    "二分": "02-search",
    "search": "02-search",
    "链表": "03-linked-list",
    "linked": "03-linked-list",
    "栈": "04-stack-queue",
    "队列": "04-stack-queue",
    "stack": "04-stack-queue",
    "queue": "04-stack-queue",
    "树": "05-tree",
    "tree": "05-tree",
    "图": "06-graph",
    "graph": "06-graph",
    "动态规划": "07-dp",
    "dp": "07-dp",
    "贪心": "07-dp",
    "回溯": "07-dp",
}

# .cpp 文件中提取信息的正则模式
PATTERNS = {
    "problem": r"@problem:\s*(.+)",
    "category": r"@category:\s*(.+)",
    "time_complexity": r"@time_complexity:\s*(.+)",
    "space_complexity": r"@space_complexity:\s*(.+)",
}

TABLE_START_MARKER = "<!-- PROBLEM_TABLE_START -->"
TABLE_END_MARKER = "<!-- PROBLEM_TABLE_END -->"


def extract_info_from_cpp(filepath: str) -> dict | None:
    """从单个 .cpp 文件顶部注释中提取题目信息"""
    info = {}
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            head = "".join([f.readline() for _ in range(50)])
    except Exception:
        return None

    for key, pattern in PATTERNS.items():
        match = re.search(pattern, head, re.IGNORECASE)
        info[key] = match.group(1).strip() if match else "—"

    return info if info.get("problem") != "—" else None


def match_category_to_dir(category: str) -> str | None:
    """根据 @category 内容匹配目标目录"""
    category_lower = category.lower()
    for keyword, dir_name in CATEGORY_TO_DIR.items():
        if keyword.lower() in category_lower:
            return dir_name
    return None


def auto_classify_leetcode(repo_root: str):
    """自动将 LeetCode/ 下的 .cpp 文件按 @category 移到对应目录"""
    leetcode_dir = Path(repo_root) / "LeetCode"
    if not leetcode_dir.exists():
        return

    moved_count = 0
    for cpp_file in leetcode_dir.glob("*.cpp"):
        info = extract_info_from_cpp(str(cpp_file))
        if not info:
            continue

        target_dir_name = match_category_to_dir(info["category"])
        if not target_dir_name:
            continue

        target_dir = Path(repo_root) / target_dir_name
        target_dir.mkdir(exist_ok=True)  # 确保目标目录存在

        target_path = target_dir / cpp_file.name

        # 避免覆盖：如果目标已存在且内容不同，加序号
        if target_path.exists():
            base = cpp_file.stem
            for i in range(1, 100):
                target_path = target_dir / f"{base}_{i}.cpp"
                if not target_path.exists():
                    break

        shutil.move(str(cpp_file), str(target_path))
        print(f"  📁 移动: LeetCode/{cpp_file.name} → {target_dir_name}/{target_path.name}")
        moved_count += 1

    if moved_count > 0:
        print(f"  ✅ 自动分类完成，共移动 {moved_count} 个文件\n")


def scan_all_cpp_files(repo_root: str) -> list[dict]:
    """扫描所有目录，收集所有 .cpp 文件的题目信息"""
    results = []
    repo_path = Path(repo_root)

    for dir_name in SCAN_DIRS:
        target_dir = repo_path / dir_name
        if not target_dir.exists():
            continue

        for cpp_file in sorted(target_dir.glob("*.cpp")):
            info = extract_info_from_cpp(str(cpp_file))
            if info:
                rel_path = cpp_file.relative_to(repo_path)
                info["file_path"] = str(rel_path).replace("\\", "/")
                results.append(info)
                print(f"  ✓ 提取: {info['file_path']}")

    return results


def generate_table_rows(problems: list[dict]) -> str:
    """根据题目信息生成 Markdown 表格行"""
    if not problems:
        return "| 暂无题目 | — | — | — | — | — |\n"

    rows = [
        "| # | 题目 | 分类 | 时间复杂度 | 空间复杂度 | 文件路径 |",
        "|---|------|------|-----------|-----------|---------|"
    ]

    for i, p in enumerate(problems, 1):
        row = f"| {i} | {p['problem']} | {p['category']} | {p['time_complexity']} | {p['space_complexity']} | `{p['file_path']}` |"
        rows.append(row)

    return "\n".join(rows) + "\n"


def update_readme(repo_root: str, table_content: str):
    """更新 README.md 中标记区域内的表格内容"""
    readme_path = Path(repo_root) / "README.md"

    if not readme_path.exists():
        full_content = f"# Algorithm-Lab\n\n{TABLE_START_MARKER}\n{table_content}\n{TABLE_END_MARKER}\n"
        readme_path.write_text(full_content, encoding="utf-8")
        return

    content = readme_path.read_text(encoding="utf-8")

    if TABLE_START_MARKER not in content or TABLE_END_MARKER not in content:
        content += f"\n\n{TABLE_START_MARKER}\n{table_content}\n{TABLE_END_MARKER}\n"
    else:
        pattern = re.compile(
            f"{re.escape(TABLE_START_MARKER)}.*?{re.escape(TABLE_END_MARKER)}",
            re.DOTALL
        )
        replacement = f"{TABLE_START_MARKER}\n{table_content}\n{TABLE_END_MARKER}"
        content = pattern.sub(replacement, content)

    readme_path.write_text(content, encoding="utf-8")
    print(f"\n✅ README.md 已更新，共 {table_content.count('|') // 7} 道题目")


def main():
    script_dir = Path(__file__).resolve().parent
    repo_root = script_dir.parent

    print(f"🔍 扫描仓库: {repo_root}\n")

    # 第 1 步：自动分类 LeetCode 下的文件
    print("📁 自动分类 LeetCode 题目...")
    auto_classify_leetcode(str(repo_root))

    # 第 2 步：扫描所有文件，生成表格
    print("🔍 扫描所有题目...")
    problems = scan_all_cpp_files(str(repo_root))

    if not problems:
        print("\n⚠️  未找到任何 .cpp 题目文件")
        return

    print(f"\n📊 共找到 {len(problems)} 道题目\n")
    table = generate_table_rows(problems)
    update_readme(str(repo_root), table)


if __name__ == "__main__":
    main()