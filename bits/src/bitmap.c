#include "../include/bitmap.h"
#include <limits.h>
#include <math.h>


struct bitmap 
{
	uint8_t *data;
	size_t bit_count, byte_count;
};

bitmap_t *bitmap_create(size_t n_bits) 
{
    //TODO: why is SIZE_MAX too large?
    if (n_bits == 0 || n_bits == SIZE_MAX)
    {
        return NULL;
    }
    
    //allocate a bitmap_t struct
    bitmap_t *map = (bitmap_t *) malloc(sizeof(bitmap_t));
    
    if (map == NULL)
    {
        //was unable to allocate for some reason....
        return NULL;
    }

    //allocate the given number of bits
    map->bit_count = n_bits;
    map->byte_count = n_bits / 8;
    
    //allocate data. Make sure it is cleared out (calloc)!
    map->data = (uint8_t *) calloc(map->byte_count, 1);
    
	return map;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) 
{
    if (! bitmap)
    {
        //must be instantiated!
        return false;
    }
    
    //ceil(bitmap->data)
    
    //made it to the end so success!
	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) 
{
    
	return false;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) 
{
    
    return false;
}

size_t bitmap_ffs(const bitmap_t *const bitmap) 
{

	return 0;
}

size_t bitmap_ffz(const bitmap_t *const bitmap) 
{

	return 0;
}

bool bitmap_destroy(bitmap_t *bitmap) 
{
	return false;
}
