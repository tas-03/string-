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
    char *str="Hello Worldo ";
    s21_size_t size =  s21_strlen(str);
    printf("s21_strlen: %llu\n", size);
    
    char *str1="sjhOOO";
    printf("s21_strlen: %llu\n", s21_strlen(str1));
    char *result = to_upper(str1);
    char *result2 = insert(str, str1, 3);
    printf("insert %s\n", result2);
    printf("to_upper %s\n", result);
    char* rr="o ";
    char *result3=trim(str,rr);
    printf("trim %s\n", result3);
    free(result);
    free(result2);
    return 0;
}

// функции допы
// верхний регистр 65-90
// разница 32
// нижний регистр 97-122

void *to_upper(const char *str){
    int flag=0;                                                           
    char *new_str = (char *)malloc(s21_strlen(str) + 1);
    if (new_str == NULL) {
        flag=1; 
    }
    if(!flag){
        for(int i=0; i<=s21_strlen(str); i++){
            if(str[i]>=97 && str[i]<=122){
                new_str[i]=str[i]-32;
            } else {
                new_str[i]=str[i];
            }
        }
        new_str[s21_strlen(str) + 1]='\0';
    }
    
    return (void *)new_str;
}

                                                           
void *to_lower(const char *str){              
    int flag=0;                                
    char *new_str = (char *)malloc(s21_strlen(str) + 1);
    if (new_str == NULL) {
       flag=1;
    }
    if(!flag){
        for(int i=0; i<=s21_strlen(str); i++){
            if(str[i]>=65 && str[i]<=90){
                new_str[i]=str[i]+32;
            } else {
                new_str[i]=str[i];
            }
        }
        new_str[s21_strlen(str) + 1]='\0';
    }
    return (void *) new_str;
}


void *insert(const char *src, const char *str, size_t start_index){
    int flag=0;
    char *new_str = (char *)malloc(s21_strlen(str) + s21_strlen(src) + 1);
    if (new_str == NULL) {
        flag=1;
    } 
    int k=0, i;
    if (!flag){
        s21_memcpy(new_str, src, start_index);
    for(i = start_index; i<s21_strlen(str) + start_index; i++, k++){
        new_str[i] = str[k];
    }
    int j= start_index,o=0;
    for ( i = start_index+s21_strlen(str); j<=s21_strlen(src); i++, j++){
        new_str[i] = src[j];
    }
    new_str [i] = '\0';
    }
    return (void *) new_str;
}

void *trim(const char *src, const char *trim_chars){
    int flag=0;
    char *new_str = (char *)malloc(s21_strlen(src)+1);
    if (new_str == NULL) {
        flag =1;
    } 
    if (!flag){
        if (deletion_first(src,trim_chars,new_str)==0){
            copy(src, 0, new_str);
        }else{
            deletion_last(src,trim_chars,new_str);
        }
    }
    return (void *) new_str;
}


int deletion_first(const char *src, const char *trim_chars, char* new_str){
    int flag=0;
for (int i=0; i<=s21_strlen(src); i++){
    for (int j=0;j<=s21_strlen(trim_chars); j++){
        if(trim_chars[j]==src[i]&&!flag){
            copy(src,i,new_str);
            flag=1;
            }      
        }
    }
return flag;
}
void deletion_last(const char *src, const char *trim_chars, char* new_str){
    int flag=0;
    for (int i=s21_strlen(src); i>=0; i--){
        for (int j=0;j<s21_strlen(trim_chars); j++){
            if(new_str[i]==trim_chars[j]&&flag==0){
                new_str[i]='\0';
                flag=1;
                }      
            }
        }
}

void copy(const char *src, int i, char* new_str){
    int k=0;
    for(int j=i+1; j<=s21_strlen(src); j++, k++){
        new_str[k] = src[j];
    }
}