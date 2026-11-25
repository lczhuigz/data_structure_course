Write-Host "========== Start Cleaning Build Directories ==========" -ForegroundColor Cyan

# 1. 清理每个 lab 目录下的 build 文件夹
Get-ChildItem -Directory -Filter "lab*" | Where-Object { $_.Name -match '^lab\d+$' } | ForEach-Object {
    $labName = $_.Name
    $buildPath = "$labName/build"
    
    if (Test-Path $buildPath) {
        Write-Host "Removing $buildPath ..." -ForegroundColor Yellow
        # -Recurse 删除文件夹内所有内容，-Force 强制删除（忽略只读等属性）
        Remove-Item -Path $buildPath -Recurse -Force -ErrorAction SilentlyContinue
        
        # 检查是否删除成功
        if (Test-Path $buildPath) {
            Write-Host "[ERROR] Failed to remove $buildPath . It might be in use by another program." -ForegroundColor Red
        } else {
            Write-Host "Successfully removed $buildPath" -ForegroundColor Green
        }
    } else {
        Write-Host "No build directory in $labName , skipping..." -ForegroundColor DarkGray
    }
}

# 2. 顺手清理根目录下可能存在的总 build 文件夹
if (Test-Path "build") {
    Write-Host "Removing root build directory ..." -ForegroundColor Yellow
    Remove-Item -Path "build" -Recurse -Force -ErrorAction SilentlyContinue
    
    if (Test-Path "build") {
        Write-Host "[ERROR] Failed to remove root build directory." -ForegroundColor Red
    } else {
        Write-Host "Successfully removed root build directory" -ForegroundColor Green
    }
}

Write-Host "----------------------------------------" -ForegroundColor Cyan
Write-Host "Clean up complete!" -ForegroundColor Green