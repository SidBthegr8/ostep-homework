#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>

#define PAGESIZE 4096 // Typical page size

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_pages> <num_trials>\n", argv[0]);
        return 1;
    }

    // Set CPU affinity (pin process to CPU 0)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) != 0) {
        perror("sched_setaffinity failed");
        return 1;
    }

    int NUMPAGES = atoi(argv[1]);
    int NUMTRIALS = atoi(argv[2]);
    int jump = PAGESIZE / sizeof(int); // Step size to touch one integer per page
    int *ptr = malloc(NUMPAGES * jump * sizeof(int));
    //volatile int *a = malloc(NUMPAGES * jump * sizeof(int));
    volatile int *a = ptr;

    if (!a) {
        perror("Memory allocation failed");
        return 1;
    }

    struct timeval start, end;
    long total_time = 0;

    // Warm-up phase: ensure pages are allocated
    for (int i = 0; i < NUMPAGES * jump; i += jump) {
        a[i] = 0;
    }
    
    for (int trial = 0; trial < NUMTRIALS; trial++) {
        gettimeofday(&start, NULL);
	int sum=0;
        for (int i = 0; i < NUMPAGES * jump; i += jump) {
            //a[i] += 1; // Access one integer per page
	    sum+=a[i];
	    printf("Ignore: %d\n", sum);
        }

        gettimeofday(&end, NULL);
        long time_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        total_time += time_us;
    }

    double avg_time_per_access = (double)total_time / (NUMTRIALS * NUMPAGES);
    printf("%d, %.2f ns\n", NUMPAGES, avg_time_per_access * 1000); // Convert µs to ns

    free(ptr);
    return 0;
}
