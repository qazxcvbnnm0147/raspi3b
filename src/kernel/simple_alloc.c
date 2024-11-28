#include "kernel/simple_alloc.h"
#include "kernel/uart.h"

char *allocated = &__end;
int offset=0;

void* simple_malloc(unsigned int size)
{
    void* ret = (void*)allocated;
    if(offset + size > HEAP_SIZE)
    {
        uart_puts("heap memory exceed\n");
        return 0;
    }
    offset = offset + size;
    allocated = allocated + size;
    return ret; 
}