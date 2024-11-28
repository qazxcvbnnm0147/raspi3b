
#include "kernel/cpio.h"
#include "kernel/uart.h"
#include "kernel/utils.h"

//char *cpio_addres = (char*)QUME_CPIO;

void ls(void)
{
    char* temp = cpio_addres;
    struct cpio_newc_header *header = (struct cpio_newc_header *)temp;
    if(!string_compare(header->c_magic,"070701",6))
    {
        uart_puts("cpio magic value error");
        uart_puts(header->c_magic);
        return;        
    }
    int file_size = 0;
    int name_size = 0;
    char *next_header_addr = (char *)(header );

    while(!string_compare((char *)(header + 1),"TRAILER!!!",0))
    {
        char *file_name = (char *)(header + 1);
        uart_puts(file_name);
        uart_putc('\n');
        name_size = h2i(header->c_namesize,8);
        file_size = h2i(header->c_filesize,8);
        next_header_addr = next_header_addr + align4(name_size+cpio_struct_size) + align4(file_size);
        header = (struct cpio_newc_header *)next_header_addr;
    }
    
}

void cat(char *input_file_name)
{
    char* temp = cpio_addres;
    struct cpio_newc_header *header = (struct cpio_newc_header *)temp;
    if(!string_compare(header->c_magic,"070701",6))
    {
        uart_puts("cpio magic value error");
        uart_puts(header->c_magic);
        return;        
    }
    int file_size = 0;
    int name_size = 0;
    char *next_header_addr = (char *)(header );

    while(!string_compare((char *)(header + 1),"TRAILER!!!",0))
    {
        char *file_name = (char *)(header + 1);
        name_size = h2i(header->c_namesize,8);
        file_size = h2i(header->c_filesize,8);
        if(string_compare(input_file_name,file_name,0))
        {
            char *start_addr = file_name + name_size;
            int i=0;
            while(i<file_size)
            {
                uart_putc(*start_addr);
                start_addr++;
                i++;
            }
            return;
        }
        next_header_addr = next_header_addr + align4(name_size+cpio_struct_size) + align4(file_size);
        header = (struct cpio_newc_header *)next_header_addr;
    }
    uart_puts("File name does not match\n");
}