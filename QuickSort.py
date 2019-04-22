import random

MAX_RANGE = 10000
RANDOM = False

try:
    numOfInt = input("Input number of integers: ")
    numOfInt = int(numOfInt)
    randomizer = input("Would you like to generate random numbers? (Y/N): ")
    
    # IF randomizer is anything but yes or y then RANDOM is kept false
    if randomizer.lower() in ("yes", "y"):
        RANDOM = True
    else:
        print("Randomizer not set.")
        # As mentioned in the directions, we are to set a number for the sorted array to increment the array 
        incremental = input("Set a number to increment the sorted array elements by: ")
    
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
    print(arr)

except ValueError as err:
    print("Value error: {0}".format(err))
    print("**INPUT WAS PROBABLY NOT AN INTEGER**")