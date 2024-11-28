#ifndef SIMPLE_ALLOC_H
#define SIMPLE_ALLOC_H


#define HEAP_SIZE 8192
// Get the symbol __end from linker script
extern char __end;
// make allocated variable global among all files
extern char* allocated;
extern int offset;

void* simple_malloc(unsigned int size); 
#endif