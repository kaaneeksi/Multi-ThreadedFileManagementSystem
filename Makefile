CC = gcc
CFLAGS = -pthread -o
TARGET = project
SRCS = main.c file_operations.c threads.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
