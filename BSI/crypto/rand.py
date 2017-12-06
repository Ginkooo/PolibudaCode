import subprocess
import binascii
from argparse import ArgumentParser


ap = ArgumentParser(description='Encrypt file using system entrophy')
ap.add_argument('algorithm', help='Algorithm to use (For full list of ciphertypes please see: man enc')
ap.add_argument('input_file', help='File to cipher')
ap.add_argument('output_file', help='Output file')

args = ap.parse_args()

rand_key = open('/dev/urandom', 'rb').read(14)
rand_iv = open('/dev/urandom', 'rb').read(14)
rand_key = binascii.hexlify(rand_key).decode('ascii')
rand_iv = binascii.hexlify(rand_iv).decode('ascii')


algo = args.algorithm
ifile = args.input_file
ofile = args.output_file

cmd = 'openssl enc -{} -e -in {} -out {} -K {} -iv {}'.format(algo, ifile, ofile, rand_key, rand_iv)

print(cmd)
subprocess.check_call(cmd, shell=True)
print('File enciphered with key:')
print(rand_key)
print('iv was:')
print(rand_iv)
