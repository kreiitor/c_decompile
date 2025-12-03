# build_all.ps1
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
# 配置源目录
$srcDir = "src"
# 获取所有 .c 文件
$sourceFiles = Get-ChildItem -Path $srcDir -Filter "*.c"

# 定义优化等级
$levels = @("O0", "O1", "O2", "O3")

if ($sourceFiles.Count -eq 0) {
    Write-Host "Error: src 目录下没有找到 .c 文件" -ForegroundColor Red
    exit 1
}

Write-Host "=== 开始构建分析文件 ===" -ForegroundColor Cyan

foreach ($level in $levels) {
    Write-Host "`n正在处理优化等级: -$level" -ForegroundColor Yellow
    
    # 1. 确保目录结构存在
    $asmDir = "build/asm/$level"
    $objDir = "build/obj/$level"
    $exeDir = "build/debug/$level"

    New-Item -ItemType Directory -Force -Path $asmDir | Out-Null
    New-Item -ItemType Directory -Force -Path $objDir | Out-Null
    New-Item -ItemType Directory -Force -Path $exeDir | Out-Null

    foreach ($file in $sourceFiles) {
        $baseName = $file.BaseName
        $srcPath = "$srcDir/$($file.Name)"
        
        Write-Host "  -> Compiling $baseName..." -NoNewline

        try {
            # --- 1. 生成汇编 (.s) ---
            # -S: 生成汇编
            # -fverbose-asm: 在汇编中把C变量名作为注释加上，极助于分析
            # -masm=intel: 使用 Intel 格式 (比 AT&T 格式更易读)
            gcc -S -fverbose-asm -masm=intel "-$level" $srcPath -o "$asmDir/$baseName.s"

            # --- 2. 生成目标文件 (.o) ---
            # -c: 仅编译不链接
            # -g: 带调试信息 (便于反汇编分析)
            gcc -c -g "-$level" $srcPath -o "$objDir/$baseName.o"

            # --- 3. 生成可执行文件 (.exe) ---
            # -g: 带调试信息
            gcc -g "-$level" $srcPath -o "$exeDir/$baseName.exe"
            
            Write-Host " [完成]" -ForegroundColor Green
        }
        catch {
            Write-Host " [失败]" -ForegroundColor Red
            Write-Host $_
        }
    }
}

Write-Host "`n=== 所有构建任务已完成 ===" -ForegroundColor Cyan