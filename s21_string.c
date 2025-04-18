#include "s21_string.h"

char *s21_strerror(int errnum) {
  static const char *strerr[] = s21_error;
  static char s21_undef[BUFF_SIZE] = {"Unknown error"};
  const char *res = S21_NULL;
  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
    res = s21_undef;
  } else {
    res = strerr[errnum];
  }
  return (char *)res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *destin = (char *)dest;
  const char *source = (const char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    destin[i] = source[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *elem = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    elem[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int flag = 0;
  s21_size_t result = s21_strlen(str1);
  for (int i = 0; (str1[i] != '\0') && (flag == 0); i++) {
    for (int j = 0; (str2[j] != '\0') && (flag == 0); j++) {
      if (str1[i] == str2[j]) {
        result = i;
        flag = 1;
      }
    }
  }
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  int diff_found = 0;
  while (n > 0 && *str1 && *str2 && !diff_found) {
    if (*str1 != *str2) {
      result = *(const unsigned char *)str1 - *(const unsigned char *)str2;
      diff_found = 1;
    }
    str1++;
    str2++;
    n--;
  }
  if (n > 0) {
    if (*str1 == '\0')
      result = -(*str2);
    else if (*str2 == '\0')
      result = *str1;
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0, flag = 0;
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n && flag == 0; i++) {
    if (ptr1[i] != ptr2[i]) {
      result = ptr1[i] - ptr2[i];
      flag = 1;
    }
  }
  return result;
}

char *s21_strtok(char *string1, const char *string2) {
  static char *last = S21_NULL;
  char *start = S21_NULL;
  char *c = S21_NULL;
  int found = 0;
  if (string2 == S21_NULL) return S21_NULL;

  if (string1 != S21_NULL) {
    last = string1;
  }

  if (last == S21_NULL || *last == '\0') return S21_NULL;

  c = last;
  while (*c != '\0' && s21_strchr(string2, *c) != S21_NULL) {
    c++;
    found = 1;
  }
  if (found && *c == '\0') {
    last = c;
    return S21_NULL;
  }
  start = c;
  found = 0;
  while (*c != '\0') {
    if (s21_strchr(string2, *c) != S21_NULL) {
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
  return start;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  for (; *(str + length); length++);
  return length;
}

char *s21_strrchr(const char *str, int c) {
  s21_size_t length = 0;
  char *new_str = S21_NULL;
  while (*(str + length)) {
    if (*(str + length) == (char)c) {
      new_str = (char *)(str + length);
    }
    length++;
  }
  if (c == '\0') {
    return (char *)(str + length);
  }
  return new_str;
}
char *s21_strchr(const char *str, int c) {
  s21_size_t length = 0;
  int flag = 0;

  char *new_str = S21_NULL;
  for (; *(str + length); length++) {
    if (*(str + length) == (char)c && !flag) {
      new_str = (char *)(str + length);
      flag = 1;
    }
  }
  if (c == '\0') {
    return (char *)(str + length);
  }
  return (new_str);
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len_haystack = 0, len_needle = 0, len = 0;
  char *new_str = S21_NULL;

  if (!*needle) return (char *)haystack;

  for (; *(haystack + len_haystack); len_haystack++) {
    if (*(haystack + len_haystack) == *needle) {
      len = len_haystack;
      new_str = (char *)(haystack + len_haystack);
      for (; *(needle + len_needle); len_needle++) {
        if (*(haystack + len) == *(needle + len_needle)) {
          len++;
        } else {
          new_str = S21_NULL;
          len_needle = s21_strlen(needle);
        }
      }
      if (new_str != S21_NULL) {
        return new_str;
      }
    }
  }
  return new_str;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = (const unsigned char *)str;
  char *new_str = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c && new_str == S21_NULL) {
      new_str = (char *)(p + i);
    }
  }
  return (void *)new_str;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len_str1 = 0, len_str2 = 0;
  char *new_str = S21_NULL;
  for (; *(str1 + len_str1); len_str1++) {
    for (; *(str2 + len_str2); len_str2++) {
      if (*(str1 + len_str1) == *(str2 + len_str2) && new_str == S21_NULL) {
        new_str = (char *)(str1 + len_str1);
        return new_str;
      }
    }
    len_str2 = 0;
  }
  return new_str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_start = dest;
  s21_size_t copied = 0;

  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
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

void *s21_to_upper(const char *str) {
  int flag = 0;
  char *new_str = (char *)malloc(s21_strlen(str) + 1);
  if (new_str == S21_NULL) {
    flag = 1;
  }
  if (!flag) {
    for (int i = 0; i < (int)s21_strlen(str); i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        new_str[i] = str[i] - 32;
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[s21_strlen(str)] = '\0';
  }

  return (void *)new_str;
}

void *s21_to_lower(const char *str) {
  int flag = 0;
  char *new_str = (char *)malloc(s21_strlen(str) + 1);
  if (new_str == S21_NULL) {
    flag = 1;
  }
  if (!flag) {
    for (int i = 0; i < (int)s21_strlen(str); i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        new_str[i] = str[i] + 32;
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[s21_strlen(str)] = '\0';
  }

  return (void *)new_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int flag = 0;
  char *new_str = (char *)malloc(s21_strlen(str) + s21_strlen(src) + 1);
  if (new_str == S21_NULL) {
    flag = 1;
  }
  if (!flag) {
    int k = 0, i;
    s21_memcpy(new_str, src, start_index);
    for (i = (int)start_index; i < (int)(s21_strlen(str) + start_index);
         i++, k++) {
      new_str[i] = str[k];
    }
    int j = (int)start_index;

    for (i = (int)(start_index + s21_strlen(str)); j <= (int)s21_strlen(src);
         i++, j++) {
      new_str[i] = src[j];
    }
    new_str[i] = '\0';
  }
  return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int flag = 0;
  char *new_str = (char *)malloc(s21_strlen(src) + 1);
  if (new_str == S21_NULL) {
    flag = 1;
  }
  if (!flag) {
    if (trim_chars == NULL) {
      trim_chars = " \t\n\r";
    }

    int start = 0;
    while ((s21_size_t)start < s21_strlen(src) &&
           is_trim_char(src[start], trim_chars)) {
      start++;
    }

    int end = s21_strlen(src) - 1;
    while (end >= 0 && is_trim_char(src[end], trim_chars)) {
      end--;
    }

    if (start > end) {
      new_str[0] = '\0';
    } else {
      int k = 0;
      for (int i = start; i <= end; i++) {
        new_str[k++] = src[i];
      }
      new_str[k] = '\0';
    }
  }
  return (void *)new_str;
}

int is_trim_char(char c, const char *trim_chars) {
  for (s21_size_t i = 0; i < s21_strlen(trim_chars); i++) {
    if (c == trim_chars[i]) {
      return 1;
    }
  }
  return 0;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

char *s21_strcpy(char *dest, const char *src) {
  char *original_dest = dest;
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return original_dest;
}
