import subprocess
import tempfile

from collections import namedtuple
from pathlib import Path
from timeit import timeit


urand = '/dev/urandom'
pwd = 'asdf'
File = namedtuple('File', 'sz_bytes path size_rel unit')
Key = namedtuple('Key', 'path size algo')
Result = namedtuple('Result', 'key_size algo fsize dectime enctime dectime_per_mb enctime_per_mb error')


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
    ret = []
    for key in keys:
        for file in files:
            encfile = f'{tmpdir}/encrypted'
            decfile = f'{tmpdir}/decrypted'
            enccmd = (f'openssl rsautl -passin pass:{pwd} '
                      f'-in {file.path} -out {encfile} -inkey {key.path} -encrypt')
            deccmd = (f'openssl rsautl -passin pass:{pwd} '
                      f'-in {encfile} -out {decfile} -inkey {key.path} -decrypt')
            enccmd = f'subprocess.check_output("{enccmd}", shell=True, stderr=subprocess.PIPE)'
            deccmd = f'subprocess.check_output("{deccmd}", shell=True, stderr=subprocess.PIPE)'
            error = False
            try:
                enctime = timeit(stmt=enccmd, setup='import subprocess', number=100)
                dectime = timeit(stmt=deccmd, setup='import subprocess', number=100)
            except:
                error = True

            result = Result(
                    algo=key.algo,
                    key_size=key.size,
                    fsize=f'{file.size_rel}{file.unit}',
                    enctime=enctime,
                    dectime=dectime,
                    enctime_per_mb=enctime/10**6,
                    dectime_per_mb=dectime/10**6,
                    error=error)
            ret.append(result)
    return ret


with tempfile.TemporaryDirectory() as tmpdir:
    files = make_files(tmpdir, (16, 'B'), (100, 'KB'), (5, 'MB'))
    algos = 'rsa aes128 des3'.split()
    szs = '1024 2048 4096'.split()
    keyfiles = make_keys(tmpdir, algos, szs)
    profiles = profile_algos(tmpdir, files, keyfiles)
    for profile in profiles:
        if profile.error:
            continue
        nl = '\n'
        print(f'Size: {profile.fsize}{nl}'
              f'Key size: {profile.key_size}{nl}'
              f'Algorithm: {profile.algo}{nl}'
              f'Decryption time per MB: {profile.dectime_per_mb}{nl}'
              f'Encryption time per MB: {profile.enctime_per_mb}')
        print()
