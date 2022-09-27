#CPSC1020 FALL2021
#PROGRAMMING ASSIGNMENT #1 (PA1)
#Skylar Hubbarth
#Last revised: 10/10/2021
#Cathy Kittelstad
#This program as a whole is designed to take images and manipulate them,
#based on the user's choice, to be either grayscaled, mirrored, green screened,
#or any combination of the three.

#*makefile*
#stores information for compiling and running the program


# Config, just variables
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out

# Generate source and object lists, also just string variables
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard src/**/*.c)
HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
	$(wildcard src/**/*.h)
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))
#default target
all: build
	@echo "All Done!"

#Link all built objects
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

#special build rule
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"

# Catch root directory src files
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Catch all nested directory files
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf bin

run: build
	./$(TARGET) ClemsonPaw.ppm Disney.ppm
