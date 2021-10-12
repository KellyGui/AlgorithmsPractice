// sortAlgorithms.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//bubleSort
void bubleSort(vector<int> &nums){
    int n = nums.size();
    //if (n == 1) return;
    int border = n-1;
    int lastChangeIndex = 0;
    for (int i = 0; i < n; ++i) {
        bool flag = true;
        for (int j = 0; j < border; ++j)
        {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                flag = false;
                lastChangeIndex = j;
            }
        }
        if (flag) break; //优化1， 省略对已经有序的数组进行排序
        border = lastChangeIndex; //优化2， 一次内存循环后，会形成一个有序的子序列，长度可能比i的值大，所以灵活调整排序边界
    }
}

//selectionSort
void selectionSort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i)
    {
        //int minIdx = i;
        for (int j = i + 1; j < n; ++j) { //找到最小项，置换到位置i
            if (nums[i] > nums[j])
                swap(nums[i],nums[j]);
        }
    }
}


//insertSort
void insertionSort(vector<int>& nums) { //向已排好序的数组中插入新数据
    int n = nums.size();
    for (int i = 1; i < n; ++i) //nums[i]是待插入数据
    {
        int tmp = nums[i];
        int j;
        for (j = i-1; j >= 0; --j)
        {
            if (nums[j] > tmp)
            {
                nums[j + 1] = nums[j];
            }
            else break;
        }
        nums[j+1] = tmp;
    }
}

//shellSort
void shellSort(vector<int>& nums) {
    int n = nums.size();
    int gap = n / 2;
    while (gap) {
          for (int i = gap; i < n; i += gap) {
              int tmp = nums[i];
              int j;
              for (j = i-gap; j >= 0; j -= gap) {
                  if (nums[j] > tmp) {
                      nums[j + gap] = nums[j];
                  }
                  else
                      break;
              }
              nums[j + gap] = tmp;
          }
          gap /= 2;
    }
    
}

//quickSort
void quick_sort(vector<int>& nums, int l, int r)
{
    if (l < r) {
        int x = nums[l], i = l, j = r;
        while (i < j) {
            while (i < j && nums[j] >= x) --j;
            if (i < j) nums[i++] = nums[j];
            while (i < j && nums[i] <= x) ++i;
            if (i < j) nums[j--] = nums[i];
        }
        nums[i] = x;
        quick_sort(nums, l, i);
        quick_sort(nums, i + 1, r);
    }
}

void quickSort(vector<int>& nums) {
    quick_sort(nums, 0, nums.size()-1);
}

//mergeSort

void merge(vector<int>& nums, int first, int mid, int end, int p[]) {
    int i = first, j = mid + 1, m = mid, n = end;
    int k = 0;
    while (i <= m && j <= n) {
        if (nums[i] < nums[j]) {
            p[k++] = nums[i++];
        }
        else p[k++] = nums[j++];
    }
    while(i<=m) p[k++] = nums[i++];
    while(j<=n) p[k++] = nums[j++];
    for (int l = 0; l < k; ++l) {
        nums[first + l] = p[l];
    }
}
void mergeSort_split(vector<int>& nums, int first, int end, int p[]) {
    if (first < end)
    { 
        int mid =(first+ end) / 2;
        mergeSort_split(nums, first, mid, p);
        mergeSort_split(nums, mid+1, end, p);
        merge(nums, first, mid, end, p);
    }
}
void mergeSort(vector<int>& nums) {
    int n = nums.size();
    int* p = new int[n];
    if (p == nullptr) return;
    mergeSort_split(nums, 0, nums.size() - 1, p);
}


//heapSort
void adjustHeap(vector<int>& nums, int start, int end) {
    int dad = start;
    int son = 2 * dad + 1;
    while (son <= end) {
        if (son+1 <= end && nums[son] < nums[son + 1]) son++;
        if (nums[dad] > nums[son]) return;
        else {
            swap(nums[dad], nums[son]);
            dad = son;
            son = 2 * son + 1;
        }
    }
}
void heapSort(vector<int>& nums) {
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        adjustHeap(nums, i, n - 1);
    for (int j = n-1 ; j > 0; --j) {
        swap(nums[0], nums[j]);
        adjustHeap(nums, 0, j-1);
        }
        
}

//bucketSort


//计数排序,类似基数排序
//需知道排序数组的范围
void bucketSort() {

}


//radixSort 基数排序
int maxDigit(vector<int>& nums) {
    int d = 0;
    int max = nums[0];
    for (int i = 1; i < nums.size();++i) {
        if (max < nums[i]) max = nums[i];
    }
    while (max) {
        max /= 10;
        ++d;
    }
    return d;

}
void radixSort(vector<int>& nums) {
    int digit =  maxDigit(nums);
    int n = nums.size();  
    int count[10]{};
    int* tmp = new int[n];
    int radix = 1;
    while(digit){
        for (int i = 0; i < 10; ++i)
            count[i] = 0;
        for (int j = 0; j < n; ++j) {
            int k = (nums[j]/ radix) % 10;
            count[k]++;
        }
        for (int j = 1; j < 10; ++j)
            count[j] = count[j - 1] + count[j];
        for (int i = n - 1; i >= 0; --i) {
            int k = (nums[i]/radix) % 10;
            tmp[count[k] - 1] = nums[i];
            count[k]--;
        }
        for (int i = 0; i < n; ++i) {
            nums[i] = tmp[i];
        }
        radix *= 10;
        --digit;
    }
    delete[] tmp;
}


int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int maxData = data[0];              ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
 
}
void radixsort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int* tmp = new int[n];
    int* count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for (j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}

void display(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i)
        cout << nums[i] << ' ';
    cout << endl;
}

void display(int data[], int n) {
    for (int i = 0; i < n; ++i)
        cout << data[i] << ' ';
    cout << endl;
}
int main()
{
    vector<int>  nums = { 5 ,3,7,8,10,2,1,0 };
    int data[8] = { 5 ,3,7,8,10,2,1,0 };
    //bubleSort(nums);
    //selectionSort(nums);
    //insertionSort(nums);
    //shellSort(nums);
    //mergeSort(nums);
    //quickSort(nums);
    //heapSort(nums);
    radixSort(nums);
    radixsort(data, 8);
    display(data, 8);
    display(nums);

    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
