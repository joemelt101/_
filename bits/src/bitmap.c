#include "../include/bitmap.h"

//TODO: OK to add?
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
    
    //TODO: Why not this?
    // map->byte_count = (size_t)ceil((double)n_bits / 8);
    
    map->byte_count = n_bits / 8;
    
    //allocate data. Make sure it is cleared out (calloc)!
    map->data = (uint8_t *) calloc(map->byte_count, 1);
    
	return map;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) 
{
    if (! bitmap || bit >= bitmap->bit_count)
    {
        //must be instantiated or bit doesn't exist
        return false;
    }
    
    //reference start of data
    uint8_t *b = bitmap->data;
    
    //figure out number of bytes and roll forward that number
    b += (bit / 8);
    
    //figure out bit number in byte
    size_t bit_num = bit % 8;
    
    //create applicable mask to set bit
    uint8_t mask = 0x01 << bit_num;
    
    //apply mask
    (*b) = (*b) | mask;
        
    //made it to the end so success!
	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) 
{
    if (! bitmap || bit >= bitmap->bit_count)
    {
        return false;
    }
    
    //ref start of data
    uint8_t *b = bitmap->data;
    
    //figure out number of bytes and roll forward that number
    b += (bit / 8);
    
    //figure out bit number in byte
    size_t bit_num = bit % 8;
    
    //create applicable mask to reset bit
    uint8_t mask = 0x01 << bit_num; 
    
    //flip
    mask = 0xFF ^ mask;
    
    //apply mask
    (*b) = (*b) & mask;
    
    //made it this far so success!
	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) 
{
    if (! bitmap || bit >= bitmap->bit_count)
    {
        return false;
    }
    
    uint8_t *b = bitmap->data;
    
    b += (bit / 8);
    
    size_t byte = *b;
    size_t bit_num = bit % 8;
    
    uint8_t mask = 0x01 << bit_num;
    byte &= mask;
    
    if (byte > 0)
    {
        //it must have been true
        return true;
    }
    
    //it must have been false
    return false;
}

//TODO: Fix 
size_t bitmap_ffs(const bitmap_t *const bitmap) 
{
    if (! bitmap || ! bitmap->data)
    {
        return SIZE_MAX;
    }
    
    size_t i = 0; //holds current byte index
    uint8_t *d = bitmap->data; //holds current data pointer
    
    //while not at the end of the bitmap
    //  and *d is equal to zero
    while (i < bitmap->byte_count && *d == 0)
    {
        ++d;
        ++i;
    }
    
    if (i == bitmap->byte_count)
    {
        //apply mask of zeros to extraneous bits in last byte
        uint8_t mask = 0xFF >> (8 - bitmap->bit_count % 8);
        
        if (((*d) & mask) == 0x00)
        {
            //arrived at end of bitmap and no ones...
            return SIZE_MAX;
        }
    }
    
    //*d != 0 and i < bitmap->byte_count
    //found a set bit
    //figure out which bit
    size_t bit_num = 1;
    
    while (*d >> bit_num != 0)
        bit_num++;
    
    //i = num bytes
    //bit_num = num bits in ith byte (zero based)
	return (i * 8) + (bit_num - 1); //subtract 1 for zero based index
}

//TODO: Fix
size_t bitmap_ffz(const bitmap_t *const bitmap) 
{
    if (! bitmap || ! bitmap->data)
    {
        return SIZE_MAX;
    }
    
    size_t i = 0; //holds current byte index
    uint8_t *d = bitmap->data; //holds current data pointer
    
    //while not at the end of the bitmap
    //  and *d is equal to zero
    while (i < bitmap->byte_count && *d == 0xFF)
    {
        ++d;
        ++i;
    }
    
    if (i == bitmap->byte_count)
    {
        //apply mask of ones to extraneous bits in last byte
        uint8_t mask = 0xFF << bitmap->bit_count % 8;
        
        if (((*d) | mask) == 0xFF)
        {
            //arrived at end of bitmap and no zeros...
            return SIZE_MAX;
        }
    }
    
    
    //*d != 0 or i == bitmap->byte_count
    
    //*d != 0 and i < bitmap->byte_count
    //found a set bit
    //figure out which bit in byte
    size_t bit_num = 1;
    
    uint8_t t = (*d) ^ 0xFF;
        
    while ((uint8_t)(t << bit_num) != 0)
        bit_num++;
    
    //i = num bytes
    //bit_num = num bits in ith byte (zero based)
	return (i * 8) + (8 - bit_num); //subtract 1 for zero based index
}

//TODO: bitmap_get_bits and bitmap_get_bytes doesn't exist...

bool bitmap_destroy(bitmap_t *bitmap) 
{
    if (! bitmap)
    {
        return false;
    }
    
    if (bitmap->data != NULL)
    {
        free(bitmap->data);
    }
    
    free(bitmap);
    
	return true;
}
