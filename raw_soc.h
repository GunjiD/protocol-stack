#ifndef RAW_SOC_H
#define RAW_SOC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <errno.h>

#include "ethernet.h"
#include "ip.h"
#include "inet.h"
#include "arp.h"

#define BUF_SIZ 65535

int create_socket(char *interface_name);

#endif