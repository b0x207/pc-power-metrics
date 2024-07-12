#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "pc-power-metrics.h"

int main() {
    if (check_powercap_dir() < 0 || check_rapl_enabled() < 0) {
        fprintf(stderr, "This computer must support Intel RAPL and have a powercap sysfs!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
