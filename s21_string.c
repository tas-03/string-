#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
    char *destin = (char *)dest;
    const char *source = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        destin[i] = source[i];
    }
    return dest;
}


void *s21_memset(void *str, int c, size_t n) {
    unsigned char *elem = (unsigned char *)str;
    for (size_t i = 0; i < n; i++) {
        elem[i] = (unsigned char)c;
    }
    return str;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}



size_t s21_strcspn(const char *str1, const char *str2){
    int flag = 0;
    size_t result = s21_strlen(str1);
    for(int i = 0; (str1[i] != '\0') && (flag == 0); i++){
        for(int j = 0; (str2[j] != '\0') && (flag == 0); j++){
        if (str1[i] == str2[j]) {
            result = i;
            flag = 1;
        }
        }
    }
    return result;
}


int s21_memcmp(const void *str1, const void *str2, size_t n){
    int result = 0, flag = 0;
    const unsigned char *ptr1 = (const unsigned char *)str1;
    const unsigned char *ptr2 = (const unsigned char *)str2;

    for(size_t i = 0; i < n && flag == 0; i++){
        if (ptr1[i] != ptr2[i]){
            result = ptr1[i] - ptr2[i];
            flag = 1;
        }
    }
    return result;
}



char *s21_strtok(char *string1, const char *string2) {
  static char *last = s21_NULL;
  char *start = s21_NULL;
  char *c = s21_NULL;
  int found = 0;
  int flag = 0;

  if (string2 == s21_NULL) {
    flag = 1;
  }

  if (string1 != s21_NULL) {
    last = string1;
  }

  if (last == s21_NULL || *last == '\0') {
    flag = 1;
  }

  c = last;
  while (*c != '\0' && s21_strchr(string2, *c) != s21_NULL) {
    c++;
    found = 1;
  }
  if (found && *c == '\0') {
    last = c;
    flag = 1;
  }
  start = c;
  found = 0;
  while (*c != '\0') {
    if (s21_strchr(string2, *c) != s21_NULL) {
      found = 1;
      break;
    }
    c++;
  }

  if (found) {
    *c = '\0';
    last = c + 1;
  } else {
    last = c;
  }
  if (flag == 1) {
    start = s21_NULL;
  }
  return start;
}





s21_size_t  s21_strlen(const char *str){
    s21_size_t length =0;
    for (;*(str+length); length++);
    return length;
}

char * s21_strrchr(const char *str, int c){
s21_size_t length = 0;
int size =  s21_strlen(str);
char *new_str=s21_NULL; 
for (;*(str+length); length++){
    if (*(str+length) == (char)c){
        new_str= (char*)(str + length);
    }
}
if (new_str == s21_NULL){
    new_str="(null)";
}
return new_str;
}

char *s21_strchr(const char *str, int c){
s21_size_t length = 0;
int flag=0;
int size =  s21_strlen(str);
char *new_str=s21_NULL; 
for (;*(str+length); length++){
    if (*(str+length) == (char)c && !flag){
        new_str= (char*)(str + length);
        flag=1;
    }
}
return (new_str);
}

char *s21_strstr(const char *haystack, const char *needle){
s21_size_t len_haystack = 0, len_needle=0, len=0;
int flag=0;
s21_size_t size =  s21_strlen(haystack);
char *new_str=s21_NULL; 
for (;*(haystack+len_haystack); len_haystack++){
    if(*(haystack+len_haystack) == *needle && !flag){
        len = len_haystack;
        new_str= (char*)(haystack + len_haystack);
        for (;*(needle+len_needle);len_needle++){
            if ( *(haystack + len) == *(needle+len_needle)){
                len++;
            } else {
                new_str=s21_NULL;
                len_needle == s21_strlen(needle);
            }
        }
    }
    if(new_str!=s21_NULL){
        flag=1;
    }    
}
return new_str;
}

void *s21_memchr(const void *str, int c, size_t n){
const unsigned char *p =(const unsigned char *)str; 
char *new_str=s21_NULL;
for (size_t i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c && new_str==s21_NULL) {
        new_str=(char*)(p+i); 
    }
}
if (new_str == s21_NULL){
    new_str="(null)";
}
return new_str;
}

char *s21_strpbrk(const char *str1, const char *str2){
s21_size_t len_str1 = 0, len_str2=0;
char *new_str=s21_NULL; 
for (;*(str1+len_str1); len_str1++){
    for (;*(str2+len_str2);len_str2++){
        if ( *(str1+len_str1) == *(str2+len_str2) && new_str==s21_NULL){
            new_str=(char*)(str1+len_str1);
            }
        }  
    len_str2=0;
}
if (new_str == s21_NULL){
    new_str="(null)";
}
return new_str;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
    char *dest_start = dest;
    size_t copied = 0;
    
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    
    while (*dest != '\0') {
        dest++;
    }
    
    while (*src != '\0' && copied < n) {
        *dest = *src;
        dest++;
        src++;
        copied++;
    }
    
    *dest = '\0';
    
    return dest_start;
}



int main(){
    char *str="sjhooo";
    s21_size_t size =  s21_strlen(str);
    printf("s21_strlen: %llu\n", size);
    char *str1="sjhOOO";
    char *result = to_upper(str1);
    printf("%s", result);
    free(result);
    return 0;
}

// функции допы
// верхний регистр 65-90
// разница 32
// нижний регистр 97-122

void *to_upper(const char *str){                                                           
    char *new_str = (char *)malloc(s21_strlen(str) + 1);
    if (new_str == NULL) {
        return NULL;
    }

    for(int i=0; i<=s21_strlen(str); i++){
        if(str[i]>=97 && str[i]<=122){
            new_str[i]=str[i]-32;
        } else {
            new_str[i]=str[i];
        }
    }
    new_str[s21_strlen(str) + 1]='\0';
    return (new_str);
}

                                                           
void *to_lower(const char *str){                                              
    char *new_str = (char *)malloc(s21_strlen(str) + 1);
    if (new_str == NULL) {
        return NULL; 
    }
    for(int i=0; i<=s21_strlen(str); i++){
        if(str[i]>=65 && str[i]<=90){
            new_str[i]=str[i]+32;
        } else {
            new_str[i]=str[i];
        }
    }
    new_str[s21_strlen(str) + 1]='\0';
    return (new_str);
}


void *insert(const char *src, const char *str, size_t start_index){

}

void *trim(const char *src, const char *trim_chars){

}