#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "pc-power-metrics.h"

reading_result_t take_reading(char *zone_path) {
    reading_result_t result = {
        .value = 0,
        .is_error = 0
    };
    FILE *energy_file = fopen(zone_path, "r");

    if (NULL == energy_file) {
        fprintf(stderr, "Failed to take a reading: %s\n", strerror(errno));
        result.is_error = 1;
        return result;
    }

    return result;
}
