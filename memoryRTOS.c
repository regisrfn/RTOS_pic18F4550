#include "memoryRTOS.h"

void *get_memory_from_heap(size_t len)
{
    static uint8_t *p;
    static size_t length;
    static  uint8_t *max_size_of_heap = (heap + HEAP_SIZE);
    
    length = len;
    
    p = pointer_to_heap;
    pointer_to_heap += length;
    if (pointer_to_heap >= max_size_of_heap)
        return NULL;
    else
        return p;
}

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  static struct block_meta *current; 
  current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
  static struct block_meta *block;
  static struct block_meta *last_block;
  static size_t size_of_block;
  
  size_of_block = size;
  last_block = last;
  block =  get_memory_from_heap(0);
  
  static void *request; 
  request = get_memory_from_heap(size + META_SIZE);
  //assert((void*)block == request); // Not thread safe.
  if (request == NULL) {
    return NULL; // sbrk failed.
  }

  if (last_block) {
    last_block->next = block;
  }
  block->size = size_of_block;
  block->next = NULL;
  block->free = 0;
  //block->magic = 0x12345678;
  return block;
}

void *malloc(size_t size) {
  static struct block_meta *block;
  // TODO: align size?

  if (size <= 0) {
    return NULL;
  }

  if (!global_base) { // First call.
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    static struct block_meta *last; 
    last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      // Found free block
      // TODO: consider splitting block here.
      block->free = 0;
      //block->magic = 0x77777777;
    }
  }
  
  //same as start of the block + sizeof(struct(block_meta))
  //the space after the metadeta
  return(block+1); 
}