#!/bin/sh

# Arduino-IDE-and-Ino-Side-by-sidy Helper Script
# Version: 0.1
# Author: Tim Pulver
# Ino URL: http://inotool.org
#
# Compile and upload Arduino sketches using Ino 
# without moving them to a "scr"-folder, so you can still edit 
# the sketch in Arduino IDE.
# This will create a hidden temp directory and copy all files in there
# Make sure Ino-is up to date!
# Copy this script to the same directory where your 
# Arduino-ino-file and ino.ini files are.
# Usage:
# 1) Make the script executabele (once): chmod +x upload.sh
# 2) Now you can run it: ./upload.sh

rm -r .tmp_build
mkdir .tmp_build
mkdir .tmp_build/src
# copy all h-, cpp- and ino-files to mkdir .tmp_build/src
# if you are using additional .h-files, uncomment this
#cp *.h .tmp_build/src
# if you are using additional .cpp-files, uncomment this
#cp *.cpp .tmp_build/src
cp *.ino .tmp_build/src
cp ino.ini .tmp_build
cd .tmp_build/
ino build
ino upload
