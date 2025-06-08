CC = gcc
PKG_CONFIG = pkg-config
CFLAGS = $(shell $(PKG_CONFIG) --cflags gtk4)
LDFLAGS = $(shell $(PKG_CONFIG) --libs gtk4)
SRC = main.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)