import random
import time
import plotting


def arraygeneration(size):
    arr = []
    for j in range(0, size):
        arr.append(random.randrange(0, 10000, 1))
    return arr


def printarray(arr, n, type):
    print("The", type, "sorted array with size ", n, "is ")
    print(arr,"\n\n")


def sorter(method, type, array1):
    N = 10
    ar = [0] * N
    for i in range(0, 10):
        temp = array1[i].copy()
        start_time = time.time()
        temp = method.sort(temp)
        end_time = time.time()
        printarray(temp, len(temp), type)
        ar[i] = (end_time - start_time)
        print(type, "Sorting time  for size", len(temp), "is ", end_time - start_time,"\n\n")
    return ar
