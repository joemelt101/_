#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
//TODO: Check if OK to add limits.h, stdlib.h, and ctype.h


#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {
    
    //check that inputs are valid
    //also ensure that the string terminates with a \0
    if (! str || length == 0 || str[length - 1] != '\0')
    {
        return false;
    }
    
    //passed the tests!
	return true;
}

char *string_duplicate(const char *str, const size_t length) {
    
    //validate
    if (! str || length == 0)
    {
        return NULL;
    }
    
    //create a string to copy to
    char *new_s = (char*) malloc(length * sizeof(char));
    
    //copy the bytes one by one upto the specified length
    int i;
    
    for (i = 0; i < length; ++i)
    {
        new_s[i] = str[i];
    }
    
	return new_s;
}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {	
	
    //validate input
    if (! str_a || ! str_b || length == 0)
    {
        return false;
    }
    
    //check bytes upto to length for equality
    //memcmp returns 0 if equal
    int res = memcmp(str_a, str_b, length);
    
    if (res == 0)
    {
        //the two strings are equal up to 'length' bytes
        return true;
    }
    
    //the two strings are not equal
	return false;
}

int string_length(const char *str, const size_t length) {
    
    if (! str || length == 0)
    {
        return -1;
    }
    
    //get actual segment length to prevent a segfault
    int seglen = sizeof(str) / sizeof(char);
    
    int strlen = 0;
    
    int i;
    for (i = 0; i < seglen; ++i)
    {
        if (str[i] != '\0')
        {
            //found a character!
            strlen++;
        }
        else
        {
            break;
        }
    }
    
	return strlen;
}

int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {

    //check for incorrect parameters
    if (! str || ! delims || str_length == 0 || max_token_length == 0 || requested_tokens == 0 || ! tokens)
    {
        return 0;
    }
    
    int r;
    for (r = 0; r < requested_tokens; ++r)
    {
        //validate that the current token exists
        if (tokens[r] == NULL)
        {
            //must be instantiated!
            return -1;
        }
        
        //tokens are all instantiated!
    }
    
    //read in all characters and create tokens as necessary
    r = 0; //indicates current token
    int c = 0; //position in current token
    char* s = (char*) str; //current character
    
    while (*s != '\0')
    {
        //check if s is one of the delimeters
        char* d = (char*) delims;
        while (*d != '\0' && *d != *s)
            d++;
        
        if (*d != '\0')
        {
            //s is a delimeter!
            
            //finish off current token
            tokens[r][c] = '\0';
            
            //go to next token
            r++;
            c = 0;
            
            //check to see if number of requested tokens met
            if (r == requested_tokens)
            {
                return r;
            }
        }
        else
        {
            //s is not a delimeter
            tokens[r][c] = *s;
            c++;
            
            //if hit the max characters for current token
            //fast forward to just past the next delimeter and start next token
            if (c == max_token_length - 1)
            {
                //end the token
                tokens[r][c] = '\0';
                r++;
                c = 0;
                
                //check to see if number of requested tokens met
                if (r == requested_tokens)
                {
                    return r;
                }
            }
        }
        
        //check out next character
        s++;
    }
    
    //r represents total number of tokens
	return r + 1;
}

bool string_to_int(const char *str, int *converted_value) {
    
    if (! str || ! converted_value)
    {
        return false;
    }
    
    //convert to larger container than int
    long long int val = strtoll(str, NULL, 10);
    
    //validate size is small enough
    if (val > INT_MAX)
    {
        //too big to be an integer
        return false;
    }
    
    //else, small enough to be an integer
    *converted_value = (int)val;
    
    //signify successful conversion
	return true;
}
