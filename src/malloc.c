/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:39:11 by niduches          #+#    #+#             */
/*   Updated: 2019/10/08 17:48:52 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

struct cstc_malloc_data cstc_glbl_malloc_data = {0};

uint8_t Fu8__update_heap_size_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        } 

    /**
    * Creation of local variable
    */
    int32_t  s32_lcl_page_size;
#ifdef THREAD_SAFE
    int32_t  s32_lcl_return_from_function;
#endif
    uint64_t u64_lcl_small_heap_value;
    uint64_t u64_lcl_tiny_heap_value;

    /**
    * Initialization of local variable
    */
    s32_lcl_page_size            = 0;
#ifdef THREAD_SAFE
    s32_lcl_return_from_function = -1;
#endif
    u64_lcl_small_heap_value     = 0;
    u64_lcl_tiny_heap_value      = 0;

    /**
    * Getting the page size
    */
    s32_lcl_page_size = getpagesize();

    /**
    * Check if the page size is zero or lower
    */
    if(s32_lcl_page_size < 1)
        {
        /**
        * Treat the case when the page size is zero or lower
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the page size is zero or lower\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the page size is zero or lower
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the page size is bigger than zero
        */
        } 

#ifdef THREAD_SAFE
    /**
    * Locking the mutex parameter
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

    /**
    * Check if function to lock the mutex parameter succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex parameter failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex parameter failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex parameter succeeded
        */
        }
#endif

    /**
    * Getting the size of a tiny heap
    */
    u64_lcl_tiny_heap_value = (((((ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ + sizeof(struct sstc_chunk_header)) * MINIMUM_NUMBER_OF_CHUNK_IN_HEAP) + sizeof(struct sstc_heap_header)) / s32_lcl_page_size) + 1) * s32_lcl_page_size;

    /**
    * Getting the size of a small heap
    */
    u64_lcl_small_heap_value = (((((ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ + sizeof(struct sstc_chunk_header)) * MINIMUM_NUMBER_OF_CHUNK_IN_HEAP) + sizeof(struct sstc_heap_header)) / s32_lcl_page_size) + 1) * s32_lcl_page_size;

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex parameter
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

    /**
    * Check if function to unlock the mutex parameter succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex parameter failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex parameter failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex parameter succeeded
        */
        }

    /**
    * Locking the mutex tiny heap
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

    /**
    * Check if function to lock the mutex tiny heap succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex tiny heap failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex tiny heap failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex tiny heap failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex tiny heap succeeded
        */
        }
#endif

    /**
    * Setting the tiny heap size
    */
    ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ = u64_lcl_tiny_heap_value;

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex tiny heap
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

    /**
    * Check if function to unlock the mutex tiny heap succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex tiny heap failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex tiny heap failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex tiny heap failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex tiny heap succeeded
        */
        }

    /**
    * Locking the mutex small heap
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);

    /**
    * Check if function to lock the mutex small heap succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex small heap failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex small heap failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex small heap failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex small heap succeeded
        */
        }
#endif

    /**
    * Setting the small heap size
    */
    ptr_cstc_pssd_malloc_data->u64_small_heap_size_ = u64_lcl_small_heap_value;

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex small heap
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);

    /**
    * Check if function to unlock the mutex small heap succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex small heap failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex small heap failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex small heap failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex small heap succeeded
        */
        }
#endif

    return (RETURN_SUCCESS);
    }

uint8_t Fu8__load_parameter_value_from_env_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        } 

    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t  s32_lcl_return_from_function;
#endif
    uint8_t  u8_lcl_return_from_function;
    uint8_t *ptr_u8_lcl_environement_value;

    /**
    * Initialization of local variable
    */
    ptr_u8_lcl_environement_value = NULL;
#ifdef THREAD_SAFE
    s32_lcl_return_from_function  = RETURN_FAILURE;
#endif
    u8_lcl_return_from_function   = RETURN_FAILURE;

#ifdef THREAD_SAFE
    /**
    * Locking the mutex parameter
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_);

    /**
    * Check if function to lock the mutex parameter succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex parameter failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex parameter failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex parameter succeeded
        */
        } 
#endif

    /**
    * Getting the value of the environement variable of tiny alloc max
    */
    ptr_u8_lcl_environement_value = NULL;
    ptr_u8_lcl_environement_value = (uint8_t *) getenv(ENV_TINY_ALLOC_MAX);

    /**
    * Check if function to get the value of the environement variable of tiny alloc max succeeded
    */
    if(ptr_u8_lcl_environement_value != NULL)
        {
        /**
        * Treat the case when the function to get the value of the environement variable of tiny alloc max failed
        */

        ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ = ft_atoui((char *) ptr_u8_lcl_environement_value);

        /**
        * Check if the tiny alloc max is smaller than the minimum tiny alloc max
        */
        if(ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ < MINIMUM_TINY_ALLOC_MAX)
            {
            /**
            * Treat the case when the tiny alloc max is smaller than the minimum tiny alloc max
            */

            ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ = MINIMUM_TINY_ALLOC_MAX;
            }
        else
            {
            /**
            * Treat the case when the tiny alloc max is not smaller than the minimum tiny alloc max
            */
            }

        /**
        * Check if the tiny alloc max is bigger than the minimum tiny alloc max
        */
        if(ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ > MAXIMUM_TINY_ALLOC_MAX)
            {
            /**
            * Treat the case when the tiny alloc max is bigger than the minimum tiny alloc max
            */

            ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_ = MAXIMUM_TINY_ALLOC_MAX;
            }
        else
            {
            /**
            * Treat the case when the tiny alloc max is not bigger than the minimum tiny alloc max
            */
            }
        }
    else
        {
        /**
        * Treat the case when function to get the value of the environement variable of tiny alloc max succeeded
        */
        }

    /**
    * Getting the value of the environement variable of small alloc max
    */
    ptr_u8_lcl_environement_value = NULL;
    ptr_u8_lcl_environement_value = (uint8_t *) getenv(ENV_SMALL_ALLOC_MAX);

    /**
    * Check if function to get the value of the environement variable of small alloc max succeeded
    */
    if(ptr_u8_lcl_environement_value != NULL)
        {
        /**
        * Treat the case when the function to get the value of the environement variable of small alloc max failed
        */

        ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ = ft_atoui((char *) ptr_u8_lcl_environement_value);

        /**
        * Check if the small alloc max is smaller than the minimum small alloc max
        */
        if(ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ < MINIMUM_SMALL_ALLOC_MAX)
            {
            /**
            * Treat the case when the small alloc max is smaller than the minimum small alloc max
            */

            ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ = MINIMUM_SMALL_ALLOC_MAX;
            }
        else
            {
            /**
            * Treat the case when the small alloc max is not smaller than the minimum small alloc max
            */
            }

        /**
        * Check if the small alloc max is bigger than the minimum small alloc max
        */
        if(ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ > MAXIMUM_SMALL_ALLOC_MAX)
            {
            /**
            * Treat the case when the small alloc max is bigger than the minimum small alloc max
            */

            ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ = MAXIMUM_SMALL_ALLOC_MAX;
            }
        else
            {
            /**
            * Treat the case when the small alloc max is not bigger than the minimum small alloc max
            */
            }
        }
    else
        {
        /**
        * Treat the case when function to get the value of the environement variable of small alloc max succeeded
        */
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex parameter
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_);

    /**
    * Check if function to unlock the mutex parameter succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex parameter failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex parameter failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex parameter succeeded
        */
        } 
#endif

    /**
    * Updating the heap size
    */
    u8_lcl_return_from_function = RETURN_FAILURE;
    u8_lcl_return_from_function = Fu8__update_heap_size_in_structure_malloc_data(ptr_cstc_pssd_malloc_data);

    /**
    * Check if function to update the heap size succeeded
    */
    if(u8_lcl_return_from_function != RETURN_SUCCESS)
        {
        /**
        * Treat the case when the function to update the heap size failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to update the heap size failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to update the heap size failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to update the heap size succeeded
        */
        } 

    return (RETURN_SUCCESS);
    }

uint8_t Fu8__init_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is already initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) != FALSE)
        {
        /**
        * Treat the case when the structure malloc data is already initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is already initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is already initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is not initialized as expected
        */
        } 

    /**
    * Creation of local variable
    */
    uint8_t  u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
    u8_lcl_return_from_function = RETURN_FAILURE;

    /**
    * Setting all the value of the global status of the structure to false
    */
    ptr_cstc_pssd_malloc_data->u8_global_status_ = 0;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FIRST_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SECOND_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_THIRD_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FOURTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FIFTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SIXTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SEVENTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_EIGHTH_BIT;

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_tiny_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_ = NULL;

    ptr_cstc_pssd_malloc_data->u64_number_of_tiny_heap_ = 0;
    ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ = 0;
#ifdef THREAD_SAFE
    (void) pthread_mutex_init(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_, NULL);
#endif

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_small_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_ = NULL;

    ptr_cstc_pssd_malloc_data->u64_number_of_small_heap_ = 0;
    ptr_cstc_pssd_malloc_data->u64_small_heap_size_ = 0;
#ifdef THREAD_SAFE
    (void) pthread_mutex_init(&ptr_cstc_pssd_malloc_data->etype_mutex_small_, NULL);
#endif

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_large_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_ = NULL;
    ptr_cstc_pssd_malloc_data->u64_number_of_large_heap_ = 0;
#ifdef THREAD_SAFE
    (void) pthread_mutex_init(&ptr_cstc_pssd_malloc_data->etype_mutex_large_, NULL);
#endif

#ifdef THREAD_SAFE
    (void) pthread_mutex_init(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_, NULL);
#endif
    ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_  = DEFAULT_TINY_ALLOC_MAX;
    ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ = DEFAULT_SMALL_ALLOC_MAX;

    /**
    * Setting the structure argument to initialized
    */
    ptr_cstc_pssd_malloc_data->u8_global_status_ |= FIRST_BIT;

    /**
    * Loading the parameter value from the env
    */
    u8_lcl_return_from_function = RETURN_FAILURE;
    u8_lcl_return_from_function = Fu8__load_parameter_value_from_env_in_structure_malloc_data(ptr_cstc_pssd_malloc_data);

    /**
    * Check if function to load the parameter value from the env succeeded
    */
    if(u8_lcl_return_from_function != RETURN_SUCCESS)
        {
        /**
        * Treat the case when the function to load the parameter value from the env failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to load the parameter value from the env failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to load the parameter value from the env failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to load the parameter value from the env succeeded
        */
        }

    return (RETURN_SUCCESS);
    }

uint8_t Fu8__close_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        } 

    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t  s32_lcl_return_from_function;
#endif

    /**
    * Initialization of local variable
    */
#ifdef THREAD_SAFE
    s32_lcl_return_from_function = RETURN_FAILURE;
#endif

#ifdef THREAD_SAFE
    /**
    * Locking the mutex tiny
    */
    s32_lcl_return_from_function = RETURN_FAILURE;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

    /**
    * Check if function to lock the mutex tiny succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex tiny failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex tiny failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex tiny failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex tiny succeeded
        */
        } 

    /**
    * Locking the mutex small
    */
    s32_lcl_return_from_function = RETURN_FAILURE;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);

    /**
    * Check if function to lock the mutex small succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex small failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex small failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);

        /**
        * Return failure to indicate the function to lock the mutex small failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex small succeeded
        */
        } 

    /**
    * Locking the mutex large
    */
    s32_lcl_return_from_function = RETURN_FAILURE;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_large_);

    /**
    * Check if function to lock the mutex large succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex large failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex large failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);
        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);

        /**
        * Return failure to indicate the function to lock the mutex large failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex large succeeded
        */
        } 

    /**
    * Locking the mutex parameter
    */
    s32_lcl_return_from_function = RETURN_FAILURE;
    s32_lcl_return_from_function = pthread_mutex_lock(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_);

    /**
    * Check if function to lock the mutex parameter succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex parameter failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);
        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);
        (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_large_);

        /**
        * Return failure to indicate the function to lock the mutex parameter failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex parameter succeeded
        */
        } 
#endif

    //TODO munmap all list of heap

    /**
    * Setting all the value of the global status of the structure to false
    */
    ptr_cstc_pssd_malloc_data->u8_global_status_ = 0;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FIRST_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SECOND_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_THIRD_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FOURTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FIFTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SIXTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_SEVENTH_BIT;
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_EIGHTH_BIT;

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_tiny_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_ = NULL;

    ptr_cstc_pssd_malloc_data->u64_number_of_tiny_heap_ = 0;

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_small_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_ = NULL;

    ptr_cstc_pssd_malloc_data->u64_number_of_small_heap_ = 0;

    ptr_cstc_pssd_malloc_data->ptr_sstc_heap_large_list_ = NULL;
    ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_ = NULL;
    ptr_cstc_pssd_malloc_data->u64_number_of_large_heap_ = 0;

    ptr_cstc_pssd_malloc_data->u64_tiny_alloc_max_  = 0;
    ptr_cstc_pssd_malloc_data->u64_small_alloc_max_ = 0;

#ifdef THREAD_SAFE
    (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);
    (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);
    (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_large_);
    (void) pthread_mutex_unlock(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_);

    (void) pthread_mutex_destroy(&ptr_cstc_pssd_malloc_data->etype_mutex_tiny_);
    (void) pthread_mutex_destroy(&ptr_cstc_pssd_malloc_data->etype_mutex_small_);
    (void) pthread_mutex_destroy(&ptr_cstc_pssd_malloc_data->etype_mutex_large_);
    (void) pthread_mutex_destroy(&ptr_cstc_pssd_malloc_data->etype_mutex_parameter_);
#endif

    /**
    * Setting the structure argument to uninitialized
    */
    ptr_cstc_pssd_malloc_data->u8_global_status_ &= NOT_FIRST_BIT;

    return (RETURN_SUCCESS);
    }

/**
* the tiny heap list mutex must be hold when entering the function
*/
uint8_t Fu8__generate_new_tiny_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        }

    /**
    * Creation of local variable
    */
    void *ptr_vd_mmaped_memory;

    /**
    * Initialization of local variable
    */
    ptr_vd_mmaped_memory = NULL;

    /**
    * Getting virtual memory
    */
#if __APPLE__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#elif __linux__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_, PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

    /**
    * Check if function to get virtual memory succeeded
    */
    if((ptr_vd_mmaped_memory == MAP_FAILED) || (ptr_vd_mmaped_memory == NULL))
        {
        /**
        * Treat the case when the function to get virtual memory failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get virtual memory failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get virtual memory failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to get virtual memory succeeded
        */
        }

    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_       = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_   = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_length_of_data_       = ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ - sizeof(struct sstc_heap_header);
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_number_of_free_space_ = ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header);
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_heap_status_          = 0;

    /**
    * Setting the actual heap to tiny
    */
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_tiny_status_ = TRUE;

    /**
    * Check if if their is no element in the list of tiny heap
    */
    if(ptr_cstc_pssd_malloc_data->ptr_sstc_heap_tiny_list_ == NULL)
        {
        /**
        * Treat the case when if their is no element in the list of tiny heap
        */

        ptr_cstc_pssd_malloc_data->ptr_sstc_heap_tiny_list_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        }
    else
        {
        /**
        * Treat the case when if their is element in the list of tiny heap
        */

        /**
        * Setting the new tiny heap to the end of the tiny heap list
        */
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_ = ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_;
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_     = NULL;

        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_->ptr_sstc_next_heap_ = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_tiny_                      = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        }

    /**
    * Checking for overflow
    */
    if(ptr_cstc_pssd_malloc_data->u64_number_of_tiny_heap_ < UINT64_MAX)
        {
        ptr_cstc_pssd_malloc_data->u64_number_of_tiny_heap_++;
        }
    else
        {
        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return a failure to indicate the counter variable overflow
        */ 
        return (RETURN_FAILURE);
        } 

    /**
    * Setting a free chunk to the total size of the new heap
    */
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_redundancy_          = (ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header));
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_1_               = TRUE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_redundancy_ = 0;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_2_               = TRUE;

    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_                   = (ptr_cstc_pssd_malloc_data->u64_tiny_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header));
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_data_free_flag_                 = TRUE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_          = 0;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_previous_data_heap_header_flag_ = TRUE;

    return (RETURN_SUCCESS);
    }

/**
* the small heap list mutex must be hold when entering the function
*/
uint8_t Fu8__generate_new_small_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        }

    /**
    * Creation of local variable
    */
    void *ptr_vd_mmaped_memory;

    /**
    * Initialization of local variable
    */
    ptr_vd_mmaped_memory = NULL;

    /**
    * Getting virtual memory
    */
#if __APPLE__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, ptr_cstc_pssd_malloc_data->u64_small_heap_size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#elif __linux__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, ptr_cstc_pssd_malloc_data->u64_small_heap_size_, PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

    /**
    * Check if function to get virtual memory succeeded
    */
    if((ptr_vd_mmaped_memory == MAP_FAILED) || (ptr_vd_mmaped_memory == NULL))
        {
        /**
        * Treat the case when the function to get virtual memory failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get virtual memory failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get virtual memory failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to get virtual memory succeeded
        */
        }

    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_       = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_   = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_length_of_data_       = ptr_cstc_pssd_malloc_data->u64_small_heap_size_ - sizeof(struct sstc_heap_header);
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_number_of_free_space_ = ptr_cstc_pssd_malloc_data->u64_small_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header);
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_heap_status_          = 0;

    /**
    * Setting the actual heap to small
    */
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_small_status_ = TRUE;

    /**
    * Check if if their is no element in the list of small heap
    */
    if(ptr_cstc_pssd_malloc_data->ptr_sstc_heap_small_list_ == NULL)
        {
        /**
        * Treat the case when if their is no element in the list of small heap
        */

        ptr_cstc_pssd_malloc_data->ptr_sstc_heap_small_list_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        }
    else
        {
        /**
        * Treat the case when if their is element in the list of small heap
        */

        /**
        * Setting the new small heap to the end of the small heap list
        */
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_ = ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_;
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_     = NULL;

        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_->ptr_sstc_next_heap_ = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_small_                      = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        }

    /**
    * Checking for overflow
    */
    if(ptr_cstc_pssd_malloc_data->u64_number_of_small_heap_ < UINT64_MAX)
        {
        ptr_cstc_pssd_malloc_data->u64_number_of_small_heap_++;
        }
    else
        {
        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return a failure to indicate the counter variable overflow
        */ 
        return (RETURN_FAILURE);
        } 

    /**
    * Setting a free chunk to the total size of the new heap
    */
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_redundancy_          = (ptr_cstc_pssd_malloc_data->u64_small_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header));
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_1_               = TRUE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_redundancy_ = 0;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_2_               = TRUE;

    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_                   = (ptr_cstc_pssd_malloc_data->u64_small_heap_size_ - sizeof(struct sstc_heap_header) - sizeof(struct sstc_chunk_header));
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_data_free_flag_                 = TRUE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_          = 0;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_previous_data_heap_header_flag_ = TRUE;

    return (RETURN_SUCCESS);
    }

/**
* the large heap list mutex must be hold when entering the function
*/
uint8_t Fu8__generate_new_large_heap_in_structure_malloc_data(struct cstc_malloc_data *ptr_cstc_pssd_malloc_data, uint64_t u64_pssd_length_of_large_heap)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the structure malloc data is correctly pointing passed as an argument of the function
    */
    if(ptr_cstc_pssd_malloc_data == NULL)
        {
        /**
        * Treat the case when the structure malloc data is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Check if the structure malloc data is not initialized
    */
    if((ptr_cstc_pssd_malloc_data->u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when the structure malloc data is not initialized
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the structure malloc data is not initialized\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the structure malloc data is not initialized
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the structure malloc data is initialized as expected
        */
        }

    /**
    * Creation of local variable
    */
    void   *ptr_vd_mmaped_memory;

    /**
    * Initialization of local variable
    */
    ptr_vd_mmaped_memory         = NULL;

    /**
    * Getting virtual memory
    */
#if __APPLE__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, u64_pssd_length_of_large_heap + sizeof(struct sstc_chunk_header) + sizeof(struct sstc_heap_header), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#elif __linux__
    ptr_vd_mmaped_memory = MAP_FAILED;
    ptr_vd_mmaped_memory = mmap(NULL, u64_pssd_length_of_large_heap + sizeof(struct sstc_chunk_header) + sizeof(struct sstc_heap_header), PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

    /**
    * Check if function to get virtual memory succeeded
    */
    if((ptr_vd_mmaped_memory == MAP_FAILED) || (ptr_vd_mmaped_memory == NULL))
        {
        /**
        * Treat the case when the function to get virtual memory failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get virtual memory failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get virtual memory failed
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when function to get virtual memory succeeded
        */
        }

    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_       = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_   = NULL;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_length_of_data_       = u64_pssd_length_of_large_heap + sizeof(struct sstc_chunk_header);
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_number_of_free_space_ = 0;
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_heap_status_          = 0;

    /**
    * Setting the actual heap to large
    */
    ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->u64_large_status_ = TRUE;

    /**
    * Check if if their is no element in the list of large heap
    */
    if(ptr_cstc_pssd_malloc_data->ptr_sstc_heap_large_list_ == NULL)
        {
        /**
        * Treat the case when if their is no element in the list of large heap
        */

        ptr_cstc_pssd_malloc_data->ptr_sstc_heap_large_list_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_ = (struct sstc_heap_header *) ptr_vd_mmaped_memory;
        }
    else
        {
        /**
        * Treat the case when if their is element in the list of large heap
        */

        /**
        * Setting the new large heap to the end of the large heap list
        */
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_previous_heap_ = ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_;
        ((struct sstc_heap_header *) ptr_vd_mmaped_memory)->ptr_sstc_next_heap_     = NULL;

        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_->ptr_sstc_next_heap_ = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        ptr_cstc_pssd_malloc_data->ptr_sstc_last_heap_large_                      = ((struct sstc_heap_header *) ptr_vd_mmaped_memory);
        }

    /**
    * Checking for overflow
    */
    if(ptr_cstc_pssd_malloc_data->u64_number_of_large_heap_ < UINT64_MAX)
        {
        ptr_cstc_pssd_malloc_data->u64_number_of_large_heap_++;
        }
    else
        {
        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return a failure to indicate the counter variable overflow
        */ 
        return (RETURN_FAILURE);
        } 

    /**
    * Setting a free chunk to the total size of the new heap
    */
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_redundancy_          = u64_pssd_length_of_large_heap;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_1_               = TRUE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_redundancy_ = LARGE_HEAP_MAGIC_NUMBER;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_check_redundancy_2_               = TRUE;

    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_data_length_                   = u64_pssd_length_of_large_heap;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_data_free_flag_                 = FALSE;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u64_previous_data_length_          = LARGE_HEAP_MAGIC_NUMBER;
    ((struct sstc_chunk_header *) (ptr_vd_mmaped_memory + sizeof(struct sstc_heap_header)))->u8_previous_data_heap_header_flag_ = TRUE;

    return (RETURN_SUCCESS);
    }

/**
* the coresponding heap list mutex must be hold when entering the function
*/
uint8_t Fu8__alloc_chunk_in_heap(void *ptr_vd_pssd_heap, uint64_t u64_pssd_size_to_allocate, void **dbl_ptr_vd_pssd_allocated_chunk_to_return)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the heap is correctly pointing passed as an argument of the function
    */
    if(ptr_vd_pssd_heap == NULL)
        {
        /**
        * Treat the case when the heap is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the heap is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the heap is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the heap is correctly pointing passed as an argument of the function
        */
        } 

    /**
    * Check if the size to allocate is zero
    */
    if(u64_pssd_size_to_allocate == 0)
        {
        /**
        * Treat the case when the size to allocate is zero
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the size to allocate is zero\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the size to allocate is zero
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the size to allocate is not zero
        */
        }

    /**
    * Check if the pointer to the new allocated data to return is correctly pointing passed as an argument of the function
    */
    if(dbl_ptr_vd_pssd_allocated_chunk_to_return == NULL)
        {
        /**
        * Treat the case when the pointer to the new allocated data to return is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the pointer to the new allocated data to return is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the pointer to the new allocated data to return is not correctly pointing passed as an argument of the function
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when the pointer to the new allocated data to return is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Creation of local variable
    */
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_chunk_to_change_previous_size;
    struct sstc_chunk_header *ptr_sstc_lcl_next_chunk;
    uint64_t                  u64_lcl_position_in_heap;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk                  = NULL;
    ptr_sstc_lcl_chunk_to_change_previous_size = NULL;
    ptr_sstc_lcl_next_chunk                    = NULL;
    u64_lcl_position_in_heap                   = 0;

    (*dbl_ptr_vd_pssd_allocated_chunk_to_return) = NULL;

    /**
    * Check if the size to allocate is bigger than the free space in the actual heap
    */
    if(u64_pssd_size_to_allocate > ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_)
        {
        /**
        * Treat the case when the size to allocate is bigger than the free space in the actual heap
        */

        (*dbl_ptr_vd_pssd_allocated_chunk_to_return) = NULL;

        return (RETURN_SUCCESS);
        }
    else
        {
        /**
        * Treat the case when the size to allocate is not bigger than the free space in the actual heap
        */
        }

    /**
    * Getting the address of the first chunk of the heap
    */
    u64_lcl_position_in_heap  = sizeof(struct sstc_heap_header);
    ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
    while(u64_lcl_position_in_heap < ((uint64_t) ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_ + sizeof(struct sstc_heap_header)))
        {
        /**
        * Check if the actual chunk is free
        */
        if(ptr_sstc_lcl_actual_chunk->u8_data_free_flag_ == TRUE)
            {
            /**
            * Treat the case when the actual chunk is free
            */

            /**
            * Check if the actual free chunk can contain the chunk to allocate
            */
            if(u64_pssd_size_to_allocate <= (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_)
                {
                /**
                * Treat the case when the actual free chunk can contain the chunk to allocate
                */

                /**
                * Setting the actual chunk not free
                */
                ptr_sstc_lcl_actual_chunk->u8_data_free_flag_ = FALSE;

                (*dbl_ptr_vd_pssd_allocated_chunk_to_return)  = ptr_vd_pssd_heap + u64_lcl_position_in_heap;

                /**
                * Check if the size after the new allocated chunk is bigger than a chunk header
                */
                if(((uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_ - u64_pssd_size_to_allocate) > sizeof(struct sstc_chunk_header))
                    {
                    /**
                    * Treat the case when the size after the new allocated chunk is bigger than a chunk header
                    */

                    /**
                    * Getting the address of the next chunk of the heap
                    */
                    ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header) + u64_pssd_size_to_allocate);

                    /**
                    * Setting the create of the next new chunk of the heap
                    */
                    ptr_sstc_lcl_next_chunk->u64_data_length_redundancy_          = (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_ - u64_pssd_size_to_allocate - sizeof(struct sstc_chunk_header);
                    ptr_sstc_lcl_next_chunk->u8_check_redundancy_1_               = TRUE;
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_redundancy_ = u64_pssd_size_to_allocate;
                    ptr_sstc_lcl_next_chunk->u8_check_redundancy_2_               = TRUE;

                    ptr_sstc_lcl_next_chunk->u64_data_length_                   = (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_ - u64_pssd_size_to_allocate - sizeof(struct sstc_chunk_header);
                    ptr_sstc_lcl_next_chunk->u8_data_free_flag_                 = TRUE;
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_          = u64_pssd_size_to_allocate;
                    ptr_sstc_lcl_next_chunk->u8_previous_data_heap_header_flag_ = FALSE;

                    /**
                    * Setting the number of free space in the actual heap
                    */
                    ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_ = (((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_ - sizeof(struct sstc_chunk_header));

                    /**
                    * Setting the size of the actual chunk in the heap
                    */
                    ptr_sstc_lcl_actual_chunk->u64_data_length_redundancy_ = u64_pssd_size_to_allocate;
                    ptr_sstc_lcl_actual_chunk->u64_data_length_            = u64_pssd_size_to_allocate;

                    /**
                    * Getting the position of the next chunk of the new created chunk
                    */
                    u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header)) + (ptr_sstc_lcl_next_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header));

                    /**
                    * Check if the new created chunk is not the last chunk of the heap
                    */
                    if(u64_lcl_position_in_heap < ((uint64_t) ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_ + sizeof(struct sstc_heap_header)))
                        {
                        /**
                        * Treat the case when the new created chunk is not the last chunk of the heap
                        */

                        /**
                        * Setting the size of the previous chunk of the next chunk of the new created chunk
                        */
                        ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_next_chunk->u64_data_length_;
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_next_chunk->u64_data_length_;
                        }
                    else
                        {
                        /**
                        * Treat the case when the new created chunk is the last chunk of the heap
                        */
                        }
                    }
                else
                    {
                    /**
                    * Treat the case when the size after the new allocated chunk is not bigger than a chunk header
                    */
                    }

                /**
                * Setting the number of free space in the actual heap
                */
                ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_ = (((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_ - ptr_sstc_lcl_actual_chunk->u64_data_length_);

                return (RETURN_SUCCESS);
                }
            else
                {
                /**
                * Treat the case when the actual free chunk can not contain the chunk to allocate
                */
                }
            }
        else
            {
            /**
            * Treat the case when the actual chunk is not free
            */
            }

        u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header));

        /**
        * Getting the address of the next chunk of the heap
        */
        ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
        }

    (*dbl_ptr_vd_pssd_allocated_chunk_to_return) = NULL;

    return (RETURN_SUCCESS);
    }

/**
* the coresponding heap list mutex must be hold when entering the function
* ptr_u64_pssd_total_allocated_memory can be NULL
*/
void Fv__simple_display_heap(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the heap is correctly pointing passed as an argument of the function
    */
    if(ptr_vd_pssd_heap == NULL)
        {
        /**
        * Treat the case when the heap is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the heap is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the heap is not correctly pointing passed as an argument of the function
        */
        return;
        }
    else
        {
        /**
        * Treat the case when the heap is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Creation of local variable
    */
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    uint64_t                  u64_lcl_position_in_heap;
    uint64_t                  u64_lcl_total_allocated_memory;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk      = NULL;
    u64_lcl_position_in_heap       = 0;
    u64_lcl_total_allocated_memory = 0;

    /**
    * Getting the address of the first chunk of the heap
    */
    u64_lcl_position_in_heap  = sizeof(struct sstc_heap_header);
    ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);

    while(u64_lcl_position_in_heap < ((uint64_t) ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_ + sizeof(struct sstc_heap_header)))
        {
        /**
        * Check if the actual chunk is not free
        */
        if(ptr_sstc_lcl_actual_chunk->u8_data_free_flag_ == FALSE)
            {
            /**
            * Treat the case when the actual chunk is not free
            */

            if(u64_lcl_total_allocated_memory == 0)
                {
                if(((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_tiny_status_ == TRUE)
                    {
                    ft_printf("TINY : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                else if(((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_small_status_ == TRUE)
                    {
                    ft_printf("SMALL : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                else
                    {
                    ft_printf("LARGE : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                }

            ft_printf("0x%" PRIX64 " - 0x%" PRIX64 " : %" PRIu64 " octets\n", (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header), (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_);

            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + ptr_sstc_lcl_actual_chunk->u64_data_length_;
            }
        else
            {
            /**
            * Treat the case when the actual chunk is free
            */
            }

        u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header));

        /**
        * Getting the address of the next chunk of the heap
        */
        ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
        }

    if(ptr_u64_pssd_total_allocated_memory != NULL)
        {
        (*ptr_u64_pssd_total_allocated_memory) = u64_lcl_total_allocated_memory;
        }
    }

/**
* the coresponding heap list mutex must be hold when entering the function
* ptr_u64_pssd_total_allocated_memory can be NULL
*/
void Fv__simple_display_heap_ex(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the heap is correctly pointing passed as an argument of the function
    */
    if(ptr_vd_pssd_heap == NULL)
        {
        /**
        * Treat the case when the heap is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the heap is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the heap is not correctly pointing passed as an argument of the function
        */
        return;
        }
    else
        {
        /**
        * Treat the case when the heap is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Creation of local variable
    */
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    uint64_t                  u64_lcl_cnt;
    uint64_t                  u64_lcl_position_in_heap;
    uint64_t                  u64_lcl_total_allocated_memory;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk      = NULL;
    u64_lcl_cnt                    = 0;
    u64_lcl_position_in_heap       = 0;
    u64_lcl_total_allocated_memory = 0;

    /**
    * Getting the address of the first chunk of the heap
    */
    u64_lcl_position_in_heap  = sizeof(struct sstc_heap_header);
    ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);

    while(u64_lcl_position_in_heap < ((uint64_t) ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_ + sizeof(struct sstc_heap_header)))
        {
        /**
        * Check if the actual chunk is not free
        */
        if(ptr_sstc_lcl_actual_chunk->u8_data_free_flag_ == FALSE)
            {
            /**
            * Treat the case when the actual chunk is not free
            */

            if(u64_lcl_total_allocated_memory == 0)
                {
                if(((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_tiny_status_ == TRUE)
                    {
                    ft_printf("TINY : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                else if(((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_small_status_ == TRUE)
                    {
                    ft_printf("SMALL : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                else
                    {
                    ft_printf("LARGE : 0x%lX\n", (uintptr_t) ptr_vd_pssd_heap);
                    }
                }

            ft_printf("0x%" PRIX64 " - 0x%" PRIX64 " : %" PRIu64 " octets\n", (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header), (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_);

            u64_lcl_cnt = 0;
            while((uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_ - u64_lcl_cnt >= 16)
                {
                ft_printf("%.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x %.2x%.2x%.2x%.2x\n", ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 1], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 2], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 3], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 4], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 5], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 6], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 7], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 8], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 9], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 10], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 11], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 12], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 13], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 14], ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt + 15]);

                u64_lcl_cnt += 16;
                }

            while(u64_lcl_cnt < (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_)
                {
                ft_printf("%.2x", ((uint8_t *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header)))[u64_lcl_cnt]);

                if((u64_lcl_cnt % 4) == 3)
                    ft_printf(" ");

                if((u64_lcl_cnt % 16) == 15)
                    ft_printf("\n");

                /**
                * Checking for overflow
                */
                if(u64_lcl_cnt < UINT64_MAX)
                    {
                    u64_lcl_cnt++;
                    }
                else
                    {
                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return a failure to indicate the counter variable overflow
                    */
                    return;
                    }
                }
            ft_printf("\n");

            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + ptr_sstc_lcl_actual_chunk->u64_data_length_;
            }
        else
            {
            /**
            * Treat the case when the actual chunk is free
            */
            }

        u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header));

        /**
        * Getting the address of the next chunk of the heap
        */
        ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
        }

    if(ptr_u64_pssd_total_allocated_memory != NULL)
        {
        (*ptr_u64_pssd_total_allocated_memory) = u64_lcl_total_allocated_memory;
        }
    }

/**
* the coresponding heap list mutex must be hold when entering the function
* ptr_u64_pssd_total_allocated_memory can be NULL
*/
void Fv__display_heap(void *ptr_vd_pssd_heap, uint64_t *ptr_u64_pssd_total_allocated_memory)
    {
    /**
    * Assertion of argument
    */

    /**
    * Check if the heap is correctly pointing passed as an argument of the function
    */
    if(ptr_vd_pssd_heap == NULL)
        {
        /**
        * Treat the case when the heap is not correctly pointing passed as an argument of the function
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the heap is not correctly pointing passed as an argument of the function\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the heap is not correctly pointing passed as an argument of the function
        */
        return;
        }
    else
        {
        /**
        * Treat the case when the heap is correctly pointing passed as an argument of the function
        */
        }

    /**
    * Creation of local variable
    */
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    uint64_t                  u64_lcl_number_of_allocated_chunk;
    uint64_t                  u64_lcl_number_of_free_chunk;
    uint64_t                  u64_lcl_position_in_heap;
    uint64_t                  u64_lcl_total_allocated_memory;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk         = NULL;
    u64_lcl_number_of_allocated_chunk = 0;
    u64_lcl_number_of_free_chunk      = 0;
    u64_lcl_position_in_heap          = 0;
    u64_lcl_total_allocated_memory    = 0;

    ft_printf("\nHEAP %p, size: %" PRIu64 ", free: %" PRIu64 "\n\n", ptr_vd_pssd_heap, ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_, ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_number_of_free_space_);

    /**
    * Getting the address of the first chunk of the heap
    */
    u64_lcl_position_in_heap  = sizeof(struct sstc_heap_header);
    ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);

    u64_lcl_number_of_allocated_chunk = 0;
    u64_lcl_number_of_free_chunk      = 0;
    while(u64_lcl_position_in_heap < ((uint64_t) ((struct sstc_heap_header *) ptr_vd_pssd_heap)->u64_length_of_data_ + sizeof(struct sstc_heap_header)))
        {
        /**
        * Check if the actual chunk is not free
        */
        if(ptr_sstc_lcl_actual_chunk->u8_data_free_flag_ == FALSE)
            {
            /**
            * Treat the case when the actual chunk is not free
            */

            ft_printf("ALLOCATED: 0x%" PRIX64 " - 0x%" PRIX64 " : %" PRIu64 " octets  prev %" PRIu64 "\n", (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header), (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_previous_data_length_);

            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + ptr_sstc_lcl_actual_chunk->u64_data_length_;

            /**
            * Checking for overflow
            */
            if(u64_lcl_number_of_allocated_chunk < UINT64_MAX)
                {
                u64_lcl_number_of_allocated_chunk++;
                }
            else
                {
                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return a failure to indicate the counter variable overflow
                */ 
                return;
                } 
            }
        else
            {
            /**
            * Treat the case when the actual chunk is free
            */

            ft_printf("FREE     : 0x%" PRIX64 " - 0x%" PRIX64 " : %" PRIu64 " octets  prev %" PRIu64 "\n", (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header), (uintptr_t) ptr_vd_pssd_heap + u64_lcl_position_in_heap + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_data_length_, (uint64_t) ptr_sstc_lcl_actual_chunk->u64_previous_data_length_);

            /**
            * Checking for overflow
            */
            if(u64_lcl_number_of_free_chunk < UINT64_MAX)
                {
                u64_lcl_number_of_free_chunk++;
                }
            else
                {
                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return a failure to indicate the counter variable overflow
                */ 
                return;
                } 
            }

        u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header));

        /**
        * Getting the address of the next chunk of the heap
        */
        ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr_vd_pssd_heap + u64_lcl_position_in_heap);
        }

    ft_printf("\nNB CHUNK allocated: %" PRIu64 ", free: %" PRIu64 "\n\n", u64_lcl_number_of_allocated_chunk, u64_lcl_number_of_free_chunk);

    if(ptr_u64_pssd_total_allocated_memory != NULL)
        {
        (*ptr_u64_pssd_total_allocated_memory) = u64_lcl_total_allocated_memory;
        }
    }

void Fv__custom_show_alloc_mem(void)
    {
    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t                  s32_lcl_return_from_function;
#endif
    struct sstc_heap_header *ptr_sstc_lcl_actual_heap;
    uint64_t                 u64_lcl_tmp_allocated_memory;
    uint64_t                 u64_lcl_total_allocated_memory;
    uint8_t                  u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_heap       = NULL;
#ifdef THREAD_SAFE
    s32_lcl_return_from_function   = -1;
#endif
    u64_lcl_tmp_allocated_memory   = 0;
    u64_lcl_total_allocated_memory = 0;
    u8_lcl_return_from_function    = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

#ifdef THREAD_SAFE
    /**
    * Locking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }
#endif

    ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_;
    while(ptr_sstc_lcl_actual_heap != NULL)
        {
        ft_printf("TINY : 0x%lX\n", (uintptr_t) ptr_sstc_lcl_actual_heap);
        (void) Fv__display_heap((void *) ptr_sstc_lcl_actual_heap, &u64_lcl_tmp_allocated_memory);

        if(u64_lcl_total_allocated_memory <= (UINT64_MAX - u64_lcl_tmp_allocated_memory))
            {
            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + u64_lcl_tmp_allocated_memory;
            }

        ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
        }

    ft_printf("\n");

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }
#endif

    ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_small_list_;
    while(ptr_sstc_lcl_actual_heap != NULL)
        {
        ft_printf("SMALL : 0x%lX\n", (uintptr_t) ptr_sstc_lcl_actual_heap);
        (void) Fv__display_heap((void *) ptr_sstc_lcl_actual_heap, &u64_lcl_tmp_allocated_memory);

        if(u64_lcl_total_allocated_memory <= (UINT64_MAX - u64_lcl_tmp_allocated_memory))
            {
            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + u64_lcl_tmp_allocated_memory;
            }

        ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
        }

    ft_printf("\n");

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_large_list_;
    while(ptr_sstc_lcl_actual_heap != NULL)
        {
        ft_printf("LARGE : 0x%lX\n", (uintptr_t) ptr_sstc_lcl_actual_heap);
        (void) Fv__display_heap((void *) ptr_sstc_lcl_actual_heap, &u64_lcl_tmp_allocated_memory);

        if(u64_lcl_total_allocated_memory <= (UINT64_MAX - u64_lcl_tmp_allocated_memory))
            {
            u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + u64_lcl_tmp_allocated_memory;
            }

        ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    ft_printf("Total : %" PRIu64 " octets\n", u64_lcl_total_allocated_memory);
    }

void *malloc(size_t size)
    {
    /**
    * Creation of local variable
    */
    int32_t                  s32_lcl_return_from_function;
    struct rlimit            estc_lcl_resource_limit;
    struct sstc_heap_header *ptr_sstc_lcl_actual_heap;
    uint8_t                  u8_lcl_return_from_function;
    void                    *ptr_vd_lcl_new_allocated_chunk;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_heap       = NULL;
    ptr_vd_lcl_new_allocated_chunk = NULL;
    s32_lcl_return_from_function   = -1;
    u8_lcl_return_from_function    = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

    if(size == 0)
        return (NULL);

    /**
    * Getting the resource limit of the virtual memory of the actual process
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = getrlimit(RLIMIT_AS, &estc_lcl_resource_limit);

    /**
    * Check if function to get the resource limit of the virtual memory of the actual process succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to get the resource limit of the virtual memory of the actual process failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get the resource limit of the virtual memory of the actual process failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get the resource limit of the virtual memory of the actual process failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to get the resource limit of the virtual memory of the actual process succeeded
        */
        }

    /**
    * Check if if the size to allocate is bigger than the maximun
    */
    if(size > estc_lcl_resource_limit.rlim_cur)
        {
        /**
        * Treat the case when if the size to allocate is bigger than the maximun
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    if the size to allocate is bigger than the maximun\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate if the size to allocate is bigger than the maximun
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when if the size to allocate is not bigger than the maximun
        */
        }

    /**
    * Getting the resource limit of the data segment of the actual process
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = getrlimit(RLIMIT_DATA, &estc_lcl_resource_limit);

    /**
    * Check if function to get the resource limit of the data segment of the actual process succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to get the resource limit of the data segment of the actual process failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get the resource limit of the data segment of the actual process failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get the resource limit of the data segment of the actual process failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to get the resource limit of the data segment of the actual process succeeded
        */
        }

    /**
    * Check if if the size to allocate is bigger than the maximun
    */
    if(size > estc_lcl_resource_limit.rlim_cur)
        {
        /**
        * Treat the case when if the size to allocate is bigger than the maximun
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    if the size to allocate is bigger than the maximun\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate if the size to allocate is bigger than the maximun
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when if the size to allocate is not bigger than the maximun
        */
        }

    /**
    * Selecte the alloc size
    */
    if(size <= cstc_glbl_malloc_data.u64_tiny_alloc_max_)
        {
        /**
        * Select the tiny alloc size
        */

#ifdef THREAD_SAFE
        /**
        * Locking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            }
#endif

        /**
        * Check if the list of tiny heap is empty
        */
        if(cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_ == NULL)
            {
            /**
            * Treat the case when the list of tiny heap is empty
            */

            /**
            * Generating new tiny heap
            */
            u8_lcl_return_from_function = RETURN_FAILURE;
            u8_lcl_return_from_function = Fu8__generate_new_tiny_heap_in_structure_malloc_data(&cstc_glbl_malloc_data);

            /**
            * Check if function to generate new tiny heap succeeded
            */
            if(u8_lcl_return_from_function != RETURN_SUCCESS)
                {
                /**
                * Treat the case when the function to generate new tiny heap failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to generate new tiny heap failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate the function to generate new tiny heap failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to generate new tiny heap succeeded
                */
                }

            /**
            * Searching and allocate a free chunk in the new created heap
            */
            u8_lcl_return_from_function = RETURN_FAILURE;
            u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) cstc_glbl_malloc_data.ptr_sstc_last_heap_tiny_, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

            /**
            * Check if function to search and allocate a free chunk in the new created heap succeeded
            */
            if(u8_lcl_return_from_function != RETURN_SUCCESS)
                {
                /**
                * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                */
                }

            /**
            * Check if no free chunk was found in the new created heap
            */
            if(ptr_vd_lcl_new_allocated_chunk == NULL)
                {
                /**
                * Treat the case when no free chunk was found in the new created heap
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    no free chunk was found in the new created heap\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate no free chunk was found in the new created heap
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when free chunk is found and is allocated in the new created heap
                */
                }
            }
        else
            {
            /**
            * Treat the case when the list of tiny heap is not empty
            */

            /**
            * Go through all the tiny heap to find free space to allocate
            */
            ptr_vd_lcl_new_allocated_chunk = NULL;
            ptr_sstc_lcl_actual_heap       = cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_;
            while((ptr_sstc_lcl_actual_heap != NULL) && (ptr_vd_lcl_new_allocated_chunk == NULL))
                {
                /**
                * Searching and allocate a free chunk in the new created heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) ptr_sstc_lcl_actual_heap, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

                /**
                * Check if function to search and allocate a free chunk in the new created heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                    */
                    }

                /**
                * Going to the next tiny heap
                */
                ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
                }

            /**
            * Check if no free chunk was found in all the tiny heap
            */
            if(ptr_vd_lcl_new_allocated_chunk == NULL)
                {
                /**
                * Treat the case when no free chunk was found in all the tiny heap
                */

                /**
                * Generating new tiny heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__generate_new_tiny_heap_in_structure_malloc_data(&cstc_glbl_malloc_data);

                /**
                * Check if function to generate new tiny heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to generate new tiny heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to generate new tiny heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to generate new tiny heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to generate new tiny heap succeeded
                    */
                    }

                /**
                * Searching and allocate a free chunk in the new created heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) cstc_glbl_malloc_data.ptr_sstc_last_heap_tiny_, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

                /**
                * Check if function to search and allocate a free chunk in the new created heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                    */
                    }

                /**
                * Check if no free chunk was found in the new created heap
                */
                if(ptr_vd_lcl_new_allocated_chunk == NULL)
                    {
                    /**
                    * Treat the case when no free chunk was found in the new created heap
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    no free chunk was found in the new created heap\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate no free chunk was found in the new created heap
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when free chunk is found and is allocated in the new created heap
                    */
                    }
                }
            else
                {
                /**
                * Treat the case when new chunk was allacted in an already created tiny heap
                */
                }
            }

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            }
#endif

        return (ptr_vd_lcl_new_allocated_chunk + sizeof(struct sstc_chunk_header));
        }
    else if(size <= cstc_glbl_malloc_data.u64_small_alloc_max_)
        {
        /**
        * Select the small alloc size
        */

#ifdef THREAD_SAFE
        /**
        * Locking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = 1;
        s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
            */
            }
#endif

        /**
        * Check if the list of small heap is empty
        */
        if(cstc_glbl_malloc_data.ptr_sstc_heap_small_list_ == NULL)
            {
            /**
            * Treat the case when the list of small heap is empty
            */

            /**
            * Generating new small heap
            */
            u8_lcl_return_from_function = RETURN_FAILURE;
            u8_lcl_return_from_function = Fu8__generate_new_small_heap_in_structure_malloc_data(&cstc_glbl_malloc_data);

            /**
            * Check if function to generate new small heap succeeded
            */
            if(u8_lcl_return_from_function != RETURN_SUCCESS)
                {
                /**
                * Treat the case when the function to generate new small heap failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to generate new small heap failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the small heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                /**
                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate the function to generate new small heap failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to generate new small heap succeeded
                */
                }

            /**
            * Searching and allocate a free chunk in the new created heap
            */
            u8_lcl_return_from_function = RETURN_FAILURE;
            u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) cstc_glbl_malloc_data.ptr_sstc_last_heap_small_, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

            /**
            * Check if function to search and allocate a free chunk in the new created heap succeeded
            */
            if(u8_lcl_return_from_function != RETURN_SUCCESS)
                {
                /**
                * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the small heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                /**
                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                */
                }

            /**
            * Check if no free chunk was found in the new created heap
            */
            if(ptr_vd_lcl_new_allocated_chunk == NULL)
                {
                /**
                * Treat the case when no free chunk was found in the new created heap
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    no free chunk was found in the new created heap\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the small heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                /**
                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate no free chunk was found in the new created heap
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when free chunk is found and is allocated in the new created heap
                */
                }
            }
        else
            {
            /**
            * Treat the case when the list of small heap is not empty
            */

            /**
            * Go through all the small heap to find free space to allocate
            */
            ptr_vd_lcl_new_allocated_chunk = NULL;
            ptr_sstc_lcl_actual_heap       = cstc_glbl_malloc_data.ptr_sstc_heap_small_list_;
            while((ptr_sstc_lcl_actual_heap != NULL) && (ptr_vd_lcl_new_allocated_chunk == NULL))
                {
                /**
                * Searching and allocate a free chunk in the new created heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) ptr_sstc_lcl_actual_heap, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

                /**
                * Check if function to search and allocate a free chunk in the new created heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                    */
                    }

                /**
                * Going to the next small heap
                */
                ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
                }

            /**
            * Check if no free chunk was found in all the small heap
            */
            if(ptr_vd_lcl_new_allocated_chunk == NULL)
                {
                /**
                * Treat the case when no free chunk was found in all the small heap
                */

                /**
                * Generating new small heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__generate_new_small_heap_in_structure_malloc_data(&cstc_glbl_malloc_data);

                /**
                * Check if function to generate new small heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to generate new small heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to generate new small heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to generate new small heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to generate new small heap succeeded
                    */
                    }

                /**
                * Searching and allocate a free chunk in the new created heap
                */
                u8_lcl_return_from_function = RETURN_FAILURE;
                u8_lcl_return_from_function = Fu8__alloc_chunk_in_heap((void *) cstc_glbl_malloc_data.ptr_sstc_last_heap_small_, (uint64_t) size, &ptr_vd_lcl_new_allocated_chunk);

                /**
                * Check if function to search and allocate a free chunk in the new created heap succeeded
                */
                if(u8_lcl_return_from_function != RETURN_SUCCESS)
                    {
                    /**
                    * Treat the case when the function to search and allocate a free chunk in the new created heap failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to search and allocate a free chunk in the new created heap failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate the function to search and allocate a free chunk in the new created heap failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to search and allocate a free chunk in the new created heap succeeded
                    */
                    }

                /**
                * Check if no free chunk was found in the new created heap
                */
                if(ptr_vd_lcl_new_allocated_chunk == NULL)
                    {
                    /**
                    * Treat the case when no free chunk was found in the new created heap
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    no free chunk was found in the new created heap\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    /**
                    * Return failure to indicate no free chunk was found in the new created heap
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when free chunk is found and is allocated in the new created heap
                    */
                    }
                }
            else
                {
                /**
                * Treat the case when new chunk was allacted in an already created small heap
                */
                }
            }

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            }
#endif

        return (ptr_vd_lcl_new_allocated_chunk + sizeof(struct sstc_chunk_header));
        }
    else
        {
        /**
        * Select the large alloc size
        */

#ifdef THREAD_SAFE
        /**
        * Locking the mutex to access the large heap list in the structure malloc data
        */
        s32_lcl_return_from_function = 1;
        s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

        /**
        * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
            */
            }
#endif

        /**
        * Generating new large heap
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__generate_new_large_heap_in_structure_malloc_data(&cstc_glbl_malloc_data, (uint64_t) size);

        /**
        * Check if function to generate new large heap succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to generate new large heap failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to generate new large heap failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

#ifdef THREAD_SAFE
            /**
            * Unlocking the mutex to access the large heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

            /**
            * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                */
                } 
#endif

            /**
            * Return failure to indicate the function to generate new large heap failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to generate new large heap succeeded
            */
            }

        /**
        * Getting the address of the new allocated chunk
        */
        ptr_vd_lcl_new_allocated_chunk = ((void *) cstc_glbl_malloc_data.ptr_sstc_last_heap_large_) + sizeof(struct sstc_heap_header);

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex to access the large heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

        /**
        * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
            */
            }
#endif

        return (ptr_vd_lcl_new_allocated_chunk + sizeof(struct sstc_chunk_header));
        }

    return (NULL);
    }

void free(void *ptr)
    {
    /**
    * Creation of local variable
    */
    int32_t                   s32_lcl_return_from_function;
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_next_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_passed_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_previous_chunk;
    struct sstc_heap_header  *ptr_sstc_lcl_actual_heap;
    uint64_t                  u64_lcl_freed_memory;
    uint64_t                  u64_lcl_position_in_heap;
    uint8_t                   u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk    = NULL;
    ptr_sstc_lcl_actual_heap     = NULL;
    ptr_sstc_lcl_next_chunk      = NULL;
    ptr_sstc_lcl_passed_chunk    = NULL;
    ptr_sstc_lcl_previous_chunk  = NULL;
    s32_lcl_return_from_function = -1;
    u64_lcl_freed_memory         = 0;
    u64_lcl_position_in_heap     = 0;
    u8_lcl_return_from_function  = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

    if(ptr == NULL)
        return;

    ptr_sstc_lcl_passed_chunk = (struct sstc_chunk_header *) (ptr - sizeof(struct sstc_chunk_header));

    /**
    * Check if the passed chunk is not valid
    */
    if((ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ != ptr_sstc_lcl_passed_chunk->u64_data_length_) || (ptr_sstc_lcl_passed_chunk->u64_previous_data_length_redundancy_ != ptr_sstc_lcl_passed_chunk->u64_previous_data_length_) || (ptr_sstc_lcl_passed_chunk->u8_check_redundancy_1_ != TRUE) || (ptr_sstc_lcl_passed_chunk->u8_check_redundancy_2_ != TRUE))
        {
        /**
        * Treat the case when the passed chunk is not valid
        */

        /**
        * Return failure to indicate the passed chunk is not valid
        */
        return;
        }
    else
        {
        /**
        * Treat the case when the passed chunk is valid
        */
        }

    /**
    * Check if the passed chunk is already free
    */
    if(ptr_sstc_lcl_passed_chunk->u8_data_free_flag_ == TRUE)
        {
        /**
        * Treat the case when the passed chunk is already free
        */

        return;
        }
    else
        {
        /**
        * Treat the case when the passed chunk is not free as expected
        */
        }

#ifdef THREAD_SAFE
    /**
    * Locking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    /**
    * Check if the passed chunk is in a large heap
    */
    if((ptr_sstc_lcl_passed_chunk->u8_previous_data_heap_header_flag_ == TRUE) && (ptr_sstc_lcl_passed_chunk->u64_previous_data_length_ == LARGE_HEAP_MAGIC_NUMBER))
        {
        /**
        * Treat the case when the passed chunk is in a large heap
        */

        ptr_sstc_lcl_passed_chunk->u8_data_free_flag_ = TRUE;

        ptr_sstc_lcl_actual_heap = ((struct sstc_heap_header *) (ptr - sizeof(struct sstc_chunk_header) - sizeof(struct sstc_heap_header)));

        if(ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_ != NULL)
            {
            ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_->ptr_sstc_next_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        if(ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_ != NULL)
            {
            ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_->ptr_sstc_previous_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
            }

        if(ptr_sstc_lcl_actual_heap == cstc_glbl_malloc_data.ptr_sstc_heap_large_list_)
            {
            cstc_glbl_malloc_data.ptr_sstc_heap_large_list_ = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        if(ptr_sstc_lcl_actual_heap == cstc_glbl_malloc_data.ptr_sstc_last_heap_large_)
            {
            cstc_glbl_malloc_data.ptr_sstc_last_heap_large_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
            }

        if(cstc_glbl_malloc_data.u64_number_of_large_heap_ != 0)
            {
            cstc_glbl_malloc_data.u64_number_of_large_heap_--;
            }

        /**
        * Freeing the actual large heap
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = munmap((void *) ptr_sstc_lcl_actual_heap, ptr_sstc_lcl_actual_heap->u64_length_of_data_ + sizeof(struct sstc_heap_header));

        /**
        * Check if function to free the actual large heap succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to free the actual large heap failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to free the actual large heap failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

#ifdef THREAD_SAFE
            /**
            * Unlocking the mutex to access the large heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

            /**
            * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Unlocking the mutex to access the small heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                /**
                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 
#endif

            /**
            * Return failure to indicate the function to free the actual large heap failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to free the actual large heap succeeded
            */
            }

        return;
        }
    else
        {
        /**
        * Treat the case when the passed chunk is not in a large heap
        */

        /**
        * Getting the actual heap header
        */
        ptr_sstc_lcl_actual_heap  = NULL;
        ptr_sstc_lcl_actual_chunk = ptr_sstc_lcl_passed_chunk;
        u64_lcl_position_in_heap  = sizeof(struct sstc_chunk_header);
        while(ptr_sstc_lcl_actual_chunk->u8_previous_data_heap_header_flag_ == FALSE)
            {
            u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_previous_data_length_ + sizeof(struct sstc_chunk_header));

            ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr - u64_lcl_position_in_heap);
            }

        ptr_sstc_lcl_actual_heap = (struct sstc_heap_header *) (ptr - u64_lcl_position_in_heap - sizeof(struct sstc_heap_header));

        if(ptr_sstc_lcl_passed_chunk->u8_previous_data_heap_header_flag_ == FALSE)
            {
            ptr_sstc_lcl_previous_chunk = (struct sstc_chunk_header *) (ptr - sizeof(struct sstc_chunk_header) - ptr_sstc_lcl_passed_chunk->u64_previous_data_length_ - sizeof(struct sstc_chunk_header));
            }
        else
            {
            ptr_sstc_lcl_previous_chunk = NULL;
            }

        if((uintptr_t) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
            {
            ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_);
            }
        else
            {
            ptr_sstc_lcl_next_chunk = NULL;
            }

        /**
        * Check if the passed chunk can not be defrag
        */
        if(((ptr_sstc_lcl_previous_chunk == NULL) || (ptr_sstc_lcl_previous_chunk->u8_data_free_flag_ == FALSE)) && ((ptr_sstc_lcl_next_chunk == NULL) || (ptr_sstc_lcl_next_chunk->u8_data_free_flag_ == FALSE)))
            {
            /**
            * Treat the case when the passed chunk can not be defrag
            */

            /**
            * Freeing the passed chunk and set the new free space in the actual heap
            */
            ptr_sstc_lcl_passed_chunk->u8_data_free_flag_        = TRUE;

            ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += ptr_sstc_lcl_passed_chunk->u64_data_length_;
            }
        else
            {
            /**
            * Treat the case when the passed chunk can be defrag
            */

            u64_lcl_freed_memory = ptr_sstc_lcl_passed_chunk->u64_data_length_;

            /**
            * Check if the next chunk of the passed chunk is free and can be defragmented
            */
            if((ptr_sstc_lcl_next_chunk != NULL) && (ptr_sstc_lcl_next_chunk->u8_data_free_flag_ != FALSE))
                {
                /**
                * Treat the case when the next chunk of the passed chunk is free and can be defragmented
                */

                u64_lcl_freed_memory += sizeof(struct sstc_chunk_header);

                ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = ptr_sstc_lcl_passed_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_;
                ptr_sstc_lcl_passed_chunk->u64_data_length_            = ptr_sstc_lcl_passed_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_;

                if((uintptr_t) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                    {
                    /**
                    * Setting the length of the previous data in the new next chunk
                    */
                    ptr_sstc_lcl_next_chunk                                       = (struct sstc_chunk_header *) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_);
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_            = ptr_sstc_lcl_passed_chunk->u64_data_length_;
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_passed_chunk->u64_data_length_;
                    ptr_sstc_lcl_next_chunk->u8_previous_data_heap_header_flag_   = FALSE;
                    }
                }
            else
                {
                /**
                * Treat the case when the next chunk of the passed chunk is not free and can not be defragmented
                */
                }

            /**
            * Check if the previous chunk of the passed chunk is free and can be defragmented
            */
            if((ptr_sstc_lcl_previous_chunk != NULL) && (ptr_sstc_lcl_previous_chunk->u8_data_free_flag_ != FALSE))
                {
                /**
                * Treat the case when the previous chunk of the passed chunk is free and can be defragmented
                */

                u64_lcl_freed_memory += sizeof(struct sstc_chunk_header);

                ptr_sstc_lcl_previous_chunk->u64_data_length_redundancy_ = ptr_sstc_lcl_previous_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_passed_chunk->u64_data_length_;
                ptr_sstc_lcl_previous_chunk->u64_data_length_            = ptr_sstc_lcl_previous_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_passed_chunk->u64_data_length_;
                }
            else
                {
                /**
                * Treat the case when the previous chunk of the passed chunk is not free and can not be defragmented
                */
                }

            /**
            * Freeing the passed chunk and set the new free space in the actual heap
            */
            ptr_sstc_lcl_passed_chunk->u8_data_free_flag_        = TRUE;

            ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += u64_lcl_freed_memory;
            }

        /**
        * Check if the actual heap is totaly free
        */
        if(ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ >= (ptr_sstc_lcl_actual_heap->u64_length_of_data_ - sizeof(struct sstc_chunk_header)))
            {
            /**
            * Treat the case when the actual heap is totaly free
            */

            /**
            * Check if the actual heap is not in the tiny list and not in the small list
            */
            if((ptr_sstc_lcl_actual_heap->u64_tiny_status_ == FALSE) && (ptr_sstc_lcl_actual_heap->u64_small_status_ == FALSE))
                {
                /**
                * Treat the case when the actual heap is not in the tiny list and not in the small list
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    the actual heap is not in the tiny list and not in the small list\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

#ifdef THREAD_SAFE
                /**
                * Unlocking the mutex to access the large heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

                /**
                * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Unlocking the mutex to access the tiny heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                        /**
                        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 

                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Unlocking the mutex to access the small heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                /**
                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return;
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 
#endif

                /**
                * Return failure to indicate the actual heap is not in the tiny list and not in the small list
                */
                return;
                }
            else
                {
                /**
                * Treat the case when the actual heap is in the tiny list or in the small list
                */
                }

            if(ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_ != NULL)
                {
                ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_->ptr_sstc_next_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
                }

            if(ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_ != NULL)
                {
                ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_->ptr_sstc_previous_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
                }

            if(ptr_sstc_lcl_actual_heap->u64_tiny_status_ == TRUE)
                {
                if(ptr_sstc_lcl_actual_heap != cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_)
                    {
                    if(ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_ != NULL)
                        {
                        ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_->ptr_sstc_next_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
                        }

                    if(ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_ != NULL)
                        {
                        ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_->ptr_sstc_previous_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
                        }

                    if(ptr_sstc_lcl_actual_heap == cstc_glbl_malloc_data.ptr_sstc_last_heap_tiny_)
                        {
                        cstc_glbl_malloc_data.ptr_sstc_last_heap_tiny_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
                        }

                    cstc_glbl_malloc_data.u64_number_of_tiny_heap_--;

                    /**
                    * Freeing the actual large heap
                    */
                    ft_printf("MUUUUUNNNNNMAAAAP %" PRIu64 "\n", ptr_sstc_lcl_actual_heap->u64_length_of_data_ + sizeof(struct sstc_heap_header));
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = munmap((void *) ptr_sstc_lcl_actual_heap, ptr_sstc_lcl_actual_heap->u64_length_of_data_ + sizeof(struct sstc_heap_header));

                    /**
                    * Check if function to free the actual large heap succeeded
                    */
                    if(u8_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to free the actual large heap failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to free the actual large heap failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

#ifdef THREAD_SAFE
                        /**
                        * Unlocking the mutex to access the large heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

                        /**
                        * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Unlocking the mutex to access the small heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                            /**
                            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                                */
                                s32_lcl_return_from_function = -1;
                                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                                /**
                                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                                */
                                if(s32_lcl_return_from_function != 0)
                                    {
                                    /**
                                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                    */

                                    #ifdef DEVELOPEMENT
                                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                    #endif

                                    #ifdef DEMO
                                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                    #endif

                                    #ifdef PRODUCTION
                                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                    #endif

                                    /**
                                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                    */
                                    return;
                                    }
                                else
                                    {
                                    /**
                                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                                    */
                                    } 

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Unlocking the mutex to access the tiny heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                            /**
                            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Unlocking the mutex to access the small heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                        /**
                        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Unlocking the mutex to access the tiny heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                            /**
                            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Unlocking the mutex to access the tiny heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                        /**
                        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                            */
                            } 
#endif

                        /**
                        * Return failure to indicate the function to free the actual large heap failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to free the actual large heap succeeded
                        */
                        }
                    }
                }
            else
                {
                if(ptr_sstc_lcl_actual_heap != cstc_glbl_malloc_data.ptr_sstc_heap_small_list_)
                    {
                    if(ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_ != NULL)
                        {
                        ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_->ptr_sstc_next_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
                        }

                    if(ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_ != NULL)
                        {
                        ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_->ptr_sstc_previous_heap_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
                        }

                    if(ptr_sstc_lcl_actual_heap == cstc_glbl_malloc_data.ptr_sstc_last_heap_small_)
                        {
                        cstc_glbl_malloc_data.ptr_sstc_last_heap_small_ = ptr_sstc_lcl_actual_heap->ptr_sstc_previous_heap_;
                        }

                    cstc_glbl_malloc_data.u64_number_of_small_heap_--;

                    /**
                    * Freeing the actual large heap
                    */
                    ft_printf("MUUUUUNNNNNMAAAAP %" PRIu64 "\n", ptr_sstc_lcl_actual_heap->u64_length_of_data_ + sizeof(struct sstc_heap_header));
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = munmap((void *) ptr_sstc_lcl_actual_heap, ptr_sstc_lcl_actual_heap->u64_length_of_data_ + sizeof(struct sstc_heap_header));

                    /**
                    * Check if function to free the actual large heap succeeded
                    */
                    if(u8_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to free the actual large heap failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to free the actual large heap failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

#ifdef THREAD_SAFE
                        /**
                        * Unlocking the mutex to access the large heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

                        /**
                        * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Unlocking the mutex to access the small heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                            /**
                            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Unlocking the mutex to access the small heap list in the structure malloc data
                                */
                                s32_lcl_return_from_function = -1;
                                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                                /**
                                * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                */
                                if(s32_lcl_return_from_function != 0)
                                    {
                                    /**
                                    * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                    */

                                    #ifdef DEVELOPEMENT
                                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                    #endif

                                    #ifdef DEMO
                                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                    #endif

                                    #ifdef PRODUCTION
                                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                    #endif

                                    /**
                                    * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                    */
                                    return;
                                    }
                                else
                                    {
                                    /**
                                    * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                    */
                                    } 

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Unlocking the mutex to access the small heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                            /**
                            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Unlocking the mutex to access the small heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                        /**
                        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Unlocking the mutex to access the small heap list in the structure malloc data
                            */
                            s32_lcl_return_from_function = -1;
                            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                            /**
                            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            if(s32_lcl_return_from_function != 0)
                                {
                                /**
                                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */

                                #ifdef DEVELOPEMENT
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                                #endif

                                #ifdef DEMO
                                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                                #endif

                                #ifdef PRODUCTION
                                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                                #endif

                                /**
                                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                                */
                                return;
                                }
                            else
                                {
                                /**
                                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                                */
                                } 

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Unlocking the mutex to access the small heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                        /**
                        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                            */
                            return;
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                            */
                            } 
#endif

                        /**
                        * Return failure to indicate the function to free the actual large heap failed
                        */
                        return;
                        }
                    else
                        {
                        /**
                        * Treat the case when function to free the actual large heap succeeded
                        */
                        }
                    }
                }
            }
        else
            {
            /**
            * Treat the case when the actual heap is not totaly free
            */
            }
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 
#endif
    }

void *realloc(void *ptr, size_t size)
    {
    /**
    * Creation of local variable
    */
    int32_t                   s32_lcl_return_from_function;
    struct rlimit             estc_lcl_resource_limit;
    struct sstc_chunk_header *ptr_sstc_lcl_actual_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_chunk_to_change_previous_size;
    struct sstc_chunk_header *ptr_sstc_lcl_next_chunk;
    struct sstc_chunk_header *ptr_sstc_lcl_passed_chunk;
    struct sstc_heap_header  *ptr_sstc_lcl_actual_heap;
    uint64_t                  u64_lcl_cnt;
    uint64_t                  u64_lcl_position_in_heap;
    uint8_t                   u8_lcl_return_from_function;
    void                     *ptr_vd_lcl_tmp;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_chunk                  = NULL;
    ptr_sstc_lcl_actual_heap                   = NULL;
    ptr_sstc_lcl_chunk_to_change_previous_size = NULL;
    ptr_sstc_lcl_next_chunk                    = NULL;
    ptr_sstc_lcl_passed_chunk                  = NULL;
    ptr_vd_lcl_tmp                             = NULL;
    s32_lcl_return_from_function               = -1;
    u64_lcl_cnt                                = 0;
    u64_lcl_position_in_heap                   = 0;
    u8_lcl_return_from_function                = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

    if(ptr == NULL)
        return (malloc(size));

    if(size == 0)
        {
        (void) free(ptr);
        return (NULL);
        }

    /**
    * Getting the resource limit of the virtual memory of the actual process
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = getrlimit(RLIMIT_AS, &estc_lcl_resource_limit);

    /**
    * Check if function to get the resource limit of the virtual memory of the actual process succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to get the resource limit of the virtual memory of the actual process failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get the resource limit of the virtual memory of the actual process failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get the resource limit of the virtual memory of the actual process failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to get the resource limit of the virtual memory of the actual process succeeded
        */
        }

    /**
    * Check if if the size to allocate is bigger than the maximun
    */
    if(size > estc_lcl_resource_limit.rlim_cur)
        {
        /**
        * Treat the case when if the size to allocate is bigger than the maximun
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    if the size to allocate is bigger than the maximun\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate if the size to allocate is bigger than the maximun
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when if the size to allocate is not bigger than the maximun
        */
        }

    /**
    * Getting the resource limit of the data segment of the actual process
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = getrlimit(RLIMIT_DATA, &estc_lcl_resource_limit);

    /**
    * Check if function to get the resource limit of the data segment of the actual process succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to get the resource limit of the data segment of the actual process failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to get the resource limit of the data segment of the actual process failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to get the resource limit of the data segment of the actual process failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to get the resource limit of the data segment of the actual process succeeded
        */
        }

    /**
    * Check if if the size to allocate is bigger than the maximun
    */
    if(size > estc_lcl_resource_limit.rlim_cur)
        {
        /**
        * Treat the case when if the size to allocate is bigger than the maximun
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    if the size to allocate is bigger than the maximun\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate if the size to allocate is bigger than the maximun
        */
        return (RETURN_FAILURE);
        }
    else
        {
        /**
        * Treat the case when if the size to allocate is not bigger than the maximun
        */
        }

#ifdef THREAD_SAFE
    /**
    * Locking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    /**
    * Getting the chunk header of the passed chunk
    */
    ptr_sstc_lcl_passed_chunk = (struct sstc_chunk_header *) (ptr - sizeof(struct sstc_chunk_header));

    /**
    * Check if the passed chunk is not valid
    */
    if((ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ != ptr_sstc_lcl_passed_chunk->u64_data_length_) || (ptr_sstc_lcl_passed_chunk->u64_previous_data_length_redundancy_ != ptr_sstc_lcl_passed_chunk->u64_previous_data_length_) || (ptr_sstc_lcl_passed_chunk->u8_check_redundancy_1_ != TRUE) || (ptr_sstc_lcl_passed_chunk->u8_check_redundancy_2_ != TRUE))
        {
        /**
        * Treat the case when the passed chunk is not valid
        */

        /**
        * Return failure to indicate the passed chunk is not valid
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when the passed chunk is valid
        */
        }

    /**
    * Check if the new size is equals to the actual size of the chunk
    */
    if((uint64_t) size == (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_)
        {
        /**
        * Treat the case when the new size is equals to the actual size of the chunk
        */

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex to access the large heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

        /**
        * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 
#endif

        return (ptr);
        }
    else
        {
        /**
        * Treat the case when the new size is not equals to the actual size of the chunk
        */
        }

    /**
    * Check if the new size of the allocation is a large allocation
    */
    if(size > cstc_glbl_malloc_data.u64_small_alloc_max_)
        {
        /**
        * Treat the case when the new size of the allocation is a large allocation
        */

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex to access the large heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

        /**
        * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 
#endif

        ptr_vd_lcl_tmp = malloc(size);

        if(ptr_vd_lcl_tmp != NULL)
            {
            /**
            * Copying the content of the previous chunk to the new allocated chunk
            */
            u64_lcl_cnt = 0;
            while((u64_lcl_cnt < (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_) && (u64_lcl_cnt < (uint64_t) size))
                {
                ((uint8_t *) ptr_vd_lcl_tmp)[u64_lcl_cnt] = ((uint8_t *) ptr)[u64_lcl_cnt];

                /**
                * Checking for overflow
                */
                if(u64_lcl_cnt < UINT64_MAX)
                    {
                    u64_lcl_cnt++;
                    }
                else
                    {
                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return a failure to indicate the counter variable overflow
                    */
                    return (NULL);
                    }
                }
            }

        (void) free(ptr);

        return (ptr_vd_lcl_tmp);
        }
    else
        {
        /**
        * Treat the case when the new size of the allocation is not a large allocation
        */
        } 

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        } 
#endif

    /**
    * Getting the actual heap header
    */
    ptr_sstc_lcl_actual_heap  = NULL;
    ptr_sstc_lcl_actual_chunk = ptr_sstc_lcl_passed_chunk;
    u64_lcl_position_in_heap  = sizeof(struct sstc_chunk_header);
    while(ptr_sstc_lcl_actual_chunk->u8_previous_data_heap_header_flag_ == FALSE)
        {
        u64_lcl_position_in_heap = u64_lcl_position_in_heap + (ptr_sstc_lcl_actual_chunk->u64_previous_data_length_ + sizeof(struct sstc_chunk_header));

        ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr - u64_lcl_position_in_heap);
        }

    ptr_sstc_lcl_actual_heap = (struct sstc_heap_header *) (ptr - u64_lcl_position_in_heap - sizeof(struct sstc_heap_header));

    /**
    * Check if the new size is in the same heap category of the actual chunk
    */
    if((((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ <= cstc_glbl_malloc_data.u64_tiny_alloc_max_) && (size <= cstc_glbl_malloc_data.u64_tiny_alloc_max_)) || ((((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ > cstc_glbl_malloc_data.u64_tiny_alloc_max_) && ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ <= cstc_glbl_malloc_data.u64_small_alloc_max_)) && (((uint64_t) size > cstc_glbl_malloc_data.u64_tiny_alloc_max_) && ((uint64_t) size <= cstc_glbl_malloc_data.u64_small_alloc_max_))))
        {
        /**
        * Treat the case when the new size is in the same heap category of the actual chunk
        */

        /**
        * Check if the passed chunk need to be reduce
        */
        if((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ > (uint64_t) size)
            {
            /**
            * Treat the case when the passed chunk need to be reduce
            */

            /**
            * Getting the next chunk
            */
            if((uintptr_t) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                {
                ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_);

                /**
                * Check if the next chunk is free
                */
                if(ptr_sstc_lcl_next_chunk->u8_data_free_flag_ == TRUE)
                    {
                    /**
                    * Treat the case when the next chunk is free
                    */

                    /**
                    * Getting the address of the new next chunk to create of the heap
                    */
                    ptr_sstc_lcl_actual_chunk = (struct sstc_chunk_header *) (ptr + size);

                    /**
                    * Setting the create of the next new chunk of the heap
                    */
                    ptr_sstc_lcl_actual_chunk->u64_data_length_redundancy_          = ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size) + (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;
                    ptr_sstc_lcl_actual_chunk->u8_check_redundancy_1_               = TRUE;
                    ptr_sstc_lcl_actual_chunk->u64_previous_data_length_redundancy_ = size;
                    ptr_sstc_lcl_actual_chunk->u8_check_redundancy_2_               = TRUE;

                    ptr_sstc_lcl_actual_chunk->u64_data_length_                   = ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size) + (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;
                    ptr_sstc_lcl_actual_chunk->u8_data_free_flag_                 = TRUE;
                    ptr_sstc_lcl_actual_chunk->u64_previous_data_length_          = size;
                    ptr_sstc_lcl_actual_chunk->u8_previous_data_heap_header_flag_ = FALSE;

                    /**
                    * Setting the size of the actual chunk in the heap
                    */
                    ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = size;
                    ptr_sstc_lcl_passed_chunk->u64_data_length_            = size;

                    ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size);

                    /**
                    * Check if the new created chunk is not the last chunk of the heap
                    */
                    if(((uintptr_t) ptr_sstc_lcl_actual_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                        {
                        /**
                        * Treat the case when the new created chunk is not the last chunk of the heap
                        */

                        /**
                        * Setting the size of the previous chunk of the next chunk of the new created chunk
                        */
                        ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) ((void *) ptr_sstc_lcl_actual_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_actual_chunk->u64_data_length_);
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_actual_chunk->u64_data_length_;
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_actual_chunk->u64_data_length_;
                        ptr_sstc_lcl_chunk_to_change_previous_size->u8_previous_data_heap_header_flag_   = FALSE;
                        }
                    else
                        {
                        /**
                        * Treat the case when the new created chunk is the last chunk of the heap
                        */
                        }
                    }
                else
                    {
                    /**
                    * Treat the case when the next chunk is not free
                    */

                    /**
                    * Check if the size after the new allocated chunk is bigger than a chunk header
                    */
                    if(((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size) > sizeof(struct sstc_chunk_header))
                        {
                        /**
                        * Treat the case when the size after the new allocated chunk is bigger than a chunk header
                        */

                        /**
                        * Getting the address of the new next chunk to create of the heap
                        */
                        ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + size);

                        /**
                        * Setting the create of the next new chunk of the heap
                        */
                        ptr_sstc_lcl_next_chunk->u64_data_length_redundancy_          = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                        ptr_sstc_lcl_next_chunk->u8_check_redundancy_1_               = TRUE;
                        ptr_sstc_lcl_next_chunk->u64_previous_data_length_redundancy_ = size;
                        ptr_sstc_lcl_next_chunk->u8_check_redundancy_2_               = TRUE;

                        ptr_sstc_lcl_next_chunk->u64_data_length_                   = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                        ptr_sstc_lcl_next_chunk->u8_data_free_flag_                 = TRUE;
                        ptr_sstc_lcl_next_chunk->u64_previous_data_length_          = size;
                        ptr_sstc_lcl_next_chunk->u8_previous_data_heap_header_flag_ = FALSE;

                        /**
                        * Setting the size of the actual chunk in the heap
                        */
                        ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = size;
                        ptr_sstc_lcl_passed_chunk->u64_data_length_            = size;

                        ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;

                        /**
                        * Check if the new created chunk is not the last chunk of the heap
                        */
                        if(((uintptr_t) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                            {
                            /**
                            * Treat the case when the new created chunk is not the last chunk of the heap
                            */

                            /**
                            * Setting the size of the previous chunk of the next chunk of the new created chunk
                            */
                            ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) ((void *) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_);
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_next_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_next_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u8_previous_data_heap_header_flag_   = FALSE;
                            }
                        else
                            {
                            /**
                            * Treat the case when the new created chunk is the last chunk of the heap
                            */
                            }
                        }
                    else
                        {
                        /**
                        * Treat the case when the size after the new allocated chunk is not bigger than a chunk header
                        */
                        }
                    }
                }
            else
                {
                /**
                * Check if the size after the new allocated chunk is bigger than a chunk header
                */
                if(((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size) > sizeof(struct sstc_chunk_header))
                    {
                    /**
                    * Treat the case when the size after the new allocated chunk is bigger than a chunk header
                    */

                    /**
                    * Getting the address of the new next chunk to create of the heap
                    */
                    ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + size);

                    /**
                    * Setting the create of the next new chunk of the heap
                    */
                    ptr_sstc_lcl_next_chunk->u64_data_length_redundancy_          = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                    ptr_sstc_lcl_next_chunk->u8_check_redundancy_1_               = TRUE;
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_redundancy_ = size;
                    ptr_sstc_lcl_next_chunk->u8_check_redundancy_2_               = TRUE;

                    ptr_sstc_lcl_next_chunk->u64_data_length_                   = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                    ptr_sstc_lcl_next_chunk->u8_data_free_flag_                 = TRUE;
                    ptr_sstc_lcl_next_chunk->u64_previous_data_length_          = size;
                    ptr_sstc_lcl_next_chunk->u8_previous_data_heap_header_flag_ = FALSE;

                    /**
                    * Setting the size of the actual chunk in the heap
                    */
                    ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = size;
                    ptr_sstc_lcl_passed_chunk->u64_data_length_            = size;

                    ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;

                    /**
                    * Check if the new created chunk is not the last chunk of the heap
                    */
                    if(((uintptr_t) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                        {
                        /**
                        * Treat the case when the new created chunk is not the last chunk of the heap
                        */

                        /**
                        * Setting the size of the previous chunk of the next chunk of the new created chunk
                        */
                        ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) ((void *) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_);
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_next_chunk->u64_data_length_;
                        ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_next_chunk->u64_data_length_;
                        ptr_sstc_lcl_chunk_to_change_previous_size->u8_previous_data_heap_header_flag_   = FALSE;
                        }
                    else
                        {
                        /**
                        * Treat the case when the new created chunk is the last chunk of the heap
                        */
                        }
                    }
                else
                    {
                    /**
                    * Treat the case when the size after the new allocated chunk is not bigger than a chunk header
                    */
                    }
                }

#ifdef THREAD_SAFE
            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Unlocking the mutex to access the tiny heap list in the structure malloc data
                */
                s32_lcl_return_from_function = -1;
                s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                /**
                * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                if(s32_lcl_return_from_function != 0)
                    {
                    /**
                    * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */

                    #ifdef DEVELOPEMENT
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                    #endif

                    #ifdef DEMO
                    fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                    #endif

                    #ifdef PRODUCTION
                    fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                    #endif

                    /**
                    * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                    */
                    return (NULL);
                    }
                else
                    {
                    /**
                    * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    } 

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Unlocking the mutex to access the tiny heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

            /**
            * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                */
                return (NULL);
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                */
                } 
#endif

            return (ptr);
            }
        else
            {
            /**
            * Treat the case when the passed chunk need to be expand
            */

            /**
            * Getting the next chunk
            */
            if((uintptr_t) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                {
                ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + ptr_sstc_lcl_passed_chunk->u64_data_length_);

                /**
                * Check if the next chunk is free
                */
                if(ptr_sstc_lcl_next_chunk->u8_data_free_flag_ == TRUE)
                    {
                    /**
                    * Treat the case when the next chunk is free
                    */

                    /**
                    * Check if the size of the actual chunk with the size of the next chunk is bigger or equals to the new size to allocate
                    */
                    if(((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_) >= (uint64_t) size)
                        {
                        /**
                        * Treat the case when the size of the actual chunk with the size of the next chunk is bigger or equals to the new size to allocate
                        */

                        ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_);
                        ptr_sstc_lcl_passed_chunk->u64_data_length_            = ((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ + sizeof(struct sstc_chunk_header) + (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_);

                        ptr_sstc_lcl_actual_heap->u64_number_of_free_space_   -= (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;

                        /**
                        * Check if the passed chunk is not the last chunk of the heap
                        */
                        if(((uintptr_t) ptr_sstc_lcl_passed_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_passed_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                            {
                            /**
                            * Treat the case when the passed chunk is not the last chunk of the heap
                            */

                            /**
                            * Setting the size of the previous chunk of the next chunk of the passed chunk
                            */
                            ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) ((void *) ptr_sstc_lcl_passed_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_passed_chunk->u64_data_length_);
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_passed_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_passed_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u8_previous_data_heap_header_flag_   = FALSE;
                            }
                        else
                            {
                            /**
                            * Treat the case when the passed chunk is the last chunk of the heap
                            */
                            }
                        }
                    else
                        {
                        /**
                        * Treat the case when the size of the actual chunk with the size of the next chunk is not bigger nor equals to the new size to allocate
                        */
                        }

                    /**
                    * Check if the size after the new allocated chunk is bigger than a chunk header
                    */
                    if(((uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size) > sizeof(struct sstc_chunk_header))
                        {
                        /**
                        * Treat the case when the size after the new allocated chunk is bigger than a chunk header
                        */

                        /**
                        * Getting the address of the new next chunk to create of the heap
                        */
                        ptr_sstc_lcl_next_chunk = (struct sstc_chunk_header *) (ptr + size);

                        /**
                        * Setting the create of the next new chunk of the heap
                        */
                        ptr_sstc_lcl_next_chunk->u64_data_length_redundancy_          = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                        ptr_sstc_lcl_next_chunk->u8_check_redundancy_1_               = TRUE;
                        ptr_sstc_lcl_next_chunk->u64_previous_data_length_redundancy_ = size;
                        ptr_sstc_lcl_next_chunk->u8_check_redundancy_2_               = TRUE;

                        ptr_sstc_lcl_next_chunk->u64_data_length_                   = (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_ - size - sizeof(struct sstc_chunk_header);
                        ptr_sstc_lcl_next_chunk->u8_data_free_flag_                 = TRUE;
                        ptr_sstc_lcl_next_chunk->u64_previous_data_length_          = size;
                        ptr_sstc_lcl_next_chunk->u8_previous_data_heap_header_flag_ = FALSE;

                        /**
                        * Setting the size of the actual chunk in the heap
                        */
                        ptr_sstc_lcl_passed_chunk->u64_data_length_redundancy_ = size;
                        ptr_sstc_lcl_passed_chunk->u64_data_length_            = size;

                        ptr_sstc_lcl_actual_heap->u64_number_of_free_space_ += (uint64_t) ptr_sstc_lcl_next_chunk->u64_data_length_;

                        /**
                        * Check if the new created chunk is not the last chunk of the heap
                        */
                        if(((uintptr_t) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_) < ((uintptr_t) ptr_sstc_lcl_actual_heap) + ptr_sstc_lcl_actual_heap->u64_length_of_data_)
                            {
                            /**
                            * Treat the case when the new created chunk is not the last chunk of the heap
                            */

                            /**
                            * Setting the size of the previous chunk of the next chunk of the new created chunk
                            */
                            ptr_sstc_lcl_chunk_to_change_previous_size                                       = (struct sstc_chunk_header *) ((void *) ptr_sstc_lcl_next_chunk + sizeof(struct sstc_chunk_header) + ptr_sstc_lcl_next_chunk->u64_data_length_);
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_            = ptr_sstc_lcl_next_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u64_previous_data_length_redundancy_ = ptr_sstc_lcl_next_chunk->u64_data_length_;
                            ptr_sstc_lcl_chunk_to_change_previous_size->u8_previous_data_heap_header_flag_   = FALSE;
                            }
                        else
                            {
                            /**
                            * Treat the case when the new created chunk is the last chunk of the heap
                            */
                            }
                        }
                    else
                        {
                        /**
                        * Treat the case when the size after the new allocated chunk is not bigger than a chunk header
                        */
                        }

#ifdef THREAD_SAFE
                    /**
                    * Unlocking the mutex to access the small heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

                    /**
                    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Unlocking the mutex to access the tiny heap list in the structure malloc data
                        */
                        s32_lcl_return_from_function = -1;
                        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                        /**
                        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        if(s32_lcl_return_from_function != 0)
                            {
                            /**
                            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */

                            #ifdef DEVELOPEMENT
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                            #endif

                            #ifdef DEMO
                            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                            #endif

                            #ifdef PRODUCTION
                            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                            #endif

                            /**
                            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                            */
                            return (NULL);
                            }
                        else
                            {
                            /**
                            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                            */
                            } 

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                        */
                        } 

                    /**
                    * Unlocking the mutex to access the tiny heap list in the structure malloc data
                    */
                    s32_lcl_return_from_function = -1;
                    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

                    /**
                    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                    */
                    if(s32_lcl_return_from_function != 0)
                        {
                        /**
                        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */

                        #ifdef DEVELOPEMENT
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                        #endif

                        #ifdef DEMO
                        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                        #endif

                        #ifdef PRODUCTION
                        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                        #endif

                        /**
                        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
                        */
                        return (NULL);
                        }
                    else
                        {
                        /**
                        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
                        */
                        } 
#endif

                    return (ptr);
                    }
                else
                    {
                    /**
                    * Treat the case when the next chunk is not free
                    */
                    }
                }
            else
                {
                ptr_sstc_lcl_next_chunk = NULL;
                }
            } 
        }
    else
        {
        /**
        * Treat the case when the new size is not in the same heap category of the actual chunk
        */
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return (NULL);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return (NULL);
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 
#endif

    ptr_vd_lcl_tmp = malloc(size);

    if(ptr_vd_lcl_tmp != NULL)
        {
        /**
        * Copying the content of the previous chunk to the new allocated chunk
        */
        u64_lcl_cnt = 0;
        while((u64_lcl_cnt < (uint64_t) ptr_sstc_lcl_passed_chunk->u64_data_length_) && (u64_lcl_cnt < (uint64_t) size))
            {
            ((uint8_t *) ptr_vd_lcl_tmp)[u64_lcl_cnt] = ((uint8_t *) ptr)[u64_lcl_cnt];

            /**
            * Checking for overflow
            */
            if(u64_lcl_cnt < UINT64_MAX)
                {
                u64_lcl_cnt++;
                }
            else
                {
                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The unsigned 64 integer counter variable is going to overflow\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return a failure to indicate the counter variable overflow
                */
                return (NULL);
                }
            }
        }

    (void) free(ptr);

    return (ptr_vd_lcl_tmp);
    }

void show_alloc_mem(void)
    {
    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t                  s32_lcl_return_from_function;
#endif
    struct sstc_heap_header *ptr_sstc_lcl_actual_heap;
    struct sstc_heap_header *ptr_sstc_lcl_heap_to_display;
    struct sstc_heap_header *ptr_sstc_lcl_previous_displayed_heap;
    uint64_t                 u64_lcl_tmp_allocated_memory;
    uint64_t                 u64_lcl_total_allocated_memory;
    uint8_t                  u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_heap             = NULL;
    ptr_sstc_lcl_heap_to_display         = NULL;
    ptr_sstc_lcl_previous_displayed_heap = NULL;
#ifdef THREAD_SAFE
    s32_lcl_return_from_function         = -1;
#endif
    u64_lcl_tmp_allocated_memory         = 0;
    u64_lcl_total_allocated_memory       = 0;
    u8_lcl_return_from_function          = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

#ifdef THREAD_SAFE
    /**
    * Locking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    ptr_sstc_lcl_actual_heap             = NULL;
    ptr_sstc_lcl_heap_to_display         = (void *) 1;
    ptr_sstc_lcl_previous_displayed_heap = NULL;
    u64_lcl_tmp_allocated_memory         = 0;
    u64_lcl_total_allocated_memory       = 0;
    while(ptr_sstc_lcl_heap_to_display != NULL)
        {
        ptr_sstc_lcl_heap_to_display = NULL;

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_small_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_large_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_previous_displayed_heap = ptr_sstc_lcl_heap_to_display;

        if(ptr_sstc_lcl_heap_to_display != NULL)
            {
            u64_lcl_tmp_allocated_memory = 0;
            (void) Fv__simple_display_heap((void *) ptr_sstc_lcl_heap_to_display, &u64_lcl_tmp_allocated_memory);

            if(u64_lcl_total_allocated_memory <= (UINT64_MAX - u64_lcl_tmp_allocated_memory))
                {
                u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + u64_lcl_tmp_allocated_memory;
                }
            else
                {
                u64_lcl_total_allocated_memory = UINT64_MAX;
                }
            }
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }
#endif

    ft_printf("Total : %" PRIu64 " octets\n", u64_lcl_total_allocated_memory);
    }

void show_alloc_mem_ex(void)
    {
    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t                  s32_lcl_return_from_function;
#endif
    struct sstc_heap_header *ptr_sstc_lcl_actual_heap;
    struct sstc_heap_header *ptr_sstc_lcl_heap_to_display;
    struct sstc_heap_header *ptr_sstc_lcl_previous_displayed_heap;
    uint64_t                 u64_lcl_tmp_allocated_memory;
    uint64_t                 u64_lcl_total_allocated_memory;
    uint8_t                  u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
    ptr_sstc_lcl_actual_heap             = NULL;
    ptr_sstc_lcl_heap_to_display         = NULL;
    ptr_sstc_lcl_previous_displayed_heap = NULL;
#ifdef THREAD_SAFE
    s32_lcl_return_from_function         = -1;
#endif
    u64_lcl_tmp_allocated_memory         = 0;
    u64_lcl_total_allocated_memory       = 0;
    u8_lcl_return_from_function          = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

#ifdef THREAD_SAFE
    /**
    * Locking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to lock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to lock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the small heap list in the structure malloc data succeeded
        */
        }

    /**
    * Locking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_lock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to lock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to lock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Unlocking the mutex to access the small heap list in the structure malloc data
            */
            s32_lcl_return_from_function = -1;
            s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

            /**
            * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            if(s32_lcl_return_from_function != 0)
                {
                /**
                * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */

                #ifdef DEVELOPEMENT
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
                #endif

                #ifdef DEMO
                fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
                #endif

                #ifdef PRODUCTION
                fprintf(stderr, "\033[1;31mERROR\033[0m\n");
                #endif

                /**
                * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
                */
                return;
                }
            else
                {
                /**
                * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
                */
                } 

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Unlocking the mutex to access the small heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

        /**
        * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to lock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to lock the mutex to access the large heap list in the structure malloc data succeeded
        */
        }
#endif

    ptr_sstc_lcl_actual_heap             = NULL;
    ptr_sstc_lcl_heap_to_display         = (void *) 1;
    ptr_sstc_lcl_previous_displayed_heap = NULL;
    u64_lcl_tmp_allocated_memory         = 0;
    u64_lcl_total_allocated_memory       = 0;
    while(ptr_sstc_lcl_heap_to_display != NULL)
        {
        ptr_sstc_lcl_heap_to_display = NULL;

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_tiny_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_small_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_actual_heap = cstc_glbl_malloc_data.ptr_sstc_heap_large_list_;
        while(ptr_sstc_lcl_actual_heap != NULL)
            {
            if(((uintptr_t) ptr_sstc_lcl_actual_heap > (uintptr_t) ptr_sstc_lcl_previous_displayed_heap) && ((ptr_sstc_lcl_heap_to_display == NULL) || ((uintptr_t) ptr_sstc_lcl_actual_heap < (uintptr_t) ptr_sstc_lcl_heap_to_display)))
                {
                ptr_sstc_lcl_heap_to_display = ptr_sstc_lcl_actual_heap;
                }

            ptr_sstc_lcl_actual_heap = ptr_sstc_lcl_actual_heap->ptr_sstc_next_heap_;
            }

        ptr_sstc_lcl_previous_displayed_heap = ptr_sstc_lcl_heap_to_display;

        if(ptr_sstc_lcl_heap_to_display != NULL)
            {
            u64_lcl_tmp_allocated_memory = 0;
            (void) Fv__simple_display_heap_ex((void *) ptr_sstc_lcl_heap_to_display, &u64_lcl_tmp_allocated_memory);

            if(u64_lcl_total_allocated_memory <= (UINT64_MAX - u64_lcl_tmp_allocated_memory))
                {
                u64_lcl_total_allocated_memory = u64_lcl_total_allocated_memory + u64_lcl_tmp_allocated_memory;
                }
            else
                {
                u64_lcl_total_allocated_memory = UINT64_MAX;
                }
            }
        }

#ifdef THREAD_SAFE
    /**
    * Unlocking the mutex to access the large heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_large_));

    /**
    * Check if function to unlock the mutex to access the large heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the large heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the large heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the large heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the small heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_small_));

    /**
    * Check if function to unlock the mutex to access the small heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the small heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Unlocking the mutex to access the tiny heap list in the structure malloc data
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

        /**
        * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
            */
            return;
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
            */
            } 

        /**
        * Return failure to indicate the function to unlock the mutex to access the small heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the small heap list in the structure malloc data succeeded
        */
        } 

    /**
    * Unlocking the mutex to access the tiny heap list in the structure malloc data
    */
    s32_lcl_return_from_function = -1;
    s32_lcl_return_from_function = pthread_mutex_unlock(&(cstc_glbl_malloc_data.etype_mutex_tiny_));

    /**
    * Check if function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
    */
    if(s32_lcl_return_from_function != 0)
        {
        /**
        * Treat the case when the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */

        #ifdef DEVELOPEMENT
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex to access the tiny heap list in the structure malloc data failed\n", __FILE__, __func__, __LINE__);
        #endif

        #ifdef DEMO
        fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
        #endif

        #ifdef PRODUCTION
        fprintf(stderr, "\033[1;31mERROR\033[0m\n");
        #endif

        /**
        * Return failure to indicate the function to unlock the mutex to access the tiny heap list in the structure malloc data failed
        */
        return;
        }
    else
        {
        /**
        * Treat the case when function to unlock the mutex to access the tiny heap list in the structure malloc data succeeded
        */
        }
#endif

    ft_printf("Total : %" PRIu64 " octets\n", u64_lcl_total_allocated_memory);
    }

void *calloc(size_t nmemb, size_t size)
    {
    (void) nmemb;
    (void) size;

    return (NULL);
    }

/**
* TINY_ALLOC_MAX
* SMALL_ALLOC_MAX
*/
int mallopt(int param, int value)
    {
    /**
    * Creation of local variable
    */
#ifdef THREAD_SAFE
    int32_t s32_lcl_return_from_function;
#endif
    uint8_t u8_lcl_return_from_function;

    /**
    * Initialization of local variable
    */
#ifdef THREAD_SAFE
    s32_lcl_return_from_function = -1;
#endif
    u8_lcl_return_from_function  = RETURN_FAILURE;

    /**
    * Check if The structure malloc is not initialized
    */
    if((cstc_glbl_malloc_data.u8_global_status_ & FIRST_BIT) == FALSE)
        {
        /**
        * Treat the case when The structure malloc is not initialized
        */

        /**
        * Initialize the global structure malloc
        */
        u8_lcl_return_from_function = RETURN_FAILURE;
        u8_lcl_return_from_function = Fu8__init_structure_malloc_data(&cstc_glbl_malloc_data);

        /**
        * Check if function to init the global structure malloc succeeded
        */
        if(u8_lcl_return_from_function != RETURN_SUCCESS)
            {
            /**
            * Treat the case when the function to init the global structure malloc failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to init the global structure malloc failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to init the global structure malloc failed
            */
            return (0);
            }
        else
            {
            /**
            * Treat the case when function to init the global structure malloc succeeded
            */
            } 
        }
    else
        {
        /**
        * Treat the case when The structure malloc is already initialized
        */
        }

    if(param == TINY_ALLOC_MAX)
        {
#ifdef THREAD_SAFE
        /**
        * Locking the mutex parameter
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_lock(&cstc_glbl_malloc_data.etype_mutex_parameter_);

        /**
        * Check if function to lock the mutex parameter succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to lock the mutex parameter failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to lock the mutex parameter failed
            */
            return (0);
            }
        else
            {
            /**
            * Treat the case when function to lock the mutex parameter succeeded
            */
            } 
#endif

        if(value < MINIMUM_TINY_ALLOC_MAX)
            {
            cstc_glbl_malloc_data.u64_tiny_alloc_max_ = MINIMUM_TINY_ALLOC_MAX;
            }
        else if(value > MAXIMUM_TINY_ALLOC_MAX)
            {
            cstc_glbl_malloc_data.u64_tiny_alloc_max_ = MAXIMUM_TINY_ALLOC_MAX;
            }
        else
            {
            cstc_glbl_malloc_data.u64_tiny_alloc_max_ = value;
            }

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex parameter
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&cstc_glbl_malloc_data.etype_mutex_parameter_);

        /**
        * Check if function to unlock the mutex parameter succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex parameter failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex parameter failed
            */
            return (0);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex parameter succeeded
            */
            } 
#endif
        }
    else if(param == SMALL_ALLOC_MAX)
        {
#ifdef THREAD_SAFE
        /**
        * Locking the mutex parameter
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_lock(&cstc_glbl_malloc_data.etype_mutex_parameter_);

        /**
        * Check if function to lock the mutex parameter succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to lock the mutex parameter failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to lock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to lock the mutex parameter failed
            */
            return (0);
            }
        else
            {
            /**
            * Treat the case when function to lock the mutex parameter succeeded
            */
            }
#endif

        if(value < MINIMUM_SMALL_ALLOC_MAX)
            {
            cstc_glbl_malloc_data.u64_small_alloc_max_ = MINIMUM_SMALL_ALLOC_MAX;
            }
        else if(value > MAXIMUM_SMALL_ALLOC_MAX)
            {
            cstc_glbl_malloc_data.u64_small_alloc_max_ = MAXIMUM_SMALL_ALLOC_MAX;
            }
        else
            {
            cstc_glbl_malloc_data.u64_small_alloc_max_ = value;
            }

#ifdef THREAD_SAFE
        /**
        * Unlocking the mutex parameter
        */
        s32_lcl_return_from_function = -1;
        s32_lcl_return_from_function = pthread_mutex_unlock(&cstc_glbl_malloc_data.etype_mutex_parameter_);

        /**
        * Check if function to unlock the mutex parameter succeeded
        */
        if(s32_lcl_return_from_function != 0)
            {
            /**
            * Treat the case when the function to unlock the mutex parameter failed
            */

            #ifdef DEVELOPEMENT
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m in function \033[1m%s\033[0m at line \033[1m%d\033[0m\n    The function to unlock the mutex parameter failed\n", __FILE__, __func__, __LINE__);
            #endif

            #ifdef DEMO
            fprintf(stderr, "\033[1;31mERROR\033[0m: in file \033[1m%s\033[0m at line \033[1m%s\033[0m\n", __FILE__, __LINE__);
            #endif

            #ifdef PRODUCTION
            fprintf(stderr, "\033[1;31mERROR\033[0m\n");
            #endif

            /**
            * Return failure to indicate the function to unlock the mutex parameter failed
            */
            return (0);
            }
        else
            {
            /**
            * Treat the case when function to unlock the mutex parameter succeeded
            */
            }
#endif
        }

    return (1);
    }
