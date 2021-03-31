CC=gcc
TARGET=decode

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^
