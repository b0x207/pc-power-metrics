#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include "pc-power-metrics.h"

sample_result_t sample(char *zone_path) {
    sample_result_t result = {
        .value = 0,
        .is_error = 0
    };

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    // We sample 3 values for a more accurate average
    reading_result_t res1 = take_reading(zone_path);
    sleep(1);

    reading_result_t res2 = take_reading(zone_path);
    sleep(1);

    reading_result_t res3 = take_reading(zone_path);
    sleep(1);

    clock_gettime(CLOCK_REALTIME, &end);

    if (res1.is_error || res2.is_error || res3.is_error) {
        result.is_error = 1;
        return result;
    }

    double tdiff = ((double) end.tv_nsec - start.tv_nsec) / 1E9;
    tdiff += (double) (end.tv_sec - start.tv_sec);

    printf("%ld %ld %ld\n", res1.value, res2.value, res3.value);
    double energy_diff1 = ((double) res2.value - res1.value) / 1E6;
    double energy_diff2 = ((double) res3.value - res2.value) / 1E6;
    double energy_avg = (energy_diff1 + energy_diff2) / 2;
    result.value = energy_avg / tdiff;

    printf("Time diff: %f\n", tdiff);
    printf("Energy diffs: %f %f\n", energy_diff1, energy_diff2);
    printf("Joules: %f\n", energy_avg);

    return result;
}

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

    fscanf(energy_file, "%ld", &result.value);

    if (ferror(energy_file)) {
        fclose(energy_file);
        fprintf(stderr, "Failed to read value: %s\n", strerror(errno));
        result.is_error = 1;
        return result;
    }

    fclose(energy_file);

    return result;
}
