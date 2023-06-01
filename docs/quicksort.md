

# Quicksort
The quicksort or quick sort algorithm is a divide and conquer algorithm and one of the most popular algorithms, that works by selecting a *pivot* element and then ordering the array in a way so that everything smaller than the pivot is positioned to it's left (before it) and everything bigger is positioned to it's right, and then applying quicksort recursively to each of those sides. 



It differs from mergesort because the work is done in the division part, there is no merging* (in this implementation). Quicksort is also in-place*. In the original implementation, we always select the last element as the pivot, but this is an [issue](#quicksort-issues) that can cause the algorithm to reach it's worst case performance (N²).

### index
1. [Quicksort](#quicksort)
2. [Quicksort steps](#steps)
3. [Explanation](#explanation)
4. [Issues](#issues)



## steps
1. Check if there is nothing to sort
2. While we dont break: if array\[ScoutIdx\] > pivot, it must be swapped. Continue looping till we find an element smaller (than the pivot), which can be swapped with the bigger one found earlier and whose position swapIdx will store. If we find another bigger, pass it too, because it's either in place already or will be swapped and put in place later.
3. *else*, the element <= pivot, and there are 3 possible conclusions out of this:
    1. scoutIdx has looped through the entire array or array segment. If yes, scoutIdx will == end, and we must swap the pivot, put it in place and break out of the while.S
    2. We must swap it with a smaller element. If true, swapIdx will hold the position of the bigger and scoutIdx of the smaller, which was just found. 
    3. We dont need to do or swap anything. In that case, both Idxs will hold the same positions.
4. NOTE: We can find a situation in which swapIdx == scoutIdx (means that there is nothing to swap) && scoutIdx == end (means that we must swap the pivot and put it in place). Those two conclusions are conflicting, however,  and that's why we must check both instead of if elsing. Note that we can also find a situation in which scoutIdx == end but swapIdx != scoutIdx.
5. Apply quicksort recursively to the part to the left and to the right

## Explanation 
 The scout index loops through the array, looking for an element bigger than pivot, that is, an element that should be swapped with some other element that is smaller than the pivot and is currently in the wrong position too. Those are the steps "followed" by scout in the swapping of elements context. If you want a less abstracted and more direct approach, read the actual steps [here](#steps):
1. Once it finds one bigger element, scout leaves it's friend, the swap index, marking the position right before the misplaced el that we'll swap, and proceeds to look for another misplaced element, but this time we are looking for a smaller el.
2.  After finding it, we'll have the position of two elements that _should_ be swapped, one that should go to the "left" and other to the right, (the element smaller than the pivot and the element bigger than the pivot, respectively,) so we swap++, so that swap moves to the right position, and then swap them. 

## Issues

1. Quicksort's Big Theta is nlogn, and it is achieved when we select the median element (the one that would occupy the middle position if the array was sorted) as the pivot, dividing the array then in two equal parts always. However, if the list is sorted, selecting the first or last element of the array would lead us to the worst case performance (N²), because we would sort a single element per recursion. This can be solved by:
    1.1 Selecting the middle element of the array, because if it is sorted we'll get the best case performance instead of the worst
    1.2 Randomly choosing the pivots
