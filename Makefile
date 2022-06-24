# Copyright (c) 2022 2bllw8
# SPDX-License-Identifier: GPL-3.0-only

CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = permscalc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

permscalc: permscalc.o main.o
	$(CC) -o $@ $^ $(CFLAGS)

test: permscalc.o test.o
	$(CC) -o $@ $^ $(CFLAGS)
	./$@

clean:
	rm -f *.o permscalc test

.DEFAULT_GOAL :=  permscalc
