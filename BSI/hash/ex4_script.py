import sys
import os
from hashlib import sha256
from itertools import permutations
import string
import random

SZ = 4


def small_hash(bytes_):
    return sha256(bytes_).digest()[:SZ]


or_string = b'siema'
length = len(or_string)
or_hash = small_hash(or_string)

counts = []


def get_avg_reverse_time():
    for i in range(10):
        count = 0
        or_string = ''.join([random.choice(string.ascii_lowercase) for _ in range(length)]).encode('ascii')
        or_hash = small_hash(or_string)
        perms = permutations(string.ascii_lowercase, length)
        for perm in perms:
            count += 1
            perm = ''.join(perm).encode('ascii')
            if small_hash(perm) == or_hash:
                counts.append(count)
                break
    avg = sum(counts)/len(counts)
    return avg


def get_avg_collision_time_for_random_bytes_sequence():
    counts = []
    for i in range(10):
        count = 0
        original = os.urandom(5)
        original_hash = small_hash(original)
        while True:
            count += 1
            random_bytes = os.urandom(30)
            random_hash = small_hash(random_bytes)
            if original_hash == random_hash:
                counts.append(count)
                break
    avg = sum(counts)/len(counts)
    return avg


rnd_string_avg = get_avg_reverse_time()
print('Random {} ascii lowercase letter avg reverse time: '.format(length), rnd_string_avg)
print('Random bytes avg collision time: ', get_avg_collision_time_for_random_bytes_sequence())
