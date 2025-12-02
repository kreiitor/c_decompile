#include <stdio.h>

// 计算斐波那契数
int fibonacci(int n) {
    if (n <= 1) 
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// 数组求和
int array_sum(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 矩阵乘法 2x2
void matrix_mult(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    // 测试 fibonacci
    int fib_result = fibonacci(10);
    printf("Fib(10) = %d\n", fib_result);
    
    // 测试 array_sum
    int test_array[] = {1, 2, 3, 4, 5};
    int sum_result = array_sum(test_array, 5);
    printf("Array sum = %d\n", sum_result);
    
    // 测试 matrix_mult
    int m1[2][2] = {{1, 2}, {3, 4}};
    int m2[2][2] = {{5, 6}, {7, 8}};
    int result[2][2];
    matrix_mult(m1, m2, result);
    printf("Matrix result: [%d, %d], [%d, %d]\n", 
           result[0][0], result[0][1], result[1][0], result[1][1]);
    
    return 0;
}