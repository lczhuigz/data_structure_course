#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 20000


/* 插入排序 */
void insert_sort(int *array, int n){

    int i, j, key_num;
    for (i = 1; i < n; i++){
        key_num = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key_num){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key_num;
    }
}

/* 归并排序的合并函数 */
void merge(int *array, int left, int mid, int right, int *temp){

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right){
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= mid)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    for (i = left; i <= right; i++)
        array[i] = temp[i];
}

/* 归并排序 */
void merge_sort(int *array, int left, int right, int *temp){

    int mid;
    if (left < right){
        mid = (left + right) / 2;
        merge_sort(array, left, mid, temp);
        merge_sort(array, mid + 1, right, temp);
        merge(array, left, mid, right, temp);
    }
}

/* 二分查找，找到返回下标，找不到返回 -1 */
int binary_search(int *array, int n, int key_num){

    int low = 0, high = n - 1, mid;

    while (low <= high){
        mid = (low + high) / 2;
        if (array[mid] == key_num)
            return mid;
        else if (array[mid] < key_num)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* 检查数组是否有序 */
int check_sorted(int *array, int n){

    int i;
    for (i = 1; i < n; i++){
        if (array[i - 1] > array[i])
            return 0;
    }

    return 1;
}

int main(int argc, char ** argv){

    int *array, *b, *temp;
    int i, key_num, pos;
    clock_t start, end;
    double timeInsert, timeMerge;

    srand((unsigned)time(NULL));

    array = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));
    temp = (int *)malloc(N * sizeof(int));

    if(array == NULL || b == NULL || temp == NULL){
        printf("内存分配失败！\n");
        return 1;
    }

    /* 随机生成 20000 个数，范围 1~1000000 */
    for(i = 0; i < N; i++){
        array[i] = rand() % 1000000 + 1;
        b[i] = array[i];
    }

    /* 插入排序计时 */
    start = clock();
    insert_sort(array, N);
    end = clock();
    timeInsert = (double)(end - start) / CLOCKS_PER_SEC;

    /* 归并排序计时 */
    start = clock();
    merge_sort(b, 0, N - 1, temp);
    end = clock();
    timeMerge = (double)(end - start) / CLOCKS_PER_SEC;

    printf("随机生成 %d 个整数，范围 1~1000000\n", N);
    printf("插入排序耗时：%.6f 秒\n", timeInsert);
    printf("归并排序耗时：%.6f 秒\n", timeMerge);

    printf("插入排序结果验证：%s\n", check_sorted(array, N) ? "有序" : "无序");
    printf("归并排序结果验证：%s\n", check_sorted(b, N) ? "有序" : "无序");

    printf("归并排序后前10个数：");
    for (i = 0; i < 10; i++)
        printf("%d ", b[i]);
    printf("\n");

    /* 对归并排序后的有序数组进行二分查找 */
    key_num = b[N / 2];
    pos = binary_search(b, N, key_num);

    if (pos != -1)
        printf("二分查找：目标值 %d 查找成功，下标为 %d\n", key_num, pos);
    else
        printf("二分查找：目标值 %d 查找失败\n", key_num);

    /* 再查找一个不存在的数 */
    key_num = -1;
    pos = binary_search(b, N, key_num);
    if (pos == -1)
        printf("二分查找：目标值 %d 不存在，查找失败\n", key_num);

    free(array);
    free(b);
    free(temp);


    return 0;
}