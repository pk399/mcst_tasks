import random

def algo(arr):
    max_seq = []
    cur_seq = []
    prev_n = 0

    for el in arr:
        if prev_n >= el:
            if sum(cur_seq) > sum(max_seq):
                max_seq = cur_seq.copy()
            cur_seq = []
        cur_seq.append(el)
        prev_n = el

    return max_seq

arr = [random.randint(1, 10) for _ in range(1, 100000)]

#print(arr)
print(algo(arr))
