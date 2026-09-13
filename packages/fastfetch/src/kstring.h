#ifndef STRING_H_FORGE
#define STRING_H_FORGE
#include <stddef.h>

size_t k_strlen(const char* s);
int k_strcmp(const char* a, const char* b);
int k_strncmp(const char* a, const char* b, size_t n);
void k_strcpy(char* dst, const char* src);
int k_streq(const char* a, const char* b);
void k_itoa(int val, char* buf);

#endif
