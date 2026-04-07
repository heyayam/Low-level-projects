#ifndef TIMER_H
#define TIMER_H

typedef void (*timer_callback)(void*);

typedef struct timer timer_t;

timer_t* timer_create(int interval_ms, timer_callback cb, void *arg);
void timer_start(timer_t *t);
void timer_stop(timer_t *t);
void timer_destroy(timer_t *t);

#endif
