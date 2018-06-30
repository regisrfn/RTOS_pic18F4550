#include "memoryRTOS.h"

void *get_memory_from_heap(size_t len) {
    static uint8_t *p;
    static size_t length;
    static uint8_t *max_size_of_heap = (heap + HEAP_SIZE);

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
    static struct block_meta **last_block;

    current = global_base;
    last_block = last;

    while (current && !(current->free && current->size >= size)) {
        *last_block = current;
        current = current->next;
    }
    return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
    static struct block_meta *block, *last_block;
    static size_t block_size;

    block_size = size;
    last_block = last;
    block = get_memory_from_heap(0);
    void *request = get_memory_from_heap(size + META_SIZE);

    if (request == NULL) {
        return NULL; // sbrk failed.
    }

    if (last_block) { // NULL on first request.
        last_block->next = block;
    }
    block->size = block_size;
    block->next = NULL;
    block->free = 0;

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
        } else { // Found free block
            // TODO: consider splitting block here.
            block->free = 0;
            //block->magic = 0x77777777;
        }
    }

    //same as start of the block + sizeof(struct(block_meta))
    //the space after the metadeta
    return (block + 1);
}

struct block_meta *get_block_ptr(void *ptr) {
    static  void *pointer_to_free;
    pointer_to_free = ptr;
    return (struct block_meta*) pointer_to_free - 1;
}

void free(void *ptr) {
    static  void *pointer;
    pointer = ptr;
    
    if (!pointer) {
        return;
    }

    // TODO: consider merging blocks once splitting blocks is implemented.
    static struct block_meta* block_ptr;
    block_ptr = ((struct block_meta*)pointer)-1;
    block_ptr->free = 1;
}

