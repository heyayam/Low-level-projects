#ifndef EVENTLOOP_H
#define EVENTLOOP_H

typedef void (*event_callback)(int fd);

typedef struct eventloop eventloop_t;

eventloop_t* eventloop_create();
void eventloop_add_fd(eventloop_t *loop, int fd, event_callback cb);
void eventloop_run(eventloop_t *loop);
void eventloop_free(eventloop_t *loop);

#endif
