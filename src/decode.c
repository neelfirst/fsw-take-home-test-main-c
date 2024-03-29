#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const unsigned char START0 = 0x21;
const unsigned char START1 = 0x22;

bool valid (FILE *stream, const unsigned char packet[], const unsigned int length)
{
  /* Apparently I suck at reading instructions. We can have extra data between valid packets.
     And I don't need to discard too long packets, just the extra data, which the main loop
     can handle.
  char peek0 = fgetc(stream);
  char peek1 = fgetc(stream);
  if (peek1 != EOF) ungetc(peek1, stream);
  if (peek0 != EOF) ungetc(peek0, stream);

  if (peek0 == START0 && peek1 == START1) return true;
  else if (peek0 == EOF || peek1 == EOF) return true; */

//  else { // now we need to check if our packet is too short,
         // e.g. there is another start header within this packet
    for (int i = 0; i < length; i++) {
      if (packet[i] == START0 && packet[i] == START1) {
        fseek(stream, i-(length+1), SEEK_CUR); // reset cursor, maybe the next one is good
        return false;
      }
    }
    return true;
//  }
}

int main (int argc, char **argv)
{
  if (argc != 5 || strcmp(argv[1],"--input") != 0 || strcmp(argv[3],"--output") != 0) {
    printf("Usage: decode --input <input_file> --output <output_file>\n");
    exit(1);
  }
  // too tired to protect these rn
  FILE *infile = fopen(argv[2],"rb");
  FILE *outfile = fopen(argv[4],"w");

  unsigned char byte[1];
  bool seekHeader = false;
  bool gotHeader = false;

  // Reading one byte at a time incurs I/O overhead, but it seems the
  // problem is geared to simulate real-time byte retrieval and analysis,
  // so this loop would most likely run bytewise in a serial callback.
  while (fread(byte,sizeof(char),1,infile) == 1)
  {
    if (gotHeader) {
      gotHeader = false;
      unsigned int length = (unsigned int)(byte[0]);
      unsigned char packet[length];
      bool read_success = false;
      /* Well I learned something new today. fread doesn't return bytes_read
         anymore, it just returns 1 for a success. gcc 9.3 on WSL U20. */
      if (fread(packet, length, 1, infile) != 1) {
        /* apparently you can haz zero length valid packets. sneaky. */
        if (length == 0) read_success = true;
        else read_success = false;
      }
      else read_success = true;

      if (read_success) {
        if (valid(infile, packet, length)) {
          fprintf(outfile, "{%3d}", length);
          for (int i=0; i<length; i++) fprintf(outfile, " %02X", packet[i]);
          fprintf(outfile, "\n");
        }
      }
    }
    // header detection logic
    if (seekHeader && byte[0] == START1) gotHeader = true;
    else gotHeader = false;

    if (byte[0] == START0) seekHeader = true;
    else seekHeader = false;
  }
  return 0;
}
