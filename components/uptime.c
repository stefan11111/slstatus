/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "../slstatus.h"
#include "../util.h"

#if defined(CLOCK_BOOTTIME)
	#define UPTIME_FLAG CLOCK_BOOTTIME
#elif defined(CLOCK_UPTIME)
	#define UPTIME_FLAG CLOCK_UPTIME
#else
	#define UPTIME_FLAG CLOCK_MONOTONIC
#endif

const char *
uptime(const char *unused)
{
	char warn_buf[256];
	uintmax_t w, d, h, m;
	struct timespec uptime;

	if (clock_gettime(UPTIME_FLAG, &uptime) < 0) {
		snprintf(warn_buf, 256, "clock_gettime %d", UPTIME_FLAG);
		warn(warn_buf);
		return NULL;
	}
	w = uptime.tv_sec / 604800;
	d = uptime.tv_sec / 86400 % 7;
	h = uptime.tv_sec / 3600 % 24;
	m = uptime.tv_sec % 3600 / 60;
	if(w==0&&d==0)
		return bprintf("%juh %jum", h, m);
	if(w==0)
		return bprintf("%jud %juh %jum", d, h, m);
	return bprintf("%juw %jud %juh %jum", w, d, h, m);
}
