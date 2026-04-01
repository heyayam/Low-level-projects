#include "../include/json.h"

int main() {
    const char *text = "{\"name\":\"Alex\",\"age\":25}";

    json_t *json = json_parse(text);
    json_print(json);
    json_free(json);

    return 0;
}
