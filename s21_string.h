#ifndef S21_STRING_H
#define S21_STRING_H

#include "stdio.h"
#include "stdlib.h"

#define s21_size_t unsigned long long
#define s21_NULL (void*)0

char *s21_strncat(char *dest, const char *src, size_t n);
s21_size_t  s21_strlen(const char *str);
char * s21_strrchr(const char *str, int c);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strtok(char *string1, const char *string2);
int s21_memcmp(const void *str1, const void *str2, size_t n);
size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strncpy(char *dest, const char *src, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n);


#endif 