#include "kernel/uart.h"
#include "kernel/shell.h"
#include "kernel/utils.h"
#include "kernel/mbox.h"
#include "kernel/reboot.h"
#include "kernel/cpio.h"

void shell()
{
    uart_puts("welcome to use shell, please enter # +cmd :\n");
    char buf[MAX_BUF_LEN]; 
    int i;
    char c;
    while(1)
    {
        uart_puts("# ");
        i=0;
        memset(buf, 0,MAX_BUF_LEN);
        while(1)
        {
            c = uart_getc();
            if(c > 127 || c < 0){
                uart_puts("\nwarning: Get non ASCII code\n");
                continue;
            }
            uart_putc(c); 
            buf[i++] = c;
            if(i>=MAX_BUF_LEN)
                uart_puts("\nwarning: Exceed maximun buffer size\n");
            if(c=='\n')
            {
                buf[i-1] = '\0';
                break;
            }  
         
        }
        if(string_compare(buf,"help",0))
        {
            uart_puts("# help     : print this help menu\n");
            uart_puts("# hello    : print Hello World!\n");
            uart_puts("# reboot   : reboot the device\n");
            uart_puts("# info     : get revision and memmory\n");
            uart_puts("# ls       : get all file name\n");
            uart_puts("# cat      : get the content of file\n");
        }
        else if(string_compare(buf,"hello",0))
            uart_puts("Hello World!\n");
        else if(string_compare(buf,"info",0))
        {
            get_board_revision();
            get_ARM_memory();
        }
        else if(string_compare(buf,"reboot",0))
        {
            uart_puts("after 1s start rebooting...\n");
            reset(16);
            //uart_puts("reboot complete\n"); cant run here
        }
        else if(string_compare(buf,"ls",0))
        {
            ls();
        }
        else if(string_compare(buf,"cat",0))
        {
            uart_puts("Filename: ");
            i=0;
            memset(buf, 0,MAX_BUF_LEN);
            while(1)
            {
                c = uart_getc();
                if(c > 127 || c < 0){
                    uart_puts("\nwarning: Get non ASCII code\n");
                    continue;
                }
                uart_putc(c); 
                buf[i++] = c;
                if(i>=MAX_BUF_LEN)
                    uart_puts("\nwarning: Exceed maximun buffer size\n");
                if(c=='\n')
                {
                    buf[i-1] = '\0';
                    break;
                }  
            }
            cat(buf);
        }
        else
            uart_puts("Unrecognized command\n");
    }
   
}

