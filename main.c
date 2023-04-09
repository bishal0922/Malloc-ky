#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define HEAP_CAPACITY 64000 

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

void *heap_alloc(size_t size)
{
	//make sure that heap does not exceed it max capacity
	assert(heap_size + size <= HEAP_CAPACITY);

	//find the pointer
	void *result = heap + heap_size;

	//add the size of the chunk to the heap size 
	heap_size += size;
	
	return result;
}

void heap_free(void *ptr)
{
	(void) ptr;
	assert(false && "TODO: Heap_free is not implemented");
}

void heap_collect()
{
	assert(false && "TODO: Heap_collect is not implemented");
}

int main()
{
	char *root = heap_alloc(26);

	for (int i = 0; i < 26; i++)
	{
		root[i] = i + 'A';
	}

	return 0;
}
