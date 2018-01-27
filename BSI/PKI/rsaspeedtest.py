import os
import subprocess
import tempfile

from collections import namedtuple
from itertools import cycle
from pathlib import Path
from timeit import timeit


urand = '/dev/urandom'
pwd = 'asdf'
File = namedtuple('File', 'sz_bytes path size_rel unit')
Key = namedtuple('Key', 'path size algo')
Result = namedtuple('Result', 'algo fsize time time_per_mb')


multipler = {
        'B': 1,
        'KB': 1000,
        'MB': 1000000
        }


def make_files(tmpdir, *sizes):
    ret = []
    for size, unit in sizes:
        name = f'{size}{unit or "B"}'
        path = Path(tmpdir, name)
        tmpunit = '' if unit == 'B' else unit
        cmd = f'dd if={urand} of={path} bs=1{tmpunit} count={size}'
        subprocess.check_call(cmd, shell=True, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)
        f = File(
                sz_bytes=size*multipler[unit],
                path=path,
                size_rel=size,
                unit=unit
                )
        ret.append(f)
    return ret


def make_keys(tmpdir, keys, sizes):
    ret = []
    for k in keys:
        keyarg = f'-{k}' if k != 'rsa' else ''
        for sz in sizes:
            ofile = Path(tmpdir, f'{k}{sz}.key')
            cmd = f'openssl genrsa {keyarg} -passout pass:{pwd} -out {ofile} {sz}'
            subprocess.check_call(cmd, shell=True, stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
            key = Key(size=sz, algo=k, path=ofile)
            ret.append(key)
    return ret


def profile_algos(tmpdir, files, keys):
    for key, file in zip(keys, cycle(files)):
        assert os.path.isfile(key.path)
        assert os.path.isfile(file.path)
        encfile = f'{tmpdir}/encrypted'
        decfile = f'{tmpdir}/decrypted'
        enccmd = (f'openssl rsautl -passin pass:{pwd} '
                  f'-in {file.path} -out {encfile} -inkey {key.path} -encrypt')
        deccmd = (f'openssl rsautl -passin pass:{pwd} '
                  f'-in {encfile} -out {decfile} -inkey {key.path} -decrypt')
        enccmd = f'subprocess.check_output("{enccmd}")'
        deccmd = f'subprocess.check_output("{deccmd}")'
        print(enccmd)
        print(deccmd)
        enctime = timeit(stmt=enccmd, setup='import subprocess')
        assert os.path.isfile(decfile)
        dectime = timeit(stmt=deccmd, setup='import subprocess')
        assert os.path.isfile(decfile)

        print(enctime)
        print(dectime)




with tempfile.TemporaryDirectory() as tmpdir:
    files = make_files(tmpdir, (16, 'B'), (100, 'KB'), (5, 'MB'))
    algos = 'rsa aes128 des3'.split()
    szs = '1024 2048 4096'.split()
    keyfiles = make_keys(tmpdir, algos, szs)
    profiles = profile_algos(tmpdir, files, keyfiles)
