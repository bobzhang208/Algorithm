#include <iostream>
#include <stack>

using namespace std;

/* 该函数取最后一个元素作为基准，将比基准小的元素放在基准前面，
   比基准大的元素放在基准后面，这个操作称为分区操作。
   它返回基准正确排序后的索引位置。 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // 基准
    int i = (low - 1);  // 较小元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;    // 增加较小元素的索引
            std::swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// arr[] --> 排序数组，low --> 起始索引，high --> 结束索引
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        /* pi 是 partitioning index，arr[pi] 现在
           放在正确的位置 */
        int pi = partition(arr, low, high);

        // 分别对分区前后的元素进行排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int partSort(int* array,int left,int right)
{
    if(left < right){
        int key = array[right];
        int cur = left;
        int pre = cur - 1;
        while(cur < right)
        {
            while(array[cur] < key && ++pre != cur)//如果找到小于key的值，并且cur和pre之间有距离时则进行交换。注意两个条件的先后位置不能更换，可以参照评论中的解释
            {
                swap(array[cur],array[pre]);
            }
            ++cur;
        }
        swap(array[++pre],array[right]);
        return pre;
    }
    return -1;
}

void quickSortNotR(int* array,int left,int right)
{
    stack<int> s;
    s.push(left);
    s.push(right);//后入的right，所以要先拿right
    while(!s.empty())//栈不为空
    {
        int right = s.top();
        s.pop();
        int left = s.top();
        s.pop();

        int index = partSort(array,left,right);
        if((index - 1) > left)//左子序列
        {
            s.push(left);
            s.push(index - 1);
        }
        if((index + 1) < right)//右子序列
        {
            s.push(index + 1);
            s.push(right);
        }
    }
}