
vpath %.c src

MKDIR    := mkdir -p
RM       := rm -f

CC       :=  gcc
CFLAGS   := -std=c17 -Wall -Wextra -Werror -Wpedantic -g -Og
CPPFLAGS := -I ../include -I include -D_GNU_SOURCE -D_POSIX_SOURCE
LDFLAGS  := 
LIBS     := -lcunit

TESTS := test-cmdline-args-length

all: tests

tests: $(TESTS)
	./test-cmdline-args-length

test-cmdline-args-length: test-cmdline-args-length.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$(RM) $(wildcard *.o) $(TESTS)
