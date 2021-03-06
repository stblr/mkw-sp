#include <string.h>

char *strchr(const char *s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            // This function is also a const-cast
            return (char *)s;
        }

        s++;
    }

    return NULL;
}
