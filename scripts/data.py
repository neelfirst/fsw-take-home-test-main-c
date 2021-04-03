#!/usr/bin/env python3
'''
This guy just checks an output file for consistency.
'''

import argparse

parser = argparse.ArgumentParser("Validate output data.")
parser.add_argument("--file", type=str)
args = parser.parse_args()

with open(args.file,'r') as f:
  lines = f.readlines()
  for line in lines:
    length = int(line[1:4])
    spaces = line[3:].count(' ')
    if (spaces != length):
      print (line, spaces, length)
