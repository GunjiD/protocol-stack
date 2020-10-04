CFLAGS = -I.

CC	= gcc

arp_test:	
			gcc -o arp_test -I ./ test/arp_test.c *.c
packet_capture:
			gcc -o packet_capture -I ./ test/packet_capture.c *.c
clean:		
			rm -f arp_test packet_capture