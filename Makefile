# 定义要分析的C源文件（根据你的截图使用optimization_example.c）
TARGET_SRC = src/optimization_example.c
TARGET_NAME = optimization_example

# 编译器和通用编译参数
CC = gcc
# -g 用于调试信息, -Wall 显示所有警告, -masm=intel 方便阅读
COMMON_CFLAGS = -g -Wall -masm=intel -Iinclude

# --- 优化级别设置 ---
# OLEVEL 变量默认设为 0（无优化），如果通过命令行参数传入，则使用传入的值。
OLEVEL ?= 0
CFLAGS = $(COMMON_CFLAGS) -O$(OLEVEL)

# 目录：输出文件将根据 OLEVEL 存放在独立的子目录中
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj/O$(OLEVEL)
ASM_DIR = $(BUILD_DIR)/asm/O$(OLEVEL)
BIN_DIR = $(BUILD_DIR)/debug/O$(OLEVEL)

# 文件路径
TARGET_EXE = $(BIN_DIR)/$(TARGET_NAME).exe
TARGET_OBJ = $(OBJ_DIR)/$(TARGET_NAME).o
TARGET_ASM = $(ASM_DIR)/$(TARGET_NAME).s

# 默认目标 (当你只运行 make 时，使用默认的 OLEVEL=0)
all: directories $(TARGET_EXE) $(TARGET_ASM)

# --- 核心构建逻辑 ---

# 创建构建目录 (Windows 兼容)
directories:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(ASM_DIR)" mkdir "$(ASM_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

# 链接生成可执行文件
$(TARGET_EXE): $(TARGET_OBJ)
	@echo "Linking $(OLEVEL) executable..."
	$(CC) $< -o $@

# 编译 C 代码到对象文件 (.o)
$(TARGET_OBJ): $(TARGET_SRC)
	@echo "Compiling C to .o with -O$(OLEVEL)..."
	$(CC) $(CFLAGS) -c $< -o $@

# 生成汇编文件 (.s) 用于分析
$(TARGET_ASM): $(TARGET_SRC)
	@echo "Generating Assembly to .s with -O$(OLEVEL)..."
	$(CC) $(CFLAGS) -S $< -o $@

# 清理所有生成的文件
clean:
	@echo "Cleaning build directory..."
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"