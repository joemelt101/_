#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size) {	

    if (! input_filename || ! dst || dst_size == 0)
    {
        return false;
    }
    
    int file = open(input_filename, O_RDONLY);
    
    if (file == -1)
    {
        //failed to open properly...
        return false;
    }
    
    //else, opened successfully!
    int res = pread(file, dst, dst_size, offset);
    close(file);
    
    if (res == -1)
    {
        //something went wrong
        return false;
    }
    
    //made it to the end! Signify success.
	return true;
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size) {

    if (! src || ! output_filename || src_size == 0)
    {
        return false;
    }
    
    //open file
    int file = open(output_filename, O_WRONLY);
    
    if (file == -1)
    {
        //failed to open correctly...
        return false;
    }
    
    //else, opened successfully!
    int res = pwrite(file, src, src_size, offset);
    close(file);
    
    if (res == -1)
    {
        //failed to write for some reason...
        return false;
    }
    
	return true;
}


bool file_stat(const char *query_filename, struct stat *metadata) {
    
    if (! query_filename || ! metadata)
    {
        return false;
    }
    
    int file = open(query_filename, O_RDONLY);
    int status = fstat(file, metadata);
    close(file);

    if (status == -1)
    {
        //something went wrong
        return false;
    }
    
    //everything worked!
	return true;
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {
    
    if (! src_data || ! dst_data || src_count == 0)
    {
        //invalid arguments detected
        return false;
    }
    
    //create pointer at end of source data
    size_t i;
    
    //create pointer at start of dst_data
    uint32_t *d = dst_data;
    for (i = 0; i < src_count; ++i)
    {
        //src_data is decrementing -- thus flipping the bytes
        uint32_t val = src_data[i];
        
        val = (val >> 24 & 0x000000FF) | 
            ((val >> 8) & 0x0000FF00) |
            ((val << 8) & 0x00FF0000) |
            ((val << 24) & 0xFF000000);
        
        //set d to new value
        *d = val;
        
        //increment to next memory location
        d++;
    }

	return true;
}
