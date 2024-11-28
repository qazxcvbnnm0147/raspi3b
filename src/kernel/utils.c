#include "kernel/utils.h"
#include "kernel/dtb.h"

int string_compare(const char *a , const char *b ,int compare_len )
{
    if(!compare_len)
    {   
        while(*a != '\0')
        {
            if(*a != *b)
                return 0;
            a++;
            b++;
        }
        if(*b != '\0')
            return 0;
        return 1;
    }
    else
    {
        for(int i=0;i<compare_len;i++)
        {
            if(*a != *b)
                return 0;
        }
        return 1;
    }

}


int string_len(const char* str){
    int i = 0;

    while(1){
        if(*(str + i) == '\0' || *(str + i) == '\n')
            break;
        i++;
    }

    return i;
}

unsigned int BE2LE(unsigned int BE){
    unsigned int LE = 0;
    int i = 24;

    for(; i >= 0; i -= 8){
        LE |= (((BE >> i) & 0xFF) << (24 - i));
    }

    return LE;
}


void memset(void *ptr, int value, int size_num) {
    unsigned char *p = (unsigned char *)ptr;  // 轉換指針類型
    while (size_num--) {
        *p++ = (unsigned char)value;          // 設置每個字節為指定的值
    }                            
}
int h2i(char* hex, int size)
{
    int decimal_value = 0;


    for (int i =0;i<8;i++)
    {
        char ch = *(hex+i);  
        int digit_value = 0;
        if (ch >= '0' && ch <= '9') {
            digit_value = ch - '0';  
        } else if (ch >= 'A' && ch <= 'F') {
            digit_value = ch - 'A' + 10; 
        } else {
            return -1;
        }
        decimal_value = decimal_value * 16 + digit_value;
    }

    return decimal_value;
}
int align4(int ptr) {
    if(ptr%4==0)
        return ptr;
    int offset = 4-(ptr % 4); 
    return ptr+offset;
}

int align_mem_offset(void* i, unsigned int align){
    // unsigned long long seemed not work properly?
    uintptr_t l = (uintptr_t)i;
    return ((align - (l % align) ) % align);
}