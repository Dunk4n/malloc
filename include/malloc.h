/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:21:55 by niduches          #+#    #+#             */
/*   Updated: 2021/09/13 16:06:23 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

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

# include "../libft/libft.h"

# define DEVELOPEMENT
# define RETURN_FAILURE          (0)
# define RETURN_SUCCESS          (1)
# define RETURN_INVALID_ARGUMENT (2)
# define ARGUMENT_CONTINUE       (0)
# define ARGUMENT_ERROR          (1)
# define ARGUMENT_NO_CONTINUE    (2)
# define FALSE                   (0)
# define TRUE                    (1)
# define NIL                     ('\0')

# define FIRST_BIT               (0x01)
# define SECOND_BIT              (0x02)
# define THIRD_BIT               (0x04)
# define FOURTH_BIT              (0x08)
# define FIFTH_BIT               (0x10)
# define SIXTH_BIT               (0x20)
# define SEVENTH_BIT             (0x40)
# define EIGHTH_BIT              (0x80)

# define NOT_FIRST_BIT           (0xFE)
# define NOT_SECOND_BIT          (0xFD)
# define NOT_THIRD_BIT           (0xFB)
# define NOT_FOURTH_BIT          (0xF7)
# define NOT_FIFTH_BIT           (0xEF)
# define NOT_SIXTH_BIT           (0xDF)
# define NOT_SEVENTH_BIT         (0xBF)
# define NOT_EIGHTH_BIT          (0x7F)

#define DEFAULT_TINY_ALLOC_MAX   (5400)
#define MINIMUM_TINY_ALLOC_MAX   (64)
#define MAXIMUM_TINY_ALLOC_MAX   (10240)

#define DEFAULT_SMALL_ALLOC_MAX  (32768)
#define MINIMUM_SMALL_ALLOC_MAX  (20480)
#define MAXIMUM_SMALL_ALLOC_MAX  (65536)

#define MINIMUM_NUMBER_OF_CHUNK_IN_HEAP (100)

#define ENV_TINY_ALLOC_MAX       ("TINY_ALLOC_MAX")
#define ENV_SMALL_ALLOC_MAX      ("SMALL_ALLOC_MAX")

#define LARGE_HEAP_MAGIC_NUMBER (0x7FFFFFFFFFFFFFFF)

#define TINY_ALLOC_MAX  (0x1)
#define SMALL_ALLOC_MAX (0x2)

#define HEAP_HEADER_STRUCT_SIZE (40)
#define CHUNK_HEADER_STRUCT_SIZE (32)

#define THREAD_SAFE

struct sstc_chunk_header
    {
    uint64_t u64_data_length_redundancy_   : 63;
    uint8_t  u8_check_redundancy_1_ : 1;

    uint64_t u64_data_length_ : 63;

    /**
    * Flag actual chunk is free
    */
    uint8_t  u8_data_free_flag_ : 1;

    uint64_t u64_previous_data_length_redundancy_ : 63;
    uint8_t  u8_check_redundancy_2_ : 1;

    uint64_t u64_previous_data_length_ : 63;

    /**
    * Flag previous chunk is the heap header
    */
    uint8_t  u8_previous_data_heap_header_flag_ : 1;
    };

struct sstc_heap_header
    {
    struct sstc_heap_header *ptr_sstc_next_heap_;
    struct sstc_heap_header *ptr_sstc_previous_heap_;
    uint64_t                 u64_length_of_data_;
    uint64_t                 u64_number_of_free_space_;
    union
        {
            uint64_t         u64_heap_status_;

            struct
            {
            uint64_t         u64_static_heap_ : 1;
            uint64_t         u64_tiny_status_ : 1;
            uint64_t         u64_small_status_ : 1;
            uint64_t         u64_large_status_ : 1;
            };
        };
    };

struct cstc_malloc_data
    {
    uint8_t                  u8_global_status_;
    // FIRST_BIT     Structure initialized      1 = Y / 0 = N

    struct sstc_heap_header *ptr_sstc_heap_tiny_list_;
    struct sstc_heap_header *ptr_sstc_last_heap_tiny_;
    //uint8_t                  u8_heap_tiny_data_[TINY_STATIC_HEAP_DATA_SIZE];
    uint64_t                 u64_number_of_tiny_heap_;
    uint64_t                 u64_tiny_heap_size_;
#ifdef THREAD_SAFE
    pthread_mutex_t          etype_mutex_tiny_;
#endif

    struct sstc_heap_header *ptr_sstc_heap_small_list_;
    struct sstc_heap_header *ptr_sstc_last_heap_small_;
    //uint8_t                  u8_heap_small_data_[SMALL_STATIC_HEAP_DATA_SIZE];
    uint64_t                 u64_number_of_small_heap_;
    uint64_t                 u64_small_heap_size_;
#ifdef THREAD_SAFE
    pthread_mutex_t          etype_mutex_small_;
#endif

    struct sstc_heap_header *ptr_sstc_heap_large_list_;
    struct sstc_heap_header *ptr_sstc_last_heap_large_;
    uint64_t                 u64_number_of_large_heap_;
#ifdef THREAD_SAFE
    pthread_mutex_t          etype_mutex_large_;
#endif

#ifdef THREAD_SAFE
    pthread_mutex_t          etype_mutex_parameter_;
#endif
    uint64_t                 u64_tiny_alloc_max_;
    uint64_t                 u64_small_alloc_max_;
    };

struct cstc_malloc_data cstc_glbl_malloc_data;

uint8_t Fu8__load_parameter_value_from_env_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data);
uint8_t Fu8__init_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data);
uint8_t Fu8__close_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data);

uint8_t Fu8__generate_new_tiny_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data);
uint8_t Fu8__generate_new_small_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data);
uint8_t Fu8__generate_new_large_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data, uint64_t u64_pssd_length_of_large_heap);

uint8_t Fu8__alloc_chunk_in_heap(void *ptr_vd_pssd_heap, uint64_t u64_pssd_size_to_allocate, void **dbl_ptr_vd_pssd_allocated_chunk_to_return);
void Fv__simple_display_heap(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory);
void Fv__simple_display_heap_ex(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory);
void Fv__display_heap(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory);
void Fv__custom_show_alloc_mem(void);

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);
void show_alloc_mem_ex(void);
void *calloc(size_t nmemb, size_t size);

/**
* TINY_ALLOC_MAX
* SMALL_ALLOC_MAX
*/
int mallopt(int param, int value);

#endif /* FT_MALLOC_H */
