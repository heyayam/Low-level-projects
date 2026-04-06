#include <stdlib.h>
#include <sys/select.h>
#include "../include/eventloop.h"

#define MAX_FDS 1024

typedef struct {
    int fd;
    event_callback cb;
} event_t;

struct eventloop {
    event_t events[MAX_FDS];
    int count;
};

eventloop_t* eventloop_create() {
    eventloop_t *loop = malloc(sizeof(eventloop_t));
    loop->count = 0;
    return loop;
}

void eventloop_add_fd(eventloop_t *loop, int fd, event_callback cb) {
    loop->events[loop->count].fd = fd;
    loop->events[loop->count].cb = cb;
    loop->count++;
}

void eventloop_run(eventloop_t *loop) {
    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        int maxfd = 0;
        for (int i = 0; i < loop->count; i++) {
            FD_SET(loop->events[i].fd, &readfds);
            if (loop->events[i].fd > maxfd)
                maxfd = loop->events[i].fd;
        }

        int ready = select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if (ready > 0) {
            for (int i = 0; i < loop->count; i++) {
                if (FD_ISSET(loop->events[i].fd, &readfds)) {
                    loop->events[i].cb(loop->events[i].fd);
                }
            }
        }
    }
}

void eventloop_free(eventloop_t *loop) {
    free(loop);
}
