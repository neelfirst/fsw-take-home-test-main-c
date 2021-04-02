CC=gcc
CFLAGS=-Wall -O2 -g
TARGET=decode

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^

clean:
	rm $(TARGET).o $(TARGET)
