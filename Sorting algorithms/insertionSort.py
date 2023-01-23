import ParentClass


def sort(array):
    for i in range(1, len(array)):
        key = array[i]
        hole = i
        while hole > 0 and array[hole - 1] > key:
            array[hole] = array[hole - 1]
            hole = hole - 1
        array[hole] = key
    return array


class insert(ParentClass.SortMethods):
    pass
