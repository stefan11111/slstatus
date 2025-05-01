/* See LICENSE file for copyright and license details. */
#include <limits.h>
#include <stdio.h>

#include "../util.h"

#include <stdint.h>

	#define NET_RX_BYTES "/sys/class/net/%s/statistics/rx_bytes"
	#define NET_TX_BYTES "/sys/class/net/%s/statistics/tx_bytes"

	const char *
	netspeed_rx(const char **interfaces)
	{
		uintmax_t oldrxbytes;
		static uintmax_t rxbytes;
		uintmax_t tmp = 0;
		char path[PATH_MAX];

		oldrxbytes = rxbytes;
		rxbytes = 0;
		for(; *interfaces; interfaces++) {
			if (esnprintf(path, sizeof(path), NET_RX_BYTES, *interfaces) < 0)
				return NULL;
			if (pscanf(path, "%ju", &tmp) != 1)
				tmp = 0;
			rxbytes += tmp;
		}
		if (oldrxbytes == 0)
			return NULL;
		if (rxbytes == 0)
			return NULL;
		return fmt_human((rxbytes-oldrxbytes), 1024);
	}

	const char *
	netspeed_tx(const char **interfaces)
	{
		uintmax_t oldtxbytes;
		static uintmax_t txbytes;
		uintmax_t tmp;
		char path[PATH_MAX];

		oldtxbytes = txbytes;
		txbytes = 0;

		for(; *interfaces; interfaces++) {
			if (esnprintf(path, sizeof(path), NET_TX_BYTES, *interfaces) < 0)
				return NULL;
			if (pscanf(path, "%ju", &tmp) != 1)
				tmp = 0;
			txbytes += tmp;
		}
		if (oldtxbytes == 0)
			return NULL;
		if (txbytes == 0)
			return NULL;
		return fmt_human((txbytes-oldtxbytes),  1024);
	}
