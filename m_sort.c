#include "m_sort.h"

void ModifyDown(void *base, int begin, int end, int width, int cmp(const void *, const void *))
{
    int parent, child;
    void *temp = (void *)malloc(width);
    memcpy(temp, base + (begin)*width,width);
    for (parent = begin; parent * 2 + 1 < end; parent = child) {
        child = 2 * parent + 1;
        if (child != (end -1) && cmp(base + child * width, base + (child + 1) * width) < 0) {
            child++;
        }
        if (cmp(temp , base + child * width) >= 0) 
            break;
        else
            memcpy(base + parent * width, base + child * width, width);
    }
    memcpy(base + parent * width, temp, width);
    free(temp);
}


void MergeS(void *base,void *tmpBase, int num, int length, int width, int cmp(const void *, const void *))
{
    int i, l, r, tmp;
    for (i = 0; i <= num - 2 * length; i += 2 * length ) {
        l = i; r = i + length; tmp = l;
        while (l < i + length && r < i + 2 * length) {
            if(cmp(base + l * width, base + r * width) > 0)
                memcpy(tmpBase + (tmp++) * width, base + (r++) * width, width);
            else
                memcpy(tmpBase + (tmp++) * width, base + (l++) * width, width);
        }
        while (l < i + length)
            memcpy(tmpBase + (tmp++) * width, base + (l++) * width, width);
        while (r < i + 2*length)
            memcpy(tmpBase + (tmp++) * width, base + (r++) * width, width);
    }

    if (i + length >= num) {
    	tmp = i;
        while (i < num)
            memcpy(tmpBase + (tmp++) * width, base + (i++) * width, width);
    }
    else {
        l = i; r = i + length; tmp = l;
        while (l < i + length && r < num) {
            if(cmp(base + l * width, base + r * width) > 0)
                memcpy(tmpBase + (tmp++) * width, base + (r++) * width, width);
            else
                memcpy(tmpBase + (tmp++) * width, base + (l++) * width, width);
        }
        while (l < i + length)
            memcpy(tmpBase + (tmp++) * width, base + (l++) * width, width);
        while (r < num)
            memcpy(tmpBase + (tmp++) * width, base + (r++) * width, width);

    }

}

void *Median(void *base, int left, int right, int width, int cmp(const void *, const void *))
{
    int middle = (left + right) / 2;
    if (cmp(base + left * width, base + middle * width) > 0)
        Swap(base + left * width, base + middle * width, width);
    if (cmp(base + middle * width, base + right * width) > 0)
        Swap(base + right * width, base + middle * width, width);
    if (cmp(base + left * width, base + middle * width) > 0)
        Swap(base + left * width, base + middle * width, width);
    Swap(base + middle * width, base + (right-1) * width, width);
    return base + (right-1)*width;
}

void QuickSort(void *base, int cutoff, int left, int right, int width, int cmp(const void *, const void *))
{
    int i, j;
    void *pivot;
    pivot = (void *)malloc(width);
    if (right - left < cutoff) {
        MyInsertionSort(base + left * width, right - left + 1, width, cmp);
    }
    else {
        memcpy(pivot, Median(base, left, right, width, cmp), width);
        i = left;
        j = right - 1;
        while (1) {	 
            while( cmp(base + (++i) * width, pivot) < 0);
            while( cmp(base + (--j) * width, pivot) > 0);
            if ( i < j) {
                Swap(base + i * width, base + j * width, width);
            }
            else
                break;
        }
        Swap(base + i * width, base + (right-1) * width, width);
        QuickSort(base, cutoff, left, i-1, width, cmp);
        QuickSort(base, cutoff, i+1, right, width, cmp);
    }
}

/*
 *if we choose to create a new heap, we can use these code.
 *however, we choose to modify the existing array to a maxheap.
 *
MaxHeap Create(int maxsize, int width)
{
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
    H->elements = (void *)malloc((maxsize + 1) * width);
    H->size = 0;
    H->maxsize = maxsize;
    
    return H;
}

void Insert(MaxHeap H, void * item, int width, int (*cmp)(void *, void *))
{
    int i;
    if (H->maxsize == H->size)) {
        printf("The heap is full!\n");
        return;
    }

    for (i = ++(H->size);i>1 && cmp(H->elements + i/2 * width, item) < 0; i /=2 )
        memcpy(H->elements + i * width, H->elements + i/2 * width);
    memcpy(H->elements + i * width, item, width);
}

void *HeapDelete(MaxHeap H, int width, int (*cmp)(void *, void *))
{
    int parent, child;
    void *maxitem, *tmp;
    if (H->size == 0) {
        printf("The heap is empty!\n");
        return;
    }
    maxitem = H->elements + width;
    H->size--;
    tmp = H->elements + H->size * width;
    for(parent = 1; parent*2 <= H->size; parent = child) {
        child = parent * 2;
        if ( child != H->size && cmp(H->elements + child * width, H->elements + (child + 1) * width) < 0)
            child++;
        if (cmp(tmp, H->elements + child * width) >= 0) 
            break;
        else
            memcpy(H->elements + parent * width, H->elements + child * width, width);
    }
    memcpy(H->elements + parent * width, tmp)
}

*/

void Swap(void *a, void *b, int width)
{
    void *tmp;
    tmp = (void *)malloc(width);
    memcpy(tmp, a, width);
    memcpy(a, b, width);
    memcpy(b, tmp, width);
    free(tmp);
}

int Hibbard(int num)
{
    int result, i;
    for (i = 0; pow(2, i) - 1 <= num; i++);
    result = pow(2, i - 1) - 1;
    return result;
}

void MyBubbleSort(void *base, int num, int width, int (*cmp)(const void *, const void *))
{
    int i, j, flag;
    for(i = num -1; i > 0; i--){
        flag = 0;
        for(j = 0; j < i; j++){
            if (cmp(base + j * width, base + (j+1)*width) > 0) {
                Swap(base + j * width, base + (j+1)*width, width);
                flag = 1;
            }
        }
        if (flag == 0)
            break;        
    }  
}

void MySelectionSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int i, j, tmp;
    for(i = num - 1; i > 0; i--){
        tmp = i;
        for(j = i - 1; j >= 0; j--){
            if(cmp(base + j * width, base + tmp * width) > 0){
                tmp = j;
            }
        }
        Swap(base + i * width, base + tmp * width, width);
    }
}

void MyInsertionSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int i, j, tmp;
    void *temp;
    temp = (void *)malloc(width);
    for (i = 1; i < num; i++) {
        memcpy(temp, base + i * width, width);
        for(j = i; j > 0 && cmp(base + (j - 1)*width, temp) > 0; j--)
            memcpy(base + j * width, base + (j - 1) * width, width);
        memcpy(base + j * width, temp, width);
    }
    free(temp);
}

void MyShellSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int i, j, k, tmp;
    void *temp;
    temp = (void *)malloc(width);
    for (i = Hibbard(num); i > 0; i /= 2) {
        for (j = i; j < num; j++) {
            memcpy(temp, base + j * width, width);
            for(k = j; k >= i && cmp(base + (k - i) * width, temp) > 0; k -= i)
                memcpy(base + k * width, base + (k - i) * width, width);
            memcpy(base + k * width, temp, width);
        }
    }
    
}

void MyHeapSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int i, j, k;
    for (i = num/2; i >= 0; i--) {
        ModifyDown(base, i, num, width, cmp);
    }
    for (i = num - 1; i > 0; i--) {
        Swap(base + 0 * width, base + i * width, width);
        ModifyDown(base, 0, i, width, cmp);
    }
}

void MyMergeSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int length = 1;
    void *tmpBase;
    tmpBase = (void *)malloc(num * width);
    if (tmpBase != NULL ) {
        while (length < num) {
            MergeS(base, tmpBase, num, length, width, cmp);
            length *= 2;
            MergeS(tmpBase, base, num, length, width, cmp);
            length *= 2;
        }
        free(tmpBase);
    }
    else{
    	printf("ERROR! The memory is out of use!\n");
    	return;
	}
}

void MyQuickSort(void *base, int num, int width, int cmp(const void *, const void *))
{
    int cutoff = 100;//cutoff must be bigger than 2
    QuickSort(base, cutoff, 0, num - 1, width, cmp);    
}
