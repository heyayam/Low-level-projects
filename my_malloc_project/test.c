#include <stdio.h>
#include <string.h>

void *my_malloc(size_t size);
void my_free(void *ptr);

int main() {
    char *ptr = (char*) my_malloc(20);

    strcpy(ptr, "Hello allocator!");
    printf("%s\n", ptr);

    my_free(ptr);
    return 0;
}
