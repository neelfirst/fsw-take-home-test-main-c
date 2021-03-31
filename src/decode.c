#include <fstream>
#include <iostream>

START0 = b'21'
START1 = b'22'
HEADER = [START0, START1]

def get_length(packet):
def ingest(file):
def get_packets(hexlist):
def valid(packet):
def set_format(packet):

int main (int argc, char **argv)
{
  parser = argparse.ArgumentParser("Process sample serial data, stored in binary hex format.")
  parser.add_argument("--input", type=str)
  parser.add_argument("--output", type=str)
  args = parser.parse_args()

  # convert input file to array of hex bytes
  hex_in = ingest(args.input)

  # get all packets as array of arrays
  packets = get_packets(hex_in)

  # validate all packets, print if validated
  with open(args.output,'w') as f:
    for packet in packets:
      if valid(packet):
        f.write(set_format(packet))
  return 0;
}
