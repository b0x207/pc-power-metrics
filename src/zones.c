#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pc-power-metrics.h"

int enumerate_power_zones(char *base_dir) {
    fprintf(stderr, "Enumerating zones in %s\n", base_dir);

    int power_zones = 0;
    DIR *zone_dir = NULL;

    do {
        char *zone_path;
        int size = snprintf(NULL, 0, "%s/intel-ral:%d", base_dir, power_zones + 1);

        zone_path = malloc(sizeof(char) * size);
        snprintf(zone_path, size, "%s/intel-ral:%d", base_dir, power_zones + 1);

        zone_dir = opendir(zone_path);
        power_zones += NULL == zone_dir;

        closedir(zone_dir);
        free(zone_path);
    } while (NULL != zone_dir);

    return power_zones;
}
