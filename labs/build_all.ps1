# 强制设置 UTF-8 输出（虽然提示全改英文了，但保留这行防止 CMake 报错时中文乱码）
$OutputEncoding = [System.Text.Encoding]::UTF8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

Write-Host "========== Start Building Labs ==========" -ForegroundColor Cyan

# 过滤目录：只找名字以 lab 开头，并且紧跟纯数字的文件夹（排除 lab_report）
Get-ChildItem -Directory -Filter "lab*" | Where-Object { $_.Name -match '^lab\d+$' } | ForEach-Object {
    $labName = $_.Name
    Write-Host "----------------------------------------" -ForegroundColor Cyan
    Write-Host "Configuring and Building $labName ..." -ForegroundColor Yellow
    
    # 使用相对路径
    cmake -B "$labName/build" -S "$labName" -G Ninja
    
    # 检查 cmake 是否执行成功
    if ($LASTEXITCODE -eq 0) {
        # 执行编译
        ninja -C "$labName/build"
        
        if ($LASTEXITCODE -ne 0) {
            Write-Host "[ERROR] Build failed in $labName !" -ForegroundColor Red
        }
    } else {
        Write-Host "[ERROR] CMake configure failed in $labName !" -ForegroundColor Red
    }
}

Write-Host "----------------------------------------" -ForegroundColor Cyan
Write-Host "All labs processed successfully!" -ForegroundColor Green