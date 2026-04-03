#ifndef CONFIG_H
#define CONFIG_H

typedef struct config config_t;

config_t* config_load(const char *filename);
const char* config_get(config_t *cfg, const char *key);
void config_free(config_t *cfg);

#endif
