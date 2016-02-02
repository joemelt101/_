#include "../include/debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// protected function, that only this .c can use
int comparator_func(const void *a, const void *b) {
    return *((uint16_t *) a) - *((uint16_t *)b);
}

bool terrible_sort(uint16_t *data_array, const size_t value_count) {
    
    if (! data_array || value_count == 0)
    {
        return false;
    }
    
    uint16_t *sorting_array = (uint16_t *) malloc(value_count * sizeof(uint16_t));
    
    if (! sorting_array)
    {
        return false;
    }
    
    //copy the requested number of values into sorting_array[]
    for (int i = 0; i < value_count; ++i) {
        sorting_array[i] = data_array[i];
    }

    qsort(sorting_array, value_count, sizeof(uint16_t), comparator_func);
    
    for (int i = 1; i < value_count; ++i) {
        if (sorting_array[i - 1] > sorting_array[i])
        {
            //not sorted!
            return false;
        }
    }
    
    memcpy(data_array, sorting_array, value_count * sizeof(uint16_t));
    
    free(sorting_array);
    
    //made it this far... So it must have sorted well!!!
    return true;
}

