/* See LICENSE file for copyright and license details. */

/* cpu */
const char *cpu_perc(const char *unused);

/* datetime */
const char *datetime(const char *fmt);

/* kernel_release */
const char *kernel_release(const char *unused);

/* netspeeds */
const char *netspeed_rx(const char *interface);
const char *netspeed_tx(const char *interface);

/* ram */
const char *ram_free(const char *unused);
const char *ram_perc(const char *unused);
const char *ram_total(const char *unused);
const char *ram_used(const char *unused);

/* uptime */
const char *uptime(const char *unused);
