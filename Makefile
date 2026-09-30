CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -pipe -I. -Ifil
INCLUDES = $(addprefix -I,$(shell find . -type d -not -path './.git*'))

export TMPDIR := /tmp
export TEMP := /tmp
export TMP := /tmp

TARGET = program.exe

SOURCES = $(shell find . -name '*.c' \
    -not -path './generated_example/*' \
    -not -path './png_samples/*')

OBJECTS = $(patsubst ./%.c,build/%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: clean