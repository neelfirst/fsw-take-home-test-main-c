#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const unsigned char START0 = 0x21;
const unsigned char START1 = 0x22;

int main (int argc, char **argv)
{
  if (argc != 5 || strcmp(argv[1],"--input") != 0 || strcmp(argv[3],"--output") != 0) {
    printf("Usage: decode --input <input_file> --output <output_file>\n");
    exit(1);
  }

  FILE *infile = fopen(argv[2],"rb");
  FILE *outfile = fopen(argv[4],"w");
  unsigned char byte[1];

  // The only reason to write in C is for performance, so let's
  // dispense with the niceties and write a single loop.

  bool seekHeader = false;
  bool gotHeader = false;

  // Rreading one byte at a time incurs I/O overhead, but it seems the
  // problem is geared to simulate real-time byte retrieval and analysis,
  // so this loop would most likely run bytewise in a serial callback.

  while (fread(byte,sizeof(char),1,infile) == 1)
  {
    if (gotHeader) {
      gotHeader = false;
      unsigned int length = (unsigned int)(byte[0]);
      unsigned char packet[length];
      if (fread(packet, length, 1, infile) == length) {
        printf("eof or packet read error");
        break;
      }
      else {
        fprintf(outfile, "{ %03u } ", length);
        for (int i=0; i<length; i++) fprintf(outfile, "%02X ", packet[i]);
        fprintf(outfile, "\n");
      }
    }

    if (seekHeader && byte[0] == START1) {
      gotHeader = true;
      printf("got header\n");
    }
    else gotHeader = false;

    if (byte[0] == START0) {
      seekHeader = true;
      printf("got start0, now seeking header\n");
    }
    else seekHeader = false;
  }


  // convert input file to array of hex bytes
  // unsigned char *hex_in = ingest(infile)

/*
  # get all packets as array of arrays
  packets = get_packets(hex_in)

  # validate all packets, print if validated
  with open(args.output,'w') as f:
    for packet in packets:
      if valid(packet):
        f.write(set_format(packet))
*/
  return 0;
}

