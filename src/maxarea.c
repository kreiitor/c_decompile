#include <stdio.h>
#include <stdlib.h>

// 定义最小值宏
#define MIN(a, b) ((b) < (a) ? (b) : (a))

// 定义最大值宏
#define MAX(a, b) ((b) > (a) ? (b) : (a))

// 盛最多水容器的双指针解法
int maxArea(int* height, int heightSize) {
    int ans = 0, left = 0, right = heightSize - 1;
    while (left < right) {
        int area = (right - left) * MIN(height[left], height[right]);
        ans = MAX(ans, area);
        // 移动较短的垂线，因为移动较长的垂线不会增加面积
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return ans;
}

// 打印数组
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

// 测试函数
void testMaxArea(int* height, int heightSize, char* testName) {
    printf("测试: %s\n", testName);
    printf("垂线高度数组: ");
    printArray(height, heightSize);
    printf(", 垂线数量: %d\n", heightSize);
    
    int result = maxArea(height, heightSize);
    printf("最大容量: %d\n\n", result);
}

int main() {
    printf("=== 盛最多水的容器问题测试 ===\n\n");
    
    // 测试用例1: LeetCode示例
    int height1[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    testMaxArea(height1, 9, "LeetCode示例");
    
    // 测试用例2: 两个垂线的情况
    int height2[] = {1, 1};
    testMaxArea(height2, 2, "两个垂线的情况");
    
    // 测试用例3: 递增高度
    int height3[] = {1, 2, 3, 4, 5};
    testMaxArea(height3, 5, "递增高度");
    
    // 测试用例4: 递减高度
    int height4[] = {5, 4, 3, 2, 1};
    testMaxArea(height4, 5, "递减高度");
    
    // 测试用例5: V形高度
    int height5[] = {1, 3, 5, 7, 5, 3, 1};
    testMaxArea(height5, 7, "V形高度");
    
    // 测试用例6: 只有一侧高
    int height6[] = {1, 100, 1, 1, 1, 1, 1};
    testMaxArea(height6, 7, "只有一侧高");
    
    // 测试用例7: 随机测试
    int height7[] = {3, 9, 3, 4, 7, 2, 12, 6};
    testMaxArea(height7, 8, "随机测试1");
    
    // 测试用例8: 长数组测试
    int height8[] = {1, 2, 1, 3, 2, 1, 4, 1, 2, 3, 2, 1};
    testMaxArea(height8, 12, "长数组测试");
    
    // 测试用例9: 所有垂线高度相同
    int height9[] = {5, 5, 5, 5, 5};
    testMaxArea(height9, 5, "所有垂线高度相同");
    
    // 测试用例10: 边界情况，只有两个垂线但高度不同
    int height10[] = {4, 6};
    testMaxArea(height10, 2, "两个不同高度的垂线");
    
    printf("=== 测试结束 ===\n");
    
    return 0;
}