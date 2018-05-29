#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seqstack1.h"

void Swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

/*************************************
 *
 *冒泡排序
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：稳定排序
 *
 *************************************/
void BubbleSort(int array[],size_t size)
{
    if(size <= 1)
    {
        //只有0个或者1个元素
        return ;
    }
    //[0,bound)元素表示有序元素，[bound,size)表示待排序元素
    size_t bound = 0;//边界
    for(; bound < size ; ++bound)
    {
        size_t cur = size - 1;
        for(; cur > bound ; --cur)
        {
            if(array[cur] < array[cur - 1])//cur从最后一个元素往前走，将最小的元素往前冒
            {
                Swap(&array[cur],&array[cur - 1]);
            }
        }
    }
    return ;
}

/*************************************
 *
 *选择排序
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
void SelectSet(int array[],size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    //[0,bound)为有序区间
    //[bound,size)为待排序区间
    size_t bound = 0;//相当于是擂台
    for(; bound < size ;++bound)
    {
        size_t cur = bound + 1;
        for(; cur < size ; ++cur)
        {
            if(array[bound] > array[cur])
            {
                Swap(&array[bound],&array[cur]);
            }
        }
    }
    return ;
}

/*************************************
 *
 *插入排序
 *把有序区间当作线性表，把当前bound指向的元素插入到线性表中
 *
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：稳定排序
 *选择排序特点：
 *a.当数组元素个数少的时候，执行效率快
 *b.若数组基本有序，执行效率也块
 *
 *************************************/
void InsertSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    //[0,bound)为有序区间
    //[bound,size)为待排序区间
    //插入排序把前面的有序区间当作线性表
    //再将bound位置的元素插入到线性表的合适位置中
    size_t bound = 1;
    for(; bound < size ;++bound)
    {
        //此时存起来的意义是为了方便后面的搬运，
        //一旦 array[bound]元素被单独保存起来
        //array[bound]的值就可以被修改了
        int bound_value = array[bound];
        //从此处的cur是辅助我们进行搬运的下标会从后往前遍历，
        //找到合适的位置，bound_value的位置
        size_t cur = bound;
        for(; cur > 0; --cur)
        {
            if(array[cur - 1] > bound_value)
            {
                //进行搬运
                array[cur] = array[cur - 1];
            }
            else
            {
                //说明已经找到了合适的位置
                break;
            }
        }
        array[cur] = bound_value;
    }
    return ;
}


/*************************************
 *
 *堆排序
 *时间复杂度为O(N*logN)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
#if 1
void AdjustDown(int array[],size_t size,size_t index)
{
    size_t parent = index;
    size_t child = 2*parent+1;
    while(child < size)
    {
        if(child+1 < size && array[child+1] > array[child])
        {
            child = child+1;
        }
        //经历了上面的判定之后，child就指向了左右子树中较大的那个
        if(array[parent] < array[child])
        {
            Swap(&array[parent],&array[child]);
        }
        parent = child;
        child = 2*parent+1;
    }
    return ;
}

//方法一：把新元素放到堆数组的末尾，上浮式（从前往后遍历）
void HeapCreate(int array[],size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    size_t i = (size-1-1)/2;
    for(; i > 0;--i)
    {
        AdjustDown(array,size,i);
    }
    AdjustDown(array,size,0);
}
#endif


void  AdjustUp(int array[],size_t size,size_t index)
{
    (void)size;
    size_t child = index;
    size_t parent = (child - 1)/2;
    while(child > 0)
    {
        if(array[parent] < array[child])
        {
            Swap(&array[parent],&array[child]);
        }
        else
        {
            break ;
        }
        child = parent;
        parent = (child - 1)/2;
    }
}

#if 0
//方法二：采用下沉式的调整（从后往前遍历，其实位置为堆的从后往前遍历的第一个叶子节点）
void HeapCreate(int array[],size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    size_t bound = 0;
    for(;bound < size;++bound)
    {
        AdjustUp(array,bound+1,bound);
    }
}
#endif


void HeapPop(int array[],size_t heap_size)
{
    if(heap_size <= 1)
    {
        return ;
    }
    Swap(&array[0],&array[heap_size-1]);
    AdjustDown(array,heap_size-1,0);
}

void HeapSort(int array[],size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    //1.基于数组建立一个堆（若是升序，用大堆）
    HeapCreate(array,size);
    //2.循环地删除堆顶元素，将所有元素删除完毕，排序完成
    size_t i = 0;
    for(; i < size-1 ; ++i)
    {
        //第二个参数表示数组中哪部分区间是符合堆地规则
        //第一次删除前：[0,size)都是堆
        //第二次删除前：[0,size-1)都是堆
        //第三次删除前：[0,size-2)都是堆
        HeapPop(array,size-1);//删除堆顶元素
    }
}

/*************************************
 *
 *Shell排序
 *时间复杂度:取决于步长序列，对于希尔序列为O(N^2)
 *若选择最优序列，时间复杂度最好能够达到O(N^1.3)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
void ShellSort(int array[],int64_t size)
{
    if(size <= 1)
    {
        return ;
    }
    int64_t gap = size/2;//此时使用希尔序列
    for(; gap > 0;gap/=2)//第一重循环，进行插入排序，此循环执行的顺序相当于先处理第一组的第一个
    {
        int64_t bound = gap;//此处相当于插入排序中的bound=1
        for(; bound < size ; ++bound)
        {
            //此时 bound_value 就是待插入元素
            int bound_value = array[bound];
            //第三重循环——线性表的查找和搬运（同插入排序）
            int64_t cur = bound;
            //此处 cur-=gap就是在找到同组元素的上一个元素
            for(; cur >= gap;cur-=gap)
            {
                if(array[cur-gap] > bound_value)
                {
                    //进行搬运
                    array[cur] = array[cur-gap];
                }
                else
                {
                    break ;
                }
            }
            array[cur] = bound_value;
        }
    }
    return ;
}


/*************************************
 *
 *归并排序(递归版本)
 *时间复杂度为O(N*logN)
 *空间复杂度为O(N)
 *稳定性：稳定排序
 *应用：用来归并链表
 *
 *************************************/
//合并过程
//第一个区间[begin,mid)
//第二个区间[mid,end)
void _MergeArray(int array[],int64_t begin,int64_t mid,int64_t end,int* tmp)
{
    int64_t cur1 = begin;
    int64_t cur2 = mid;
    int64_t tmp_index = begin;//下标
    while(cur1 < mid && cur2 < end)
    {
        if(array[cur1] < array[cur2])
        {
            tmp[tmp_index++] = array[cur1++];
            //上面这条代码相当与下面的三条代码
            //tmp_index[tmp_index] = array[cur1];
            //++cur1;
            //++tmp_index;
        }
        else
        {
            tmp[tmp_index++] = array[cur2++];
        }
    }
    while(cur1 < mid)
    {
        tmp[tmp_index++] = array[cur1++];
    }
    while(cur2 < end)
    {
        tmp[tmp_index++] = array[cur2++];
    }
    memcpy(array + begin , tmp + begin , sizeof(int)*(end - begin));
}

//[begin,end)
void _MergeSort(int array[],int64_t begin,int64_t end,int* tmp)
{
    if(end - begin <= 1)
    {
        //当前元素个数为0或者为1
        return ;
    }
    //下面为(begin + end)/2的升级版本，防止溢出
    int64_t mid = begin + (end - begin)/2;
    //此时有两个区间
    //[begin,mid)
    //[mid,end)
    _MergeSort(array,begin,mid,tmp);
    _MergeSort(array,mid,begin,tmp);
    //要先保证左右区间均为有序区间后才能进行合并
    _MergeArray(array,begin,mid,end,tmp);
    return ;
}

void MergeSort(int array[],int64_t size)
{
    if(size <=1)
    {
        return ;
    }
    int * tmp = (int*)malloc(sizeof(int)*size);
    //创建与原数组一样大的缓冲区临时空间，用来辅助完成合并元素
    //使用一个函数来辅助完成递归操作
    //[0,size)
    _MergeSort(array,0,size,tmp);
    free(tmp);
}

/*************************************
 *
 *归并排序(非递归版本)
 *时间复杂度为O(N*logN)
 *空间复杂度为O(N)
 *稳定性：稳定排序
 *应用：用来归并链表
 *
 *************************************/
void MergeSortByLoop(int array[],int64_t size)
{
    if(size <= 1)
    {
        return ;
    }
    int* tmp = (int*)malloc(sizeof(int)* size);
    int64_t gap = 1;
    for(; gap < size ; gap *= 2)
    {
        int64_t i = 0;
        for(; i < size; i +=2 * gap)
        {
            //每次循环其实就是在处理两个相邻的区间
            int64_t begin = i;
            int64_t mid = i + gap;
            int64_t end = i + 2 * gap;
            if(mid > size)
            {
                mid = size;
            }
            if(end > size)
            {
                end = size;
            }
            //[begin,mid),[mid,end)
            _MergeArray(array,begin,mid,end,tmp);
        }
    }
    free(tmp);
}

/*************************************
 *
 *快速排序
 *时间复杂度：最坏为O(N^2)序列为完全逆序
            平均为O(N*logN)
 *空间复杂度为O(logN)
 *稳定性：不稳定排序
 *
 *************************************/
//快速排序的改进
//1.三值取中确定基准值
//2.当区间比较小的时候，就可以使用插入排序，直接对这个区间进行排序，从而有效的减少递归次数
//3.当递归深度达到一定的程度时，使用堆排序对待排序区间进行排序

//方法一：交换法
int64_t Partion1(int array[],int64_t begin,int64_t end)
{
    //1.先定义好区间的边界
    int64_t left = begin;
    int64_t right = end - 1;
    //2.取最后一个元素作为基准值key
    int key = array[right];
    while(left < right)
    {
        //3.从左到右找到一个大于基准值key的元素
        while(left < right && array[left] <= key)
        {
            //要么 left 与 right 重合，要么找到了一个大于基准值key的元素，才最退出循环
            ++left;
        }
        //4.从右往左找到一个小于基准值key的元素
        while(left < right && array[right] > key)
        {
            //要么 left 与 right 重合，要么找到了一个小于基准值key的元素，才最退出循环
            --right;
        }
        //5.进行交换
        if(left < right)
        {
            Swap(&array[left],&array[right]);
        }
    }
    //6.此时是将 left指向的值和最后一个元素（基准值）进行交换
    //此时 left 指向的值一定大于基准值
    // a)若是因为++left导致的循环退出，由于 right 在上一次循环的交换中已经指向了一个大于等于基准值的元素
    // b)若是因为--right导致的循环退出，由于在刚刚的 left 查找过程中 left 已经找到了一个大于等于基准值的元素
    // 因此，最终的结论是：left指向的值一定大于基准值
    //因为此时 left 与 right 重合了，因此下面是写 left 还是 right 与最后一个元素交换都可以
    Swap(&array[left],&array[end - 1]);
    return left;

}

//方法二：挖坑法
int64_t Partion2(int array[],int64_t begin,int64_t end)
{
    //1.先定义好边界
    int64_t left = begin;
    int64_t right = end - 1;
    //2.取最后一个元素作为基准值
    int key = array[right];
    while(left < right)
    {
        //3.从左到右找到一个大于基准值
        while(left < right && array[left] <= key)
        {
            ++left;
        }
        if(left < right)
        {
            //将找到的大于基准值的元素填到 right 指向的坑里
            //随着填坑动作的完成，left指向的位置也就可以被别人覆盖
            //left也就成为了一个坑
            array[right--] = array[left];
        }
        //4.从右往左找到一个小于基准值
        while(left < right && array[right] >= key)
        {
            --right;
        }
        if(left < right)
        {
            array[left++] = array[right];
        }
    }
    array[left] = key;
    return left;
}

//方法三：双指针前移法（仅供参考）
int64_t Partion3(int array[],int64_t begin,int64_t end)
{
    int64_t cur = begin;
    int64_t pre = begin - 1;
    int key = array[end - 1];
    while(cur < end)
    {
        if(array[cur] < key && ++pre != cur)
        {
            Swap(&array[cur],&array[pre]);
        }
        ++cur;
    }
    if(++pre != end)
    {
        Swap(&array[pre],&array[end - 1]);
    }
    return pre;
}

void _QuickSort(int array[],int64_t begin,int64_t end)
{
    if(end - begin <= 1)
    {
        return ;
    }
    //Partion函数的作用，是对当前[begin,end)区间进行整理
    //整理成以某个基准key为中心，左侧元素小于基准值
    //右边元素大于基准值
    //返回值表示的含义是基准值所在的下标
    int64_t mid = Partion1(array,begin,end);
    _QuickSort(array,begin,mid);
    _QuickSort(array,mid + 1,end);
}

void QuickSort(int array[],int64_t size)
{
    _QuickSort(array,0,size);
}

/*************************************
 *
 *快速排序(非递归版本)
 *借助一个棧
 *时间复杂度：最坏为O(N^2)序列为完全逆序
            平均为O(N*logN)
 *空间复杂度为O(logN)
 *稳定性：不稳定排序
 *
 *************************************/
void QuickSortByLoop(int array[],int64_t size)
{
    if(size <= 1)
    {
        return ;
    }
   SeqStact stack;
   SeqStactInit(&stack);
   int64_t begin = 0;
   int64_t end = size;
   SeqStactPush(&stack,begin);
   SeqStactPush(&stack,end);
   while(stack.size > 0)//棧不为空
   {
       SeqStactTop(&stack,&end);
       SeqStactPop(&stack);
       SeqStactTop(&stack,&begin);
       SeqStactPop(&stack);
       if(end - begin <= 1)
       {
           continue;
       }
       int64_t mid = Partion1(array,begin,end);
       SeqStactPush(&stack,begin);
       SeqStactPush(&stack,mid);
       SeqStactPush(&stack,mid + 1);
       SeqStactPush(&stack,end);
   }

}

