#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define HEAP_CAP 64000 
#define CHUNK_LIST_CAP 1024

//for debugging purposes
#define UNIMPLEMENTED \
	do { \
		fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
				__FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)


typedef struct{
	char *start;
	size_t size;
} Chunk;

typedef struct {
	size_t count;
	Chunk chunks[CHUNK_LIST_CAP];
} Chunk_List;

char heap[HEAP_CAP] = {0};

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {
	.count = 1,
	.chunks = {
		[0] = {.start = heap, .size = sizeof(heap)}
	},
};
Chunk_List tmp_chunks = {0};

//deprecated
Chunk heap_allocated[CHUNK_LIST_CAP] = {0};
size_t heap_allocated_size = 0;

Chunk heap_freed[CHUNK_LIST_CAP] = {0};
size_t heap_freed_size = 0;



/*
	FUNCTIONS START HERE
*/



void chunk_list_dump(const Chunk_List *list)
{
	printf("Chunks (%zu): \n", list->count );
	for (size_t i = 0; i < list->count; i++)
	{
		printf(" start: %p, size: %zu\n", list->chunks[i].start, list->chunks[i].size);
	}
}

int chunk_start_compar(const void *a, const void *b)
{
	const Chunk *a_chunk = a;
	const Chunk *b_chunk = b;
	return a_chunk->start - b_chunk->start;
}

int chunk_List_find (const Chunk_List *list, void *ptr)
{
	Chunk key = {
		.start = ptr
	};

	Chunk *result = bsearch(&key, list->chunks, list->count, sizeof(list->chunks[0]), chunk_start_compar); 

	if (result != 0){
		assert(list->chunks <=result);
		return (result - list->chunks) / sizeof(list->chunks[0]);
	}
	else{
		return -1;
	}
}


void chunk_list_insert(Chunk_List *list,void *start, size_t size)
{
	assert(list->count < CHUNK_LIST_CAP);
	list->chunks[list->count].start = start;
	list->chunks[list->count].size = size;

	//if i become ==0 then we're already pointing to the first element
	for (size_t i = list-> count;
		i > 0 && list->chunks[i].start < list->chunks[i-1].start;
		i--)
	{
		//swap
		const Chunk temp = list->chunks[i];
		list->chunks[i] = list->chunks[i-1];
		list->chunks[i-1] = temp;
	}

	list->count++;
}

//merge the chunks so that space is utilized	
void chunk_list_merge(const Chunk_List *src, Chunk_List *dest)
{
	dest->count = 0;

	for (size_t i = 0; i < src->count; i++)
	{
		const Chunk chunk = src->chunks[i];
		if (dest->count > 0)
		{
			Chunk *top_chunk = &dest->chunks[dest->count - 1];
			dest->chunks[dest->count - 1].size += chunk.size;

			//if the chunks are adjacent, then merge them
			if (top_chunk->start + top_chunk->size == chunk.start)
			{
				top_chunk->size += chunk.size;
			}
			else
			{
				//O(1), since we're only adding one element no O(n)
				chunk_list_insert(dest, chunk.start, chunk.size);
			}
		}
		else 
		{
			chunk_list_insert(dest, chunk.start, chunk.size);
		}
	}
}

void chunk_list_remove(Chunk_List *list, size_t index)
{
	//make sure that the index is valid
	assert(index < list->count);

	//remove the elements
	for (size_t i = index; i < list->count - 1; i++)
	{
		list->chunks[i] = list->chunks[i+1];
	}

	list->count--;
}

void *heap_alloc(size_t size)
{
	if (size > 0)
	{
		//
		chunk_list_merge(&tmp_chunks, &freed_chunks);
		freed_chunks = tmp_chunks;

		//search for a chunk that is big enough
		for (size_t i = 0; i < freed_chunks.count; ++i)
		{
			const Chunk chunk = freed_chunks.chunks[i];
			if (chunk.size >= size)
			{
				Chunk chunk = freed_chunks.chunks[i];
				chunk_list_remove(&freed_chunks, i);

				// this will never be neg
				const size_t tail_size = chunk.size - size;
				chunk_list_insert(&allocated_chunks, chunk.start, size);

				if (tail_size > 0)
				{
					chunk_list_insert(&freed_chunks, chunk.start + size, tail_size);
				}

				return chunk.start;
			}
		}
	}
	//if we end the loop without returning, then we failed to find a chunk

	return NULL;
}

void heap_free(void *ptr)
{
	if (ptr != NULL)
	{
		const int index = chunk_List_find(&allocated_chunks, ptr);
		assert(index >= 0);
		chunk_list_insert(&freed_chunks, allocated_chunks.chunks[index].start,
						  allocated_chunks.chunks[index].size);
		chunk_list_remove(&allocated_chunks, (size_t)index);
	}
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
	for (int i = 0; i < 10; i++)
	{

		void *p = heap_alloc(i);
		if (i % 2 == 0)
		{
			heap_free(p);
		}

	}
	heap_alloc(10);
	chunk_list_dump(&allocated_chunks);
	chunk_list_dump(&freed_chunks);

	return 0;
}
