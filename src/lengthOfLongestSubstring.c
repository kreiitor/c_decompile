#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义最大值宏
#define MAX(a, b) ((b) > (a) ? (b) : (a))

// 无重复字符的最长子串长度
int lengthOfLongestSubstring(char* s) {
    int ans = 0, left = 0;
    int cnt[256] = {}; // 使用256确保覆盖所有可能的unsigned char值
    
    for (int right = 0; s[right]; right++) {
        unsigned char uc = (unsigned char)s[right];
        cnt[uc]++;
        while (cnt[uc] > 1) { // 窗口内有重复字母
            unsigned char left_uc = (unsigned char)s[left];
            cnt[left_uc]--; // 移除窗口左端点字母
            left++; // 缩小窗口
        }
        ans = MAX(ans, right - left + 1); // 更新窗口长度最大值
    }
    return ans;
}

// 测试函数
void testLengthOfLongestSubstring(char* s, char* testName) {
    printf("Test: %s\n", testName);
    printf("Input string: \"%s\" (length: %lu)\n", s, (unsigned long)strlen(s));  // 使用类型转换避免警告
    
    int result = lengthOfLongestSubstring(s);
    printf("Longest substring without repeating characters: %d\n\n", result);
}

int main() {
    printf("=== Test for Longest Substring Without Repeating Characters ===\n\n");
    
    // Test case 1: Basic example
    char s1[] = "abcabcbb";
    testLengthOfLongestSubstring(s1, "Basic example");
    
    // Test case 2: All same characters
    char s2[] = "bbbbb";
    testLengthOfLongestSubstring(s2, "All same characters");
    
    // Test case 3: With repeated characters
    char s3[] = "pwwkew";
    testLengthOfLongestSubstring(s3, "With repeated characters");
    
    // Test case 4: Empty string
    char s4[] = "";
    testLengthOfLongestSubstring(s4, "Empty string");
    
    // Test case 5: Single space
    char s5[] = " ";
    testLengthOfLongestSubstring(s5, "Single space");
    
    // Test case 6: Non-repeating string
    char s6[] = "abcdefghijklmnopqrstuvwxyz";
    testLengthOfLongestSubstring(s6, "Non-repeating alphabet");
    
    // Test case 7: Start with repeats
    char s7[] = "aab";
    testLengthOfLongestSubstring(s7, "Start with repeats");
    
    // Test case 8: Middle repeats
    char s8[] = "dvdf";
    testLengthOfLongestSubstring(s8, "Middle repeats");
    
    // Test case 9: With numbers and symbols
    char s9[] = "abc123!@#abc";
    testLengthOfLongestSubstring(s9, "With numbers and symbols");
    
    // Test case 10: Long string
    char s10[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    testLengthOfLongestSubstring(s10, "Long string (letters + numbers)");
    
    // Test case 11: Two different characters
    char s11[] = "au";
    testLengthOfLongestSubstring(s11, "Two different characters");
    
    printf("=== Test finished ===\n");
    
    return 0;
}