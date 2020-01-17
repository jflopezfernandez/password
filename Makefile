 # password v1.0.0 Cryptographically-secure password utility
 # Copyright (C) 2020 Jose Fernando Lopez Fernandez
 # 
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 # 
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 # 
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <https://www.gnu.org/licenses/>.

vpath %.c src

MKDIR    := mkdir -p
RM       := rm -f

OBJS     := $(patsubst %.c,%.o,$(notdir $(wildcard src/*.c)))

CC       := gcc
CFLAGS   := -std=c17 -Wall -Wextra -Werror -Wpedantic -g -Og
CPPFLAGS := -I include -D_GNU_SOURCE -D_POSIX_SOURCE
LDFLAGS  := 
LIBS     := 

TARGET   := password

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

check: $(TARGET)
	$(MAKE) -C tests tests

.PHONY: clean
clean: clean-tests
	$(RM) $(OBJS) $(TARGET)

.PHONY: clean-tests
clean-tests:
	$(MAKE) -C tests clean
