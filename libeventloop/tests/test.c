#include <stdio.h>
#include <unistd.h>
#include "../include/eventloop.h"

void stdin_callback(int fd) {
    char buf[100];
    int n = read(fd, buf, sizeof(buf)-1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Input: %s", buf);
    }
}

int main() {
    eventloop_t *loop = eventloop_create();

    eventloop_add_fd(loop, 0, stdin_callback);

    printf("Type something (Ctrl+C to exit):\n");
    eventloop_run(loop);

    eventloop_free(loop);
    return 0;
}
