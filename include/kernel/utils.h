#ifndef UTILS_H
#define UTILS_H

int string_compare(const char *a , const char *b,int compare_len );
void memset(void *ptr, int value, int size_num);
int align4(int ptr);
int h2i(char* hex, int size);
unsigned int BE2LE(unsigned int BE);
int align_mem_offset(void* i, unsigned int align);
int string_len(const char* str);

#endif