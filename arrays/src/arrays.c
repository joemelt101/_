#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) 
{
	if (! src || ! dst || elem_size == 0 || elem_count == 0)
	{
		return false; //invalid inputs....
	}

	memcpy(dst, src, elem_size * elem_count);

	return true;
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) 
{
	if (! data_one || ! data_two || elem_size == 0 || elem_count == 0)
	{
		return false; //invalid inputs
	}

	int result = memcmp(data_one, data_two, elem_size * elem_count);

	if (result == 0)
	{
		//the two are equal so return true
		return true;
	}

	//they are not equal so return false
	return false;
}

size_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) 
{
    if (! data || ! target || elem_size == 0 || elem_count == 0)
    {
        return -1;
    }
    
    char* d = (char*) data; //start at the beginning...
    
    //loop through data
    size_t i = 0;
    
    for (i = 0; i < elem_count; ++i)
    {
        int result = 0;
        
        result = memcmp(d, target, elem_size);
        
        if (result == 0)
        {
            //found the location!
            return i;
        }
        
        //else keep searching....
        d += elem_size; //increment the pointer to the next element starting loc
    }
    
    //was not able to find the target
	return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) 
{
    if (! src_data || ! dst_file || elem_size == 0 || elem_count == 0)
    {
        return false;
    }
    
    FILE* file = fopen(dst_file, "w");
    
    if (! file || ! is_valid_filename(dst_file))
    {
        //file couldn't open properly
        return false;
    }
    
    //get the number of elements written
    int bWritten = fwrite(src_data, elem_size, elem_count, file);
    
    //cleanup
    fclose(file);
    
    //check to see they were all written
    if (bWritten != elem_count)
    {
        return false; //not all the bytes were written!
    } 
    
    //else, all the bytes were written...
    return true;
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) 
{
	if (! src_file || ! dst_data || elem_size == 0 || elem_count == 0)
    {
        return false;
    }
    
    FILE* file = fopen(src_file, "r");
    
    if (! file || ! is_valid_filename(src_file))
    {
        //file didn't open properly
        return false;
    }
    
    //get number of elements read
    int bRead = fread(dst_data, elem_size, elem_count, file);
    
    //check to see they were all read
    if (bRead != elem_count)
    {
        return false; //not all the elements were read!
    }
    
    //else, all the bytes were read....
    return true;
    
    
	return true;
}

bool is_valid_filename(const char *filename)
{
    if (! filename)
    {
        return false;
    }
    
    char invalid_characters[] = "!@%^*~|\n\t";
    
    int i;
    
    for (i = 0; i < strlen(invalid_characters); ++i) 
    {
        if (strchr(filename, invalid_characters[i]) != NULL) 
        {
            //invalid character found
            return false;
        }
    }
    
    return true;
}