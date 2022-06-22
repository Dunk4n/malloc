#include <stdlib.h>
#include "include/malloc.h"

int main(void)
    {
    int i;
    char *addr;

    i = 0;
    while(i < 1)
        {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        Fv__custom_show_alloc_mem();
        free(addr);
        i++;
        }
    return (0);
    }
