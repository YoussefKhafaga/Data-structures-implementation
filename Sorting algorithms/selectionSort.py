import ParentClass


def sort(arr):
    n = len(arr)
    for i in range(0, n - 1):
        min_element = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_element] or arr[j] == arr[min_element]:
                min_element = j
        arr[i], arr[min_element] = arr[min_element], arr[i]
    return arr

class select(ParentClass.SortMethods):
    pass
