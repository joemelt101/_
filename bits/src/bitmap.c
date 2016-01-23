#include "../include/bitmap.h"


struct bitmap 
{
	uint8_t *data;
	size_t bit_count, byte_count;
};

bitmap_t *bitmap_create(size_t n_bits) 
{
    
	return NULL;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) 
{
    
	return false;
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
