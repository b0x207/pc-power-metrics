#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define POWERCAP_DIR "/sys/devices/virtual/powercap"

int check_powercap_dir() {
    printf("Checking for %s ...\n", POWERCAP_DIR);

    DIR *powercap_dir = opendir(POWERCAP_DIR);

    if (powercap_dir == NULL && errno != ENOENT) {
        fprintf(stderr, "Fatal error: %s\n", strerror(errno));
        return -2;
    }

    return 0;
}

int main() {
    if (check_powercap_dir() < 0) {
        fprintf(stderr, "The device must support Intel RAPL and have a powercap sysfs!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
