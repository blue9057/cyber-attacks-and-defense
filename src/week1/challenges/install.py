#!/usr/bin/env python

import os
import shutil
import glob

WEEK = 'week1'
UID_START = 10000

def main():

    g = glob.glob("*/")

    dirs = sorted(list(g))

    print(dirs)

    lab_dir = "/home/labs/%s" % WEEK
    # create lab directory
    if not os.path.exists(lab_dir):
        os.system("sudo mkdir %s" % lab_dir)


    idx = 0
    for dir_name in dirs:

        _dir = dir_name.strip()[:-1]
        chal_dir = "%s/%s" % (lab_dir, _dir)
        username = "%s-%s-solved" % (WEEK, _dir)
        uid = UID_START + idx
        gid = UID_START + idx
        print("%s %d %d" % (username, uid, gid))

        # create user
        os.system("sudo addgroup --gid %d %s" % (gid, username))
        os.system("yes | sudo adduser --home %s --gid %d --uid %d %s --disabled-password --no-create-home" % (chal_dir, gid, uid, username))

        # make directory
        if not os.path.exists(chal_dir):
            os.system("sudo mkdir %s" % chal_dir)

        # copy required files
        os.system("sudo cp %s/%s %s/README %s/flag %s" % (_dir, _dir, _dir, _dir, chal_dir))


        # set permissions accordingly
        os.system("sudo chown -R %s:%s %s" % (username, username, chal_dir))
        os.system("sudo chmod 2755 %s/%s" % (chal_dir, _dir))
        os.system("sudo chmod 440 %s/flag" % (chal_dir))

        idx += 1

    for dir_name in dirs:
        os.system("cat %s/flag" % dir_name)



if __name__ == '__main__':
    main()
