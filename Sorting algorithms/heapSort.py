import ParentClass


def heapify(arr, num, i):
    largest = i
    right = 2 * i + 2
    left = 2 * i + 1

    if left < num and arr[largest] < arr[left]:
        largest = left

    if right < num and arr[largest] < arr[right]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]

        heapify(arr, num, largest)


def sort(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr
