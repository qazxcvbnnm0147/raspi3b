#include "kernel/mbox.h"
#include "kernel/uart.h"
volatile unsigned int  __attribute__((aligned(16))) mbox[36];


/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox_call()
{
    unsigned int r = (((unsigned int)((unsigned long)&mbox)&~0xF) | (MBOX_CH_PROP&0xF));
    /* wait until we can write to the mailbox */
    do{asm volatile("nop");}while(*MBOX_STATUS & MBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MBOX_WRITE = r;
    /* now wait for the response */
    while(1) {
        /* is there a response? */
        do{asm volatile("nop");}while(*MBOX_STATUS & MBOX_EMPTY);
        /* is it a response to our message? */
        if(r == *MBOX_READ)
            /* is it a valid successful response? */
            return mbox[1]==MBOX_RESPONSE;
    }
    return 0;
}

void get_board_revision(){
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = GET_BOARD_REVISION ;   // get  board revision command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

  //mbox_call(); // message passing procedure call, you should implement it following the 6 steps provided above.
  if (mbox_call()) {
        uart_puts("My board revision is: ");
        uart_hex(mbox[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query serial!\n");
    }
}

void get_ARM_memory(){
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = GET_ARM_MEMORY;   // get  arm memory command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

  //mbox_call(); // message passing procedure call, you should implement it following the 6 steps provided above.
  if (mbox_call()) {
        uart_puts("My ARM memory base address: ");
        uart_hex(mbox[5]);
        uart_puts("\n");
        uart_puts("My ARM memory size: ");
        uart_hex(mbox[6]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query serial!\n");
    }
}
