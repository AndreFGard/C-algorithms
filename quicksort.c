#include <stdio.h>


void quicksort(int *array, int start, int end);
int main(void) {

int array[] = {3, 2, 5, 0, 1, 8, 7, 6, 9, 4};

int endarray = 9;
int start = 0;

quicksort(array, start, endarray);
for (int i = 0; i < endarray + 1; i++) printf("%d,", array[i]);
printf("\n");

}

void quicksort(int *array, int start, int end){

if ((end - start) == 0) 
{
    printf("%d - %d = 0\n", end, start);
    return;
}


int pivot = array[end];
int swap;
//  scoutIdx searches for elements that must to be sorted by looping through the array,
// swapIdx marks the position of one of the elements that we'll swap
int scoutIdx = start, swapIdx = start - 1;

while(1)
{
    if (array[scoutIdx] > pivot) {
        printf("%d > %d, pass\n", array[scoutIdx], pivot);
        scoutIdx++;

    }
    else 
    {
        swapIdx++;
        printf("%d <= %d, pass\n", array[scoutIdx], pivot);
        // it's <= pivot.
        if (scoutIdx == end){
            // if we got to the end of the array and have to put the pivot in place
            array[end] = array[swapIdx];
            array[swapIdx] = pivot;
            printf("\tpivot reached\n");
            break;
                
        }
        if (scoutIdx == swapIdx){
            // if there is nothing to swap, continue
            printf("scoutidx = swapidx, pass\n");
            scoutIdx++;
        }
        else {
            
                // smaller than the pivot
                // if there is, swap
                swap = array[scoutIdx];  // smaller
                array[scoutIdx] = array[swapIdx];
                array[swapIdx] = swap;
                scoutIdx++;
        }
    }
}
printf("Recursion time: ");
for (int i = 0; i < end + 1; i++)
{
    if (i == start) 
        printf("|");
    printf("%d,", array[i]);
    if (i == end) printf("|");
    
} 
printf("\n");
// recursively quicksort each part, start-pivotindex and pivotindex+1-end
// todo: check if those arrays segments are of length 0 before calling funcs over them
quicksort(array, start, swapIdx - 1);
quicksort(array, swapIdx, end);


}