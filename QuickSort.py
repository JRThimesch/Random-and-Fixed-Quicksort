import random
import timeit

MAX_RANGE = 10000
RANDOM = False
RANDOM_PIVOT = False

def partition(array, begin, end):
    if RANDOM_PIVOT:
        pivot = random.randrange(len(array))
    else:
        pivot = end

    print("pivot set to: ", pivot)
    
    for i in range(begin+1, end+1):
        if array[i] <= array[begin]:
            pivot += 1
            array[i], array[pivot] = array[pivot], array[i]
    array[pivot], array[begin] = array[begin], array[pivot]
    return pivot


def quicksort(array, begin=0, end=None):
    if end is None:
        end = len(array) - 1
    def _quicksort(array, begin, end):
        if begin >= end:
            return
        pivot = partition(array, begin, end)
        _quicksort(array, begin, pivot-1)
        _quicksort(array, pivot+1, end)
    return _quicksort(array, begin, end)

# This function takes last element as pivot, places 
# the pivot element at its correct position in sorted 
# array, and places all smaller (smaller than pivot) 
# to left of pivot and all greater elements to right 
# of pivot 
def partition(arr,low,high): 
    i = ( low-1 )         # index of smaller element 
    pivot = arr[high]     # pivot 
  
    for j in range(low , high): 
  
        # If current element is smaller than or 
        # equal to pivot 
        if   arr[j] <= pivot: 
          
            # increment index of smaller element 
            i = i+1 
            arr[i],arr[j] = arr[j],arr[i] 
  
    arr[i+1],arr[high] = arr[high],arr[i+1] 
    return ( i+1 ) 
  
# The main function that implements QuickSort 
# arr[] --> Array to be sorted, 
# low  --> Starting index, 
# high  --> Ending index 
  
# Function to do Quick sort 
def quickSort(arr,low,high): 
    if low < high: 
  
        # pi is partitioning index, arr[p] is now 
        # at right place 
        pi = partition(arr,low,high) 
  
        # Separately sort elements before 
        # partition and after partition 
        quickSort(arr, low, pi-1) 
        quickSort(arr, pi+1, high) 


try:
    numOfInt = input("Input number of integers: ")
    numOfInt = int(numOfInt)
    reply = input("Would you like to generate random numbers? (Y/N): ")
    
    # IF reply is anything but yes or y then RANDOM is kept false
    if reply.lower() in ("yes", "y"):
        RANDOM = True
    else:
        print("Randomizer not set.")
        # As mentioned in the directions, we are to set a number for the sorted array to increment the array 
        incremental = input("Set a number to multiply and increment the sorted array elements by: ")
    
    reply = input("Would you like to use randomized quicksort? (Y/N): ")

    # IF reply is anything but yes or y then RANDOM is kept false
    if reply.lower() in ("yes", "y"):
        print("Using randomized quicksort.")
        RANDOM_PIVOT = True
    else:
        print("Using regular quicksort.")
    
    arr = []
    print("Generating a list of", numOfInt, "numbers")
    if RANDOM:
        for x in range(numOfInt):
            element = random.randrange(MAX_RANGE)
            arr.append(element)
    else:
        for x in range(numOfInt):
            element = (x + 1) + (x + 1) * (int(incremental))
            arr.append(element)
    
    print("BEFORE SORT:", arr)
    start_time = timeit.default_timer()
    
    quicksort(arr)
    
    elapsed = timeit.default_timer() - start_time

    print("AFTER SORT:", arr)
    print("RUNNING TIME:", elapsed)
except ValueError as err:
    print("Value error: {0}".format(err))
    print("**INPUT WAS PROBABLY NOT AN INTEGER**")