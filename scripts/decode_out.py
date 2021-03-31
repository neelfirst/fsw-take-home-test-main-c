#!/usr/bin/env python3
'''
This inefficient python script serves as a sanity check
that we're correctly ingesting and processing files.
'''

import binascii
import argparse

START0 = b'21'
START1 = b'22'
HEADER = [START0, START1]

def ingest(file):
  with open(file,'rb') as f:
    x = []
    while (byte := binascii.hexlify(f.read(1))):
      x.append(byte)
    return x

def get_packets(hexlist):
  '''
  According to the README, any 0x00-0xFF byte is a valid data byte.
  Therefore if we observe either start byte without its pair, we must
  assume that it is part of the data payload.
  Edge case: If it is a broken header, we expect the length check of
  the preceding packet to fail, losing two packets in sum.
  '''
  indices = []
  packets = []
  # TODO: switch to while when converting to C
  for i in range(len(hexlist)):
    if hexlist[i] == HEADER[0] and hexlist[i:i+len(HEADER)] == HEADER:
      indices.append(i)
  for i in range(len(indices)):
    start = indices[i]

    # sometimes, there just isn't a better solution. OR IS THERE
    if i+1 == len(indices):
      end = len(indices)
    else:
      end = indices[i+1]

    packets.append(hexlist[start:end])
  return packets

if __name__ == "__main__":
  parser = argparse.ArgumentParser("Process sample serial data, stored in binary hex format.")
  parser.add_argument("--input", type=str)
  parser.add_argument("--output", type=str)
  args = parser.parse_args()
  print(args)
  try:
    # convert input file to array of hex bytes
    hex_in = ingest(args.input)

    # get all packets as array of arrays
    packets = get_packets(hex_in)
    '''
    # validate all packets, print if validated
    with open(args.__output,'w') as f:
      for packet in packets:
        if valid(packet):
          f.write(set_format(packet))
    '''
#    print(hex_in)
    print(packets)
  except Exception as e:
    print(e)

