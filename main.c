# include <inttypes.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/mman.h>
# include <linux/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <errno.h>
# include <string.h>

#define NB 1

int main(void)
    {
    void *ptr_vd_mmaped_memory;
    uint64_t i = 0;

    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, 4096 * NB, PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_PRIVATE | MAP_ANONYMOUS | MAP_UNINITIALIZED, -1, 0);

    if(ptr_vd_mmaped_memory == MAP_FAILED)
        {
        printf("mmap error\n");
        return (1);
        }

    i = 0;
    while(i < 4096 * NB)
        {
        printf("%u", ((uint8_t *) ptr_vd_mmaped_memory)[i]);

        i++;
        }
    printf("\n");
    return (0);
    }
