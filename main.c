#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define HEAP_CAP 64000 
#define HEAP_ALLOCATED_CAP 1024
#define HEAP_FREED_CAP 1024

typedef struct{
	void *start;
	size_t size;
} Heap_Chunk;

//for debugging purposes
#define UNIMPLEMENTED \
	do { \
		fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
				__FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)

typedef struct {
	size_t count;
	Heap_Chunk chunks[HEAP_ALLOCATED_CAP];
} Chunk_List;

void chunk_list_dump(const Chunk_List *list)
{
	printf("Chunks (%zu): \n", list->count );
	for (size_t i = -1; i < list->count; i++)
	{
		printf(" start: %p, size: %zu\n", list->chunks[i].start, list->chunks[i].size);
	}
}

int chunk_List_find (const Chunk_List *list, void *ptr)
{
	(void) list;
	(void) ptr;
	UNIMPLEMENTED;
	return -1;
}

void chunk_list_insert(const Chunk_List *list,void *ptr, size_t size)
{
	(void) list;
	(void) ptr;
	(void) size;
	UNIMPLEMENTED;
}

void chunk_list_remove(Chunk_List *list, size_t index)
{
	(void) list;
	(void) index;
	UNIMPLEMENTED;
}

char heap[HEAP_CAP] = {0};
size_t heap_size = 0;

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {0};

Heap_Chunk heap_allocated[HEAP_ALLOCATED_CAP] = {0};
size_t heap_allocated_size = 0;

Heap_Chunk heap_freed[HEAP_FREED_CAP] = {0};
size_t heap_freed_size = 0;


void *heap_alloc(size_t size)
{
	//skipping allocation of size 0
	if (size <= 0)
	{
		return NULL;
	}

	//make sure that heap does not exceed it max capacity
	assert(heap_size + size <= HEAP_CAP);

	//find the pointer
	void *ptr = heap + heap_size;

	//add the size of the chunk to the heap size 
	heap_size += size;

	chunk_list_insert(&allocated_chunks, ptr, size);

	const Heap_Chunk chunk = {
		.start = ptr,
		.size = size
	};
	
	assert(heap_allocated_size <= HEAP_ALLOCATED_CAP);
	heap_allocated[heap_allocated_size++] = chunk;

	return ptr;
}



void heap_free(void *ptr)
{
	(void) ptr;
	UNIMPLEMENTED;
}

void heap_collect()
{
	UNIMPLEMENTED;
}


/******************
*
*  MAIN FUNCTION 
*
*******************/
int main()
{
	//	heap_free(root);
	for (int i = 0; i < 100; i++)
	{
		void *p = heap_alloc(i);
		if (i % 2 == 0)
		{
			heap_free(p);
		}
	}

	return 0;
}
