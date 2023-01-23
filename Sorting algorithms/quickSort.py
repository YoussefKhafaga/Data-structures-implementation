import sys

import ParentClass

sys.setrecursionlimit(10**7)


def partition(array, start, end):
    pivot = start
    index = start + 1
    while index <= end:
        if array[index] < array[start]:
            pivot += 1
            array[index], array[pivot] = array[pivot], array[index]
        index += 1
    array[pivot], array[start] = array[start], array[pivot]
    return pivot


def quicksort(array, start, end):
    if start < end:
        pivot = partition(array, start, end)
        quicksort(array, start, pivot - 1)
        quicksort(array, pivot + 1, end)
    return array


def sort(array):
    start = 0
    end = len(array) - 1
    arr = quicksort(array, start, end)
    return arr


class insert(ParentClass.SortMethods):
    pass
