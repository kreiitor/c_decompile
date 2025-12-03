#include <stdio.h>
#include <stdlib.h>

// 滑动窗口最大值
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    // 如果数组为空或窗口大小为0，返回空数组
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // 使用数组模拟双端队列，存储索引
    int q[numsSize];
    int left = 0, right = 0;
    
    // 初始化第一个窗口
    for (int i = 0; i < k; ++i) {
        // 维护队列单调递减：移除比当前元素小的元素
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
    }
    
    // 存储结果
    *returnSize = 0;
    int* ans = malloc(sizeof(int) * (numsSize - k + 1));
    ans[(*returnSize)++] = nums[q[left]];
    
    // 滑动窗口
    for (int i = k; i < numsSize; ++i) {
        // 维护队列单调递减：移除比当前元素小的元素
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
        
        // 移除不在当前窗口中的元素
        while (q[left] <= i - k) {
            left++;
        }
        
        // 当前窗口的最大值是队列左端的元素
        ans[(*returnSize)++] = nums[q[left]];
    }
    
    return ans;
}

// 打印数组
void printArray(int* arr, int size, const char* name) {
    printf("%s: [", name);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// 测试函数
void testMaxSlidingWindow(int* nums, int numsSize, int k, const char* testName) {
    printf("Test: %s\n", testName);
    printf("Window size: %d\n", k);
    printArray(nums, numsSize, "Input array");
    
    int returnSize;
    int* result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    
    if (result != NULL) {
        printArray(result, returnSize, "Max sliding window");
        free(result);
    } else {
        printf("Result: NULL (empty array or window size is 0)\n");
    }
    printf("\n");
}

int main() {
    printf("=== Sliding Window Maximum Problem Test ===\n\n");
    
    // Test case 1: Basic example
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    testMaxSlidingWindow(nums1, 8, k1, "Basic example");
    
    // Test case 2: Single element
    int nums2[] = {1};
    int k2 = 1;
    testMaxSlidingWindow(nums2, 1, k2, "Single element");
    
    // Test case 3: All increasing
    int nums3[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int k3 = 3;
    testMaxSlidingWindow(nums3, 8, k3, "All increasing");
    
    // Test case 4: All decreasing
    int nums4[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int k4 = 4;
    testMaxSlidingWindow(nums4, 8, k4, "All decreasing");
    
    // Test case 5: Window size equals array size
    int nums5[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k5 = 8;
    testMaxSlidingWindow(nums5, 8, k5, "Window size equals array size");
    
    // Test case 6: Window size is 1
    int nums6[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k6 = 1;
    testMaxSlidingWindow(nums6, 8, k6, "Window size is 1");
    
    // Test case 7: Contains negative numbers
    int nums7[] = {-1, -3, -2, -4, -5, -3, -6, -7};
    int k7 = 3;
    testMaxSlidingWindow(nums7, 8, k7, "All negative numbers");
    
    // Test case 8: Mixed positive and negative
    int nums8[] = {9, -1, -3, 5, 3, -6, 7, 8};
    int k8 = 3;
    testMaxSlidingWindow(nums8, 8, k8, "Mixed positive and negative");
    
    // Test case 9: Duplicate values
    int nums9[] = {7, 2, 4, 7, 3, 7, 1, 7};
    int k9 = 3;
    testMaxSlidingWindow(nums9, 8, k9, "Duplicate values");
    
    // Test case 10: Empty array
    int nums10[] = {};
    int k10 = 3;
    testMaxSlidingWindow(nums10, 0, k10, "Empty array");
    
    // Test case 11: Window size 0
    int nums11[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k11 = 0;
    testMaxSlidingWindow(nums11, 8, k11, "Window size is 0");
    
    // Test case 12: Large window
    int nums12[] = {1, 2, 3, 4, 5};
    int k12 = 5;
    testMaxSlidingWindow(nums12, 5, k12, "Large window (size equals array)");
    
    // Test case 13: Single repeated value
    int nums13[] = {5, 5, 5, 5, 5};
    int k13 = 2;
    testMaxSlidingWindow(nums13, 5, k13, "All same values");
    
    printf("=== Test finished ===\n");
    
    return 0;
}