#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define HEAP_CAP 64000 
#define HEAP_ALLOCATED_CAP 1024

typedef struct{
	void *start;
	size_t size;
} Heap_Chunk;

char heap[HEAP_CAP] = {0};
size_t heap_size = 0;

Heap_Chunk heap_allocated[HEAP_ALLOCATED_CAP] = {0};
size_t heap_allocated_size = 0;


void *heap_alloc(size_t size)
{
	//make sure that heap does not exceed it max capacity
	assert(heap_size + size <= HEAP_CAP);

	//find the pointer
	void *result = heap + heap_size;

	//add the size of the chunk to the heap size 
	heap_size += size;

	const Heap_Chunk chunk = {
		.start = result,
		.size = size
	};
	
	assert(heap_allocated_size <= HEAP_ALLOCATED_CAP);
	heap_allocated[heap_allocated_size++] = chunk;

	return result;
}

void heap_dump_alloced_chunks(void)
{
	printf("Alloced Chunks (%zu): \n", heap_allocated_size);
	for (size_t i = 0; i < heap_allocated_size; i++)
	{
		printf(" start: %p, size: %zu\n", heap_allocated[i].start, heap_allocated[i].size);
	}
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
	for (int i = 0; i < 100; i++)
	{
		//is 0 valid?
		heap_alloc(i);
	}

	char *root = heap_alloc(26);

	for (int i = 0; i < 26; i++)
	{
		root[i] = i + 'A';
	}

	heap_dump_alloced_chunks();

//	heap_free(root);

	return 0;
}
