#!/usr/bin/env python3
"""Set up OLM cache dirs for unit tests"""

import sys
from pathlib import Path
from os import listdir, remove, geteuid
from common import FREAD_CACHE_DIR, FWRITE_CACHE_DIR, FREAD_FILE, FREAD_FILE2,\
        FCACHES_FREAD_VALID_FILES, FCACHES_FREAD_INVALID_FILES,\
        FCACHES_FREAD_EMPTY_FILE

if geteuid() != 0:
    print("Run as root")
    sys.exit(1)

# make cache dirs
Path(FREAD_CACHE_DIR).mkdir(parents=True, exist_ok=True)
Path(FWRITE_CACHE_DIR).mkdir(parents=True, exist_ok=True)

# clean cache dirs
for f in listdir(FREAD_CACHE_DIR):
    remove(FREAD_CACHE_DIR + f)
for f in listdir(FWRITE_CACHE_DIR):
    remove(FWRITE_CACHE_DIR + f)

# make short fread test file
with open(FREAD_CACHE_DIR + FREAD_FILE, "w") as fptr:
    fptr.write("This is a test. ")

# make fread test file for block SDO transfer testing
with open(FREAD_CACHE_DIR + FREAD_FILE2, "w") as fptr:
    fptr.write("This is a test. " * 100)

# make files for file caches tests
for f in FCACHES_FREAD_VALID_FILES:
    with open(FREAD_CACHE_DIR + f, "w") as fptr:
        fptr.write("This is a test. ")
for f in FCACHES_FREAD_INVALID_FILES:
    with open(FREAD_CACHE_DIR + f, "w") as fptr:
        fptr.write("This is a test. ")

# make empty file for file caches tests
Path(FREAD_CACHE_DIR + FCACHES_FREAD_EMPTY_FILE).touch()

print("Now start the oresat-linux-manager and then pytest")
