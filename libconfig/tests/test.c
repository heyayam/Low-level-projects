#include <stdio.h>
#include "../include/config.h"

int main() {
    config_t *cfg = config_load("config.txt");

    if (!cfg) {
        printf("Failed to load config\n");
        return 1;
    }

    printf("port: %s\n", config_get(cfg, "port"));
    printf("host: %s\n", config_get(cfg, "host"));

    config_free(cfg);
    return 0;
}
