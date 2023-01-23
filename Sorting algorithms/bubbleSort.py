import ParentClass


def sort(array):
    for i in range(0, len(array) - 1):
        flag = False
        for j in range(0, (len(array) - 1 - i)):
            if array[j] > array[j + 1]:
                array[j + 1], array[j] = array[j], array[j + 1]
                flag = True
        if not flag:
            break
    return array


class bubble(ParentClass.SortMethods):
    pass
