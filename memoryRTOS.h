// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <stdint.h>

#define HEAP_SIZE 512
uint8_t heap[HEAP_SIZE];
uint8_t *pointer_to_heap = heap;

struct block_meta {
  size_t size;
  struct block_meta *next;
  unsigned char free;
  //int magic; // For debugging only. TODO: remove this in non-debug mode.
};

void *global_base = NULL;

#define META_SIZE sizeof(struct block_meta)


void *get_memory_from_heap(size_t len);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
void *malloc(size_t size);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

