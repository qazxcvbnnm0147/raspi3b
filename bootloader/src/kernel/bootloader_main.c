#include "kernel/gpio.h"
#include "kernel/uart.h"

void bootloader_main(void)
{
    volatile int clr = 0;
    clr = uart_init();
    while(clr == 0);
    uart_puts("ready to bootload\n");
    while(1)
    {
        if(uart_getc()=='!')
        {
            uart_puts("confirm\n");
            break;
        }
           
    }
    uart_puts("start bootloading...\n");

    unsigned int kernel_size = 0;
    char *kernel_addr = (char *)0x80000;
    unsigned char recv[4];

    // since the data is little endian, LSB will at lowest address(first received)
    recv[0] = uart_getc();
    kernel_size = recv[0];
    recv[1] = uart_getc();
    kernel_size |= (recv[1] << 8);
    recv[2] = uart_getc();
    kernel_size |= (recv[2] << 16);
    recv[3] = uart_getc();
    kernel_size |= (recv[3] << 24);

    while(kernel_size>0)
    {
        *kernel_addr = uart_getc();
        kernel_addr++;
        kernel_size--;
    }

    uart_puts("Kernel transmission completed\n");
    // x30 is link register(lr), record return address(usuallt used when bl is called)
    // here we use it as our path to our shell kernel as 'ret' will return to return address
    asm volatile(
        "mov x0, x10;"
        "mov x1, x11;"
        "mov x2, x12;"
        "mov x3, x13;"
        "mov x30, 0x80000;"
        "ret;"
    );
        
    
}