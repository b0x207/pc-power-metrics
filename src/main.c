#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "pc-power-metrics.h"

int main() {
    if (check_powercap_dir() < 0 || check_rapl_enabled() < 0) {
        fprintf(stderr, "This computer must support Intel RAPL and have a powercap sysfs!\n");
        return EXIT_FAILURE;
    }

    int tl_power_zones = enumerate_power_zones(POWERCAP_DIR);

    if (-1 == tl_power_zones) {
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Found %d top-level RAPL power zones\n", tl_power_zones);

    for (int i = 0; i < tl_power_zones; i++) {
        char *zone_path;
        int size = snprintf(NULL, 0, "%s/intel-rapl:%d/energy_uj", POWERCAP_DIR, i) + 1;

        zone_path = malloc(sizeof(char) * size);
        snprintf(zone_path, size, "%s/intel-rapl:%d/energy_uj", POWERCAP_DIR, i);

        reading_result_t reading = take_reading(zone_path);

        if (1 == reading.is_error) {
            return EXIT_FAILURE;
        }

        printf("%ld\n", reading.value);
    }

    return EXIT_SUCCESS;
}
