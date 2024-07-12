#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "pc-power-metrics.h"

int main() {
    if (check_powercap_dir() < 0) {
        fprintf(stderr, "This computer must support Intel RAPL and have a powercap sysfs!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int check_powercap_dir() {
    fprintf(stderr, "Checking for %s ... ", POWERCAP_DIR);

    DIR *powercap_dir = opendir(POWERCAP_DIR);

    if (powercap_dir != NULL) {
        fprintf(stderr, "Found\n");
        closedir(powercap_dir);
        return 0;
    }

    fprintf(stderr, "Failed\n");

    if (errno != ENOENT) {
        fprintf(stderr, "Fatal error: %s\n", strerror(errno));
        return -2;
    }

    return -1;
}
