CFLAGS = -I.

CC	= gcc

arp_test:	
			gcc -o arp_test -I ./ test/arp_test.c *.c
clean:		
			rm arp_test