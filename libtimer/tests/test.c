#include <stdio.h>
#include <unistd.h>
#include "../include/timer.h"

void callback(void *arg) {
    int *count = (int*)arg;
    (*count)++;
    printf("Tick %d\n", *count);
}

int main() {
    int count = 0;

    timer_t *t = timer_create(500, callback, &count);
    timer_start(t);

    sleep(3);

    timer_stop(t);
    timer_destroy(t);

    return 0;
}
