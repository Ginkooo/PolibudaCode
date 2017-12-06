import sys
import subprocess
types = ['md5', 'sha1', 'sha256']
keys = [4*'a', 16*'a', 32*'a']

fs = sys.argv[1:]

for fname in fs:
    for t in types:
        for k in keys:
            cmd = 'openssl dgst -{type} -hmac "{key}" {fname}'.format(type=t, key=k, fname=fname)
            output = subprocess.check_output(cmd, shell=True).decode()
            print(cmd)
            print(output)
            print()
    print()
