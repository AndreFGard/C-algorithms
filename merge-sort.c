#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mergesort(int *array, int start, int end);
void merge(int *array, int start, int middle, int end);
int main(void)
{

    int nums[] = {8,7,6,5,4,3};
    mergesort(nums, 0, sizeof(nums)/sizeof(int) - 1);
    printf("merged array:");
    for (int i = 0; i < sizeof(nums)/sizeof(int); i++)
        printf("%d,", nums[i]);

}

void mergesort(int array[], int start, int end)
{
    float size = end - start + 1;
    //DEBUGprintf("Printing vars: size=%f  start:%d  end:%d\n", size, start, end);
    if (size == 1) return;                           //    Already sorted, else, sort

    float end1 = ceil( size / 2) + start - 1,        //    Middle index, where the first half ends and right before where the second half starts
    start2 = end1 + 1;                               //    Start of the first half1
    //DEBUGprintf("\t\tmiddle is: %f | ceil: %d + %d - 1\n", end1, (int) ceil(size/2), start);


    mergesort(array, start, end1);      //  sort the first half
    mergesort(array, start2, end);      //  sort the second half
    //DEBUGprintf("merging start: %d, end1:%d, end:%d:\n", start, (int) end1, end);
    merge(array, start, end1, end);     // Now that we are sure that each half is sorted, we can merge them
    //DEBUGfor(int i = start; i < end; i++) printf("\tarray[%d]:%d\n", i, array[i]);

    return;
}

void merge(int *array, int start, int end1, int end)
{
    int size = end - start + 1;
    int buffer[size]; 
    //DEBUGfor (int h = 0; h < size; h ++) buffer[h] = 69;
    int a = start,      //  loops through the first half
    b = end1 + 1,     //  loops through the second half
    z = 0;              //  position of the buffer for (int a = start, b = middle + 1, p = 0, i = start; i <= end; i++)
    

    while(a <= end1 && b <= end)  // while none of the halves have been 100% sorted
    {
        // a loops through the first half and b through the second one, z keeps the buffer's index
        if (array[b] <= array[a]) // if the sec half element is smaller than the first half element
        {
            buffer[z] = array[b]; // then it must occupy the [i] position
            //  next time, check again with the next element of the second half
            b++;
            z++;
        }
        else
        {
            buffer[z] = array[a]; // then array[a]  is smaller
            a++;
            z++;
        }
    }


    //  one of the halves has been sorted already, meaning that all the numbers in the other half are bigger than everything already sorted and buffered
    //  if the first one was sorted
    if (a > end1)
    {
        //  just copy the rest of the second half into the buffer
        //  there is actually no need to do this, we could jump to copying the buffer elements into the array until i = end - b, because the rest is there already
        while (b <= end)
        {
            //DEBUGprintf("A sorted, copying\n");
            buffer[z] = array[b];
            b++;
            z++;
        }
    }
    else
    {
        while (a <= end1)
        {
            //D//DEBUGprintf("reached end of merge, copying\n");
            buffer[z] = array[a];
            a++;
            z++;
        } 
    }

    for (int x = 0; x < size; x++)
        {
            //DEBUGprintf("\t\tbuffer[%d] %d\n", x , buffer[x]);
            array[start + x] = buffer[x];
        }
}