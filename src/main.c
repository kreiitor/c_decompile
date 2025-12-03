#include <stdio.h>
#include <stdlib.h>

// 测试函数：计算阶乘
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 测试函数：数组求和
int array_sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 测试函数：矩阵乘法（简单的优化目标）
void matrix_multiply(int A[2][2], int B[2][2], int C[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // 测试不同优化效果
    int x = factorial(5);
    printf("Factorial of 5: %d\n", x);
    
    int arr[] = {1, 2, 3, 4, 5};
    int sum = array_sum(arr, 5);
    printf("Array sum: %d\n", sum);
    
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2];
    matrix_multiply(A, B, C);
    
    printf("Matrix multiplication result:\n");
    printf("[%d %d]\n", C[0][0], C[0][1]);
    printf("[%d %d]\n", C[1][0], C[1][1]);
    
    return 0;
}