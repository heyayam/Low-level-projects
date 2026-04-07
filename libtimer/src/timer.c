#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/timer.h"

struct timer {
    int interval_ms;
    timer_callback cb;
    void *arg;
    int running;
    pthread_t thread;
};

static void* run(void *arg) {
    timer_t *t = (timer_t*)arg;
    while (t->running) {
        usleep(t->interval_ms * 1000);
        if (t->running)
            t->cb(t->arg);
    }
    return NULL;
}

timer_t* timer_create(int interval_ms, timer_callback cb, void *arg) {
    timer_t *t = malloc(sizeof(timer_t));
    t->interval_ms = interval_ms;
    t->cb = cb;
    t->arg = arg;
    t->running = 0;
    return t;
}

void timer_start(timer_t *t) {
    if (t->running) return;
    t->running = 1;
    pthread_create(&t->thread, NULL, run, t);
}

void timer_stop(timer_t *t) {
    if (!t->running) return;
    t->running = 0;
    pthread_join(t->thread, NULL);
}

void timer_destroy(timer_t *t) {
    if (t->running)
        timer_stop(t);
    free(t);
}
