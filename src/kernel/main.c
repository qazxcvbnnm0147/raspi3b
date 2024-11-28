#include "kernel/gpio.h"
#include "kernel/uart.h"
#include "kernel/shell.h"
#include "kernel/cpio.h"
#include "kernel/simple_alloc.h"
#include "kernel/dtb.h"

char *cpio_addres ;


void main(void)
{
    volatile int clr = 0;
    clr = uart_init();
    while(clr == 0);
    uart_puts("hello_words!\n");


    char *string = simple_malloc(8);

    string[0] = 'S';
    string[1] = 't';
    string[2] = 'r';
    string[3] = 'i';
    string[4] = 'n';
    string[5] = 'g';
    string[6] = '!';
    string[7] = '\0';
    uart_puts(string);
    uart_putc('\n');

    fdt_traverse(initramfs_callback);

    shell();
}