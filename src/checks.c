#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "pc-power-metrics.h"

int check_powercap_dir() {
    fprintf(stderr, "Checking for %s ... ", POWERCAP_DIR);

    DIR *powercap_dir = opendir(POWERCAP_DIR);

    if (NULL != powercap_dir) {
        fprintf(stderr, "Found\n");
        closedir(powercap_dir);
        return 0;
    }

    fprintf(stderr, "Failed\n");

    if (ENOENT != errno) {
        fprintf(stderr, "Fatal error: %s\n", strerror(errno));
        return -2;
    }

    return -1;
}

int check_rapl_enabled() {
    fprintf(stderr, "Checking if RAPl is enabled ... ");

    FILE *file = fopen(POWERCAP_DIR "/enabled", "r");

    if (NULL == file) {
        fclose(file);
        fprintf(stderr, "Inconclusive\nFatal error: %s\n", strerror(errno));
        return -2;
    }
    
    char value;
    if (fread(&value, 1, 1, file) < 0) {
        fclose(file);
        fprintf(stderr, "Inconclusive\nFatal error while reading: %s\n", strerror(errno));
        return -2;
    }

    fclose(file);

    if ('0' > value || '1' < value) {
        fprintf(
            stderr,
            "Inconclusive\nInvalid value read from %s: 0x%x\n",
            POWERCAP_DIR "/enabled",
            value
        );
        return -2;
    }

    if ('0' == value) {
        fprintf(stderr, "No\n");
        return -1;
    }

    fprintf(stderr, "Yes\n");

    return 0;
}
