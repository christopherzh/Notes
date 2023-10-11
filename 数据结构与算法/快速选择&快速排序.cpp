// 找出给定数组中第k小的元素，k从0开始计数，详见 https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E9%80%89%E6%8B%A9
#include <iostream>
#include <vector>
using namespace std;

int partition(int l, int r, int pivot, vector<int> &nums)
{
	swap(nums[pivot], nums[r]); // 将用于比较的枢纽点与最后节点的元素进行交换
	int storeIndex = l;			// 存放最终枢纽点应存入的位置
	for (int i = l; i < r; i++)
	{
		if (nums[i] < nums[r]) // 因为第一步的交换，r的位置上就是枢纽点
		{									 // 当前元素比枢纽元素小
			swap(nums[storeIndex], nums[i]); // 交换存档点与i的位置
			storeIndex++;					 // 因为存档点现在为i，比枢纽元素小，所以存档点应前移
		}
	}
	swap(nums[storeIndex], nums[r]); // i走到了最右侧，当前storeIndex的左侧全比枢纽元素小，右侧全比枢纽元素大，应当将枢纽元素放入此位置
	return storeIndex;
}

// 快速选择实现
int quickSelect(int l, int r, int k, vector<int> &nums)
{
	int pivot = l + (r - l) / 2;
	pivot = partition(l, r, pivot, nums);
	if (k == pivot)
	{ // 已找到第k小的元素位置
		return nums[pivot];
	}
	if (k < pivot)
	{ // 第k小的元素在当前枢纽点所在位置的左边，应在左侧寻找
		return quickSelect(l, pivot - 1, k, nums);
	}
	return quickSelect(pivot + 1, r, k, nums); // 第k小的元素在当前枢纽点所在位置的右边，应在右侧寻找
}

// 快速排序实现
int quickSort(int l, int r, vector<int> &nums)
{
	if (l < r)
	{
		int pivot = l + (r - l) / 2;
		pivot = partition(l, r, pivot, nums);
		quickSort(l, pivot - 1, nums);
		quickSort(l + 1, pivot, nums);
	}
}
int main()
{

	vector<int> nums{4, 2, 12, 8, 6, 10, 14};

	// 快速选择
	for (int i = 0; i <= nums.size() - 1; i++)
	{ // 输出从第0小到第nums.size()-1小的元素
		cout << quickSelect(0, nums.size() - 1, i, nums) << " ";
	}
	cout << endl;
	vector<int> arr = {5, 2, 8, 12, 1, 6, 3, 9};
	// 快速排序
	quickSort(0, arr.size() - 1, arr);
	for (auto i : arr)
	{
		cout << i << " ";
	}
	return 0;
}