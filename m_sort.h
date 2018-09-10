#ifndef _M_SORT_H
#define _M_SORT_H

#include"m_sort.h"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
/*
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    void *elements;
    int size;
    int maxsize;
};
*/
void Swap(void *a, void *b, int width);
int Hibbard(int num);
/*MaxHeap HeapCreate(int maxsize);
void HeapInsert(MaxHeap H, void * item, int width, int (*cmp)(void *, void *));
void *HeapDelete(MaxHeap H);*/
void ModifyDown(void *base, int begin, int end, int width, int cmp(const void *, const void *));
void MergeS(void *base,void *tmpBase, int num, int length, int width, int cmp(const void *, const void *));
void *Median(void *base, int left, int right, int width, int cmp(const void *, const void *));
void QuickSort(void *base, int cutoff, int left, int right, int width, int cmp(const void *, const void *));

void MySelectionSort(void *base, int num, int width, int cmp(const void *, const void *));
void MyInsertionSort(void *base, int num, int width, int cmp(const void *, const void *));
void MyBubbleSort(void *base, int num, int width, int cmp(const void *, const void *));

void MyShellSort(void *base, int num, int width, int cmp(const void *, const void *));
void MyHeapSort(void *base, int num, int width, int cmp(const void *, const void *));
void MyMergeSort(void *base, int num, int width, int cmp(const void *, const void *));
void MyQuickSort(void *base, int num, int width, int cmp(const void *, const void *));


#endif
