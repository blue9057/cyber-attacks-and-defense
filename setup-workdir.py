#!/usr/bin/env python3

import glob
import os

def main():
    g = glob.glob('/home/labs/week*/challenges/*')
    for _dir in g:
        if os.path.isdir(_dir):
            symlink_path = f"{_dir}/workdir"
            os.symlink("/home/labs/workdir", symlink_path)

    g = glob.glob('/home/labs/week*/**/Makefile', recursive=True)
    for _makefile in g:
        os.unlink(_makefile)

if __name__ == '__main__':
    main()
