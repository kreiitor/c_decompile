#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10007  // 选择一个质数作为哈希表大小

// 哈希表节点结构
typedef struct HashNode {
    int key;        // 数值
    int value;      // 索引
    struct HashNode* next;
} HashNode;

// 哈希表结构
typedef struct {
    HashNode* table[HASH_SIZE];
} HashMap;

// 哈希函数
int hash(int key) {
    return abs(key) % HASH_SIZE;
}

// 初始化哈希表
void initHashMap(HashMap* map) {
    memset(map->table, 0, sizeof(map->table));
}

// 插入键值对
void put(HashMap* map, int key, int value) {
    int index = hash(key);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->table[index];
    map->table[index] = newNode;
}

// 查找键对应的值，找到返回索引，找不到返回-1
int get(HashMap* map, int key) {
    int index = hash(key);
    HashNode* node = map->table[index];
    while (node) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

// 释放哈希表内存
void freeHashMap(HashMap* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = map->table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

// 使用哈希表的两数之和解法
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap map;
    initHashMap(&map);
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = get(&map, complement);
        
        if (complementIndex != -1) {
            result[0] = complementIndex;
            result[1] = i;
            freeHashMap(&map);
            return result;
        }
        
        put(&map, nums[i], i);
    }
    
    freeHashMap(&map);
    *returnSize = 0;
    return NULL;
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
void testTwoSum(int* nums, int numsSize, int target, char* testName) {
    printf("测试: %s\n", testName);
    printf("数组: ");
    printArray(nums, numsSize);
    printf(", 目标值: %d\n", target);
    
    int returnSize;
    int* result = twoSum(nums, numsSize, target, &returnSize);
    
    if (returnSize == 2 && result != NULL) {
        printf("结果: 索引 %d 和 %d (值: %d + %d = %d)\n", 
               result[0], result[1], 
               nums[result[0]], nums[result[1]], 
               nums[result[0]] + nums[result[1]]);
    } else {
        printf("结果: 未找到符合条件的两个数\n");
    }
    
    free(result);
    printf("\n");
}

int main() {
    printf("=== 两数之和问题测试 ===\n\n");
    
    // 测试用例1: 基本示例
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    testTwoSum(nums1, 4, target1, "基本示例");
    
    // 测试用例2: 包含负数
    int nums2[] = {-3, 4, 3, 90};
    int target2 = 0;
    testTwoSum(nums2, 4, target2, "包含负数");
    
    // 测试用例3: 重复元素
    int nums3[] = {3, 2, 4};
    int target3 = 6;
    testTwoSum(nums3, 3, target3, "无重复索引");
    
    // 测试用例4: 相同元素
    int nums4[] = {3, 3};
    int target4 = 6;
    testTwoSum(nums4, 2, target4, "相同元素");
    
    // 测试用例5: 较大数组
    int nums5[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int target5 = 30;
    testTwoSum(nums5, 10, target5, "较大数组");
    
    // 测试用例6: 无解的情况
    int nums6[] = {1, 2, 3, 4};
    int target6 = 10;
    testTwoSum(nums6, 4, target6, "无解的情况");
    
    // 测试用例7: 零和负数
    int nums7[] = {0, -1, 2, -3, 1};
    int target7 = -2;
    testTwoSum(nums7, 5, target7, "零和负数");
    
    // 测试用例8: 只有一个元素
    int nums8[] = {1};
    int target8 = 1;
    testTwoSum(nums8, 1, target8, "只有一个元素");
    
    printf("=== 测试结束 ===\n");
    
    return 0;
}