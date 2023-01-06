/* See LICENSE file for copyright and license details. */
#include <stdio.h>

#include "../util.h"

#include <stdint.h>
	const char *
	ram_total(const char *unused)
	{
		uintmax_t total;

		if (pscanf("/proc/meminfo", "MemTotal: %ju kB\n", &total)
		    != 1)
			return NULL;

		return fmt_human(total * 1024, 1024);
	}

	const char *
	ram_used(const char *unused)
	{
		FILE *fp;
                if (!(fp = fopen("/proc/meminfo", "r"))) {
                        warn("fopen '/proc/meminfo':");
                        return NULL;
                }
                uintmax_t total,free,buffers,cached,slab,kernel;
                if(!fscanf(fp,"%*s %ju %*s",&total))
                        return NULL;
                if(!fscanf(fp,"%*s %ju %*s",&free))
                        return NULL;
                if(!fscanf(fp,"%*s %ju %*s",&buffers))
                        return NULL;
                if(!fscanf(fp,"%*s %ju %*s",&buffers))
                        return NULL;
                if(!fscanf(fp,"%*s %ju %*s",&cached))
                        return NULL;
                for(int i=1;i<=20;i++)
                        if(!fscanf(fp,"%*s %ju %*s",&slab))
                        return NULL;
                for(int i=1;i<=3;i++)
                        if(!fscanf(fp,"%*s %ju %*s",&kernel))
                        return NULL;
                fclose(fp);
                return fmt_human((total - free - buffers - cached - slab + kernel)*1024,1024);

	}
