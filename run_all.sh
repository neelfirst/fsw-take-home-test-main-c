#!/bin/bash -e

cd src && make clean && make

cd ..

src/decode --input data/2_packets --output data/2_packets.cc
src/decode --input data/10_short_packets --output data/10_short_packets.cc
src/decode --input data/200_packets --output data/200_packets.cc
src/decode --input data/extra_data --output data/extra_data.cc

python3 scripts/decode_out.py --input data/2_packets --output data/2_packets.outpy
python3 scripts/decode_out.py --input data/10_short_packets --output data/10_short_packets.outpy
python3 scripts/decode_out.py --input data/200_packets --output data/200_packets.outpy
python3 scripts/decode_out.py --input data/extra_data --output data/extra_data.outpy

python3 scripts/data.py --file data/2_packets.cc
python3 scripts/data.py --file data/10_short_packets.cc
python3 scripts/data.py --file data/200_packets.cc
python3 scripts/data.py --file data/extra_data.cc

diff data/2_packets.cc data/2_packets.outpy
diff data/10_short_packets.cc data/10_short_packets.outpy
diff data/200_packets.cc data/200_packets.outpy

# this last check is pointless due to my rtfm issues.
# diff data/extra_data.cc data/extra_data.outpy
