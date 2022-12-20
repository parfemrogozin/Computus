CC = gcc
CFLAGS = -std=gnu18 -pedantic -Wall -Wextra
LDLIBS = -lm
SRCS = $(wildcard *.c)
EXECUTABLE = computus

ifeq ($(PREFIX),)
	PREFIX := $$HOME
endif

all: CFLAGS += -Og -ggdb
all: $(SRCS)
	$(CC) -o $(EXECUTABLE) $(CFLAGS) $(LDLIBS) $^

release: CFLAGS += -march=native -Oz -s
release: $(SRCS)
	$(CC) -o $(EXECUTABLE) $(CFLAGS) $(LDLIBS) $^

clean:
	rm -f $(EXECUTABLE)

install:
	install -d $(PREFIX)/.local/bin
	install $(EXECUTABLE) $(PREFIX)/.local/bin

uninstall:
	$(RM) $(PREFIX)/.local/bin/$(EXECUTABLE)
