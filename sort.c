#include <stdio.h>
#include <stdlib.h>

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
 *归并排序
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
void _MergeSort(int array[],int64_t begin,int64_t end,int* tmp)
{
    if(end - begin <= 1)
    {
        return ;
    }
    int64_t mid = begin+(end - begin)/2;
    //此时有两个区间
    //[begin,mid)
    //[mid,end)
    _MergeSort(array,begin,mid,tmp);
    _MergeSort(array,mid,begin,tmp);
    _MergeArray(array,begin,mid,endif,tmp);
    return ;
}

void MergeSort(int array[],size_t size)
{
    if(size <=1)
    {
        return ;
    }
    int * tmp = (int*)malloc(sizeof(int)*size);
    _MergeSort(array,0,size,tmp);
    free(tmp);
}
/*************************************
 *
 *选择排序
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
/*************************************
 *
 *选择排序
 *时间复杂度为O(N^2)
 *空间复杂度为O(1)
 *稳定性：不稳定排序
 *
 *************************************/
