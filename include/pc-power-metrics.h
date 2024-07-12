#ifndef _PC_POWER_METRICS_H_
#define _PC_POWER_METRICS_H_

#include <stdint.h>

#define POWERCAP_DIR "/sys/devices/virtual/powercap/intel-rapl"

typedef struct reading_result_t {
    uint64_t value;
    uint8_t is_error;
} reading_result_t;

int check_powercap_dir();
int check_rapl_enabled();
int enumerate_power_zones(char *base_dir);
reading_result_t take_reading(char *zone_path);

#endif
