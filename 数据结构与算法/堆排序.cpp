#include <iostream>
#include <vector>
using namespace std;

// 下沉操作，用于调整堆
void heapify(vector<int> &arr, int size, int root)
{
    int largest = root;                                                      // 假设根节点是最大的
    int left = 2 * root + 1;                                                 // 左子节点的索引
    int right = 2 * root + 2;                                                // 右子节点的索引
    largest = (left < size && arr[largest] < arr[left] ? left : largest);    // 如果左子节点大于根节点，则更新最大值的索引
    largest = (right < size && arr[largest] < arr[right] ? right : largest); // 如果右子节点大于根节点，则更新最大值的索引

    // 如果最大值不是根节点，则交换根节点和最大值，并继续调整堆
    if (largest != root)
    {
        swap(arr[largest], arr[root]);
        heapify(arr, size, largest);
    }
}
void heapSort(vector<int> &arr)
{
    int size = arr.size();
    // 构建最大堆，从最后一个非叶子节点开始向上调整
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    // 从堆顶开始依次取出最大值，然后调整堆
    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]); // 将最大值（堆顶）放到已排序部分的末尾
        heapify(arr, i, 0);   // 调整堆
    }
}

int main()
{
    std::vector<int> arr = {5, 2, 8, 12, 3};

    heapSort(arr);

    std::cout << "排序后的数组：";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}