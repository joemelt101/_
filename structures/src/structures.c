
#include "../include/structures.h"

int compare_structs(sample_t* a, sample_t* b)
{
    if (! a || ! b)
    {
        //null value detected...
        return 0;
    }
    
    if (a->a == b->a && a->b == b->b && a->c == b->c)
    {
        //matched so return 1
        return 1;
    }
    
    //didn't match so return 0
	return 0;
}

void print_alignments()
{
	printf("Alignment of int is %zu bytes\n",__alignof__(int));
	printf("Alignment of double is %zu bytes\n",__alignof__(double));
	printf("Alignment of float is %zu bytes\n",__alignof__(float));
	printf("Alignment of char is %zu bytes\n",__alignof__(char));
	printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
	printf("Alignment of short is %zu bytes\n",__alignof__(short));
	printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}


int sort_fruit(const fruit_t* a,int* apples,int* oranges, const size_t size)
{
    if (! a || ! apples || ! oranges || size == 0)
    {
        return -1; //invalid arguments
    }
    
    int i;
    
    for (i = 0; i < size; ++i)
    {
        if (a[i].type == 0)
        {
            //must be an orange
            *oranges += 1;
        }
        else
        {
            *apples += 1;
        }
    }
    
	return size;
}

int initialize_array(fruit_t* a, int apples, int oranges)
{
    int total = apples + oranges;
    
    if (! a || total == 0)
    {
        //malloc ran into an issue
        return -1;
    }
    
    //initialize polymorphic array
    //first apples, then oranges
    //0 - apples
    //1 - oranges
    fruit_t *b = a;
    
    int res = 0;
    
    while (apples > 0)
    {
        res = initialize_apple((apple_t *)b);
        
        if (res == -1)
        {
            //free existing memory and report error
            free(a);
            return -1;
        }
        
        //keep track of how many left
        apples--;
        
        //move to next open location for fruit
        b++;
    }
    
    //the rest are oranges
    while (oranges > 0)
    {
        res = initialize_orange((orange_t *)b);
        
        //keep track of how many oranges are left
        oranges--;
        
        //move to the next open location for fruit entries
        b++;
    }
    
	return 0;
}

int initialize_orange(orange_t* a)
{	
    if (! a)
    {
        return -1;
    }
    
    a->type = 0;
    a->weight = 2;
    a->peeled = 0;
    
	return 0;

}

int initialize_apple(apple_t* a)
{	
    if (! a)
    {
        return -1;
    }
    
    a->type = 1;
    a->weight = 1;
    a->worms = 0;
    
	return 0;
}
