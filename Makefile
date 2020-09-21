CFLAGS = -I.

CC	= gcc

arp_test.o:	test/arp_test.c
			gcc -I ./ test/arp_test.c *.c