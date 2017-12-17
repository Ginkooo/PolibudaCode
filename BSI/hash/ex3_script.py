import hashlib
import os
def change_bit(bytess):
    ret = [bytess[0] ^ 1]
    ret.extend(bytess[1:])
    return bytes(ret)
def padding_bin(x):
    str = bin(x)[2:]
    i = len(str) % 8
    str = ('0' * i) + str
    return str
data = os.urandom(100)
o_md5 = hashlib.md5(data).digest()
o_sha = hashlib.sha256(data).digest()
n_data = change_bit(data)
n_sha = hashlib.sha256(n_data).digest()
n_md5 = hashlib.md5(n_data).digest()
o_md5 = ''.join([padding_bin(x) for x in o_md5])
o_sha = ''.join([padding_bin(x) for x in o_sha])
n_sha = ''.join([padding_bin(x) for x in n_sha])
n_md5 = ''.join([padding_bin(x) for x in n_md5])
matches = 0
for a, b in zip(o_md5, n_md5):
    if a == b:
        matches += 1
print('Zgadzających się bitów w md5 jest {} co stanowi {}%'.format(matches, matches/len(o_md5) * 100))
matches = 0
for a, b in zip(o_sha, n_sha):
    if a == b:
        matches += 1
print('Zgadzających się bitów w sha jest {} co stanowi {}%'.format(matches, matches/len(o_sha) * 100))
