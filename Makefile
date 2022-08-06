CC = gcc
CFLAGS = -std=gnu18 -pedantic -Wall -Wextra -march=native -Os -s
CFLAGS_DEBUG = -std=gnu18 -pedantic -Wall -Wextra -march=native -Os -g
LDLIBS = -lm
NAME = computus

ifeq ($(PREFIX),)
	PREFIX := $$HOME
endif

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

debug: $(NAME).c
	$(CC) $(CFLAGS_DEBUG) $(LDLIBS) -o $(NAME) $^

clean:
	rm -f $(NAME)

install:
	install -d $(PREFIX)/.local/bin
	install $(NAME) $(PREFIX)/.local/bin

uninstall:
	$(RM) $(PREFIX)/.local/bin/$(NAME)
