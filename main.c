#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t astrlen(const char *str);

int main() {
    char *s = "Hello world";
    size_t alen = astrlen(s);
    size_t slen = strlen(s);
    printf("alen: %lu\n", alen);
    printf("slen: %lu\n", slen);
    return 0;
}