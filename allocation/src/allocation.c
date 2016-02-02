#include "../include/allocation.h"
#include "stdlib.h"
#include "stdio.h"

void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
    if (member_size == 0 || nmember == 0)
    {
        return NULL;
    }
    
    void *arr;
    
    if (clear)
    {
        arr = calloc(nmember, member_size);
    }
    else
    {
        arr = malloc(nmember * member_size);
    }
    
	return arr;
}

void* reallocate_array(void* ptr, size_t size)
{
    if (size == 0)
    {
        return NULL;
    }
    
	return realloc(ptr, size);    
}

void deallocate_array(void** ptr)
{
    if (! ptr)
    {
        return;
    }
    
    free(*ptr);
    *ptr = NULL;
}

char* read_line_to_buffer(char* filename)
{
    //get size of file
    
    FILE* file = fopen(filename, "r");
    
    //check to see if got the file OK
    if (file == NULL)
    {
        //failed to open file...
        return NULL;
    }
    
    char* line = NULL;
    size_t n = 0;
	
    int res = getline(&line, &n, file);
    
    //close the file
    fclose(file);
    
    //if error occurred
    if (res == -1)
    {
        return NULL;
    }
    
    //else return line
    return line;
}
