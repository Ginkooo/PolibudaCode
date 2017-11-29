import sys
from time import process_time
from timeit import timeit
import csv

types = ['md5', 'sha1', 'sha256', 'md4']


fs = sys.argv[1:]
files = []
for a in fs:
  files.append(a.split(','))

for fname, size in files:
  size = int(size)
  for t in types:
    times = []
    cmd = 'openssl dgst -{} {}'.format(t, fname)
    avg = timeit(stmt='subprocess.check_output("{cmd}", shell=True)'.format(cmd=cmd), number=10, timer=process_time, setup='import subprocess');
    print(avg)
    mbsz = size / 1000000
    print('Rozmiar pliku w mb: ', end='')
    print(mbsz)
    print('Funkcja: ' + t)
    avg_mb = avg / mbsz
    print('Czas obliczania na megabajt: ' + str(avg_mb) + ' ms')
