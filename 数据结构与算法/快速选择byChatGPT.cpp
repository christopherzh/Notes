#include <iostream>
#include <vector>
using namespace std;

// 分区函数，将数组划分为小于等于基准元素和大于基准元素的两部分
int partition(vector<int>& arr,int low, int high){
    int pivot=arr[high]; // 选择最后一个元素作为基准
    int index=low; // index用于基准元素的最后归位

    // 遍历数组，将小于等于基准的元素交换到左边
    for(int i=low;i<high;i++){
        if(arr[i]<pivot){
            swap(arr[i],arr[index]);
            index++;
        }
    }

    swap(arr[index],pivot); //不能交换pivot，因为这样的话arr[high]没有没交换到
    return index;
}

// 快速选择函数，用于查找第 k 小的元素
int quickselect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pivot = partition(arr, low, high);  // 划分数组
        if (pivot == k - 1) {
            return arr[pivot];  // 基准元素正好是第 k 小的元素
        } else if (pivot > k - 1) {
            return quickselect(arr, low, pivot - 1, k);  // 在左半部分继续查找
        } else {
            return quickselect(arr, pivot + 1, high, k);  // 在右半部分继续查找
        }
    }
    return -1;  // 处理无效输入
}

int main() {
    vector<int> arr = {5, 2, 8, 12, 1, 6, 3, 9};
    int k = 4;  // 查找第4小的元素

    int kthSmallest = quickselect(arr, 0, arr.size() - 1, k);  // 查找第 k 小的元素
    cout << "The " << k << "th smallest element is: " << kthSmallest << endl;

    return 0;
}