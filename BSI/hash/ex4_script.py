import sys
import os
from hashlib import sha256
from itertools import permutations
import string

SZ =4

def small_hash(bytes_):
    return sha256(bytes_).digest()[:SZ]

or_string = b'siemaneczko'
length = len(or_string)
or_hash = small_hash(or_string)

counts = []

for i in range(10):
    count = 0
    perms = permutations(string.ascii_lowercase)
    for perm in perms:
        perm = perm
        if small_hash(perm) == or_hash:
            counts.append(count)
            break

avg = sum(counts)/len(counts)

print(avg)
