#include "s21_string.h"

typedef struct {
  int minus;
  int plus;
  int space;
  int zero;
  int hash;

  int h;
  int l;
  int L;
  int h_count;  // количество h
  int l_count;  // количество l

  int c;
  int d;
  int i;
  int f;
  int s;
  int u;
  int percent;

  int width;
  int precision;
} format_options;

int s21_sprintf(char* str, const char* format, ...);
int parser(va_list args, const char* format, char* str);
int parse_persent(char* str, int* i, int* count, const char* format);
format_options parse_format(const char* format, int* i);
format_options parser_flags(const char* format, int* i, format_options opt);
format_options parser_width(const char* format, int* i, format_options opt);
format_options parser_precision(const char* format, int* i, format_options opt);
format_options parser_length(const char* format, int* i, format_options opt);
format_options parser_specificators(const char* format, int* i,
                                    format_options opt);
int process_specifiers(va_list args, char* str, format_options opt);
int process_char(int c, char* str, format_options opt);
int process_string(const char* s, char* str, format_options opt);
int count_numbers(int c);
void* array_numbers(int c, int count);
int minus_int(int i, int n_zeros, int count, format_options opt, char* str,
              int c, int* arr);
int minus_int_else(int i, int n_zeros, int space, int count, format_options opt,
                   char* str, int c, int* arr);
int process_int(int c, char* str, format_options opt);
int process_unsigned_int(int c, char* str, format_options opt);
int process_float(double num, char* str, format_options opt);
char* s21_strcpy(char* dest, const char* src);
void s21_itoa(long num, char* buffer, int base);
int process_float_prefix(double num, char* buffer, format_options opt);
int process_float_number(double num, char* buffer, int precision, char* int_str,
                         char* frac_str, format_options opt, char* sign_char);
int process_float_width(char* str, const char* buffer, int len, int width,
                        format_options opt);

int s21_sprintf(char* str, const char* format, ...) {
  int count = 0;
  va_list args;
  va_start(args, format);
  count = parser(args, format, str);
  va_end(args);
  str[count] = '\0';
  return count;
}

int parser(va_list args, const char* format, char* str) {
  int count = 0;
  format_options opt = {0};
  for (int i = 0; format[i]; i++) {
    if (format[i] == '%') {
      i++;
      if (parse_persent(str, &i, &count, format) == 0) {
        continue;
      }
      opt = parse_format(format, &i);
      count += process_specifiers(args, str + count, opt);
    } else {
      str[count] = format[i];
      count++;
    }
  }
  return count;
}

int parse_persent(char* str, int* i, int* count, const char* format) {
  int flag = 0;
  if (format[*i] == '%') {
    str[*count] = format[*i];
    (*count)++;
  } else
    flag = 1;
  return flag;
}

format_options parse_format(const char* format, int* i) {
  format_options options = {0};
  options.precision = -1;
  options.width = -1;
  options = parser_flags(format, i, options);
  options = parser_width(format, i, options);
  options = parser_precision(format, i, options);
  options = parser_length(format, i, options);
  options = parser_specificators(format, i, options);
  return options;
}

format_options parser_flags(const char* format, int* i, format_options opt) {
  while (format[*i] == '-' || format[*i] == '+' || format[*i] == ' ' ||
         format[*i] == '0') {
    switch (format[*i]) {
      case '-':
        opt.minus = 1;
        (*i)++;
        continue;
      case '+':
        opt.plus = 1;
        (*i)++;
        continue;
      case ' ':
        opt.space = 1;
        (*i)++;
        continue;
      case '0':
        opt.zero = 1;
        (*i)++;
        continue;
      default:
        break;
    }
  }
  if (opt.minus == 1) {  // если указан флаг -, то 0 игнорируется
    opt.zero = 0;
  }
  if (opt.plus == 1) {  // если указан флаг +, то пробел игнорируется
    opt.space = 0;
  }
  return opt;
}

format_options parser_width(const char* format, int* i, format_options opt) {
  while (format[*i] >= '0' && format[*i] <= '9') {
    if (opt.width == -1) {
      opt.width = 0;
    }
    opt.width = opt.width * 10 + (format[*i] - '0');
    (*i)++;
  }
  return opt;
}

format_options parser_precision(const char* format, int* i,
                                format_options opt) {
  if (format[*i] == '.') {
    (*i)++;
    opt.precision = 0;
    int has_digits = 0;
    while (format[*i] >= '0' && format[*i] <= '9') {
      opt.precision = opt.precision * 10 + (format[*i] - '0');
      (*i)++;
      has_digits = 1;
    }
    if (!has_digits) {
      opt.precision = 0;
    }
  }
  return opt;
}

format_options parser_length(const char* format, int* i, format_options opt) {
  while (format[*i] == 'h' || format[*i] == 'l') {
    switch (format[*i]) {
      case 'h':
        opt.h = 1;
        opt.h_count++;
        (*i)++;
        continue;
      case 'l':
        opt.l = 1;
        opt.l_count++;
        (*i)++;
        continue;
      default:
        break;
    }
  }
  return opt;
}

format_options parser_specificators(const char* format, int* i,
                                    format_options opt) {
  int flag = 0;  // флаг на найденный спецификатор
  while (!flag) {
    switch (format[*i]) {
      case 'c':
        opt.c = 1;
        flag = 1;
        continue;
      case 'd':
      case 'i':
        opt.d = 1;
        flag = 1;
        continue;
      case 'f':
        opt.f = 1;
        flag = 1;
        continue;
      case 'u':
        opt.u = 1;
        flag = 1;
        continue;
      case 's':
        opt.s = 1;
        flag = 1;
        continue;
      default:
        flag = 1;
        break;
    }
  }
  return opt;
}

int process_specifiers(va_list args, char* str, format_options opt) {
  int res = 0;
  if (opt.c) {
    res = process_char(va_arg(args, int), str, opt);
  } else if (opt.d || opt.i) {
    if (opt.h) {
      if (opt.h_count > 1)
        res = process_int((signed char)va_arg(args, int), str, opt);
      else
        res = process_int((short int)va_arg(args, int), str, opt);
    } else if (opt.l) {
      res = process_int((long int)va_arg(args, long int), str, opt);
    } else {
      res = process_int(va_arg(args, int), str, opt);
    }
  } else if (opt.u) {
    if (opt.h) {
      if (opt.h_count > 1)
        res = process_unsigned_int((unsigned char)va_arg(args, unsigned int),
                                   str, opt);
      else
        res = process_unsigned_int(
            (unsigned short int)va_arg(args, unsigned int), str, opt);
    } else if (opt.l) {
      res = process_unsigned_int(
          (unsigned long int)va_arg(args, unsigned long int), str, opt);
    } else {
      res = process_unsigned_int(va_arg(args, unsigned int), str, opt);
    }
  } else if (opt.f) {
    res = process_float(va_arg(args, double), str, opt);
  } else if (opt.s) {
    res = process_string(va_arg(args, char*), str, opt);
  } else if (opt.percent) {
    str[res++] = '%';
  }

  return res;
}

// int process_char(int c, char* str, format_options opt) {
//     int count = 0;
//     if (opt.percent == 1) {
//         str[count++] = '%';
//         opt.percent = 0;
//     } else {
//         if (opt.minus == 0 && opt.width > 1) {
//             for (int i = 0; i < opt.width - 1; i++) {
//                 str[count++] = ' ';
//             }
//             str[count++] = (char)c;
//         } else if (opt.minus == 1 && opt.width > 1) {
//             str[count++] = (char)c;
//             for (int i = 1; i != opt.width; i++) {
//                 str[count++] = ' ';
//             }
//         } else {
//             str[count++] = (char)c;
//         }

//     }
//     return count;
// }

int process_char(int c, char* str, format_options opt) {
  int count = 0;
  int width = opt.width > 0 ? opt.width : 1;

  if (opt.minus) {
    // Символ слева
    str[count++] = (char)c;
    while (count < width) str[count++] = ' ';
  } else {
    // Пробелы слева
    while (count < width - 1) str[count++] = ' ';
    str[count++] = (char)c;
  }

  return count;
}

int process_string(const char* s, char* str, format_options opt) {
  if (s == NULL) s = "(null)";
  int input_len = s21_strlen(s);
  int output_len = input_len;
  if (opt.precision != -1 && opt.precision < output_len)
    output_len = opt.precision;
  int padding = opt.width > output_len ? opt.width - output_len : 0;
  int total_len = output_len + padding;
  int i = 0;
  if (opt.minus) {
    s21_memcpy(str, s, output_len);
    i += output_len;
    s21_memset(str + i, ' ', padding);
  } else {
    s21_memset(str, ' ', padding);
    s21_memcpy(str + padding, s, output_len);
  }
  return total_len;
}

int count_numbers(int c) {
  if (c == 0) return 1;
  int count = 0;
  c = abs(c);
  while (c > 0) {
    count++;
    c /= 10;
  }
  return count;
}

void* array_numbers(int c, int count) {
  int* arr = malloc(count * sizeof(int));
  if (arr) {
    int abs_c = abs(c);
    for (int i = count - 1; i >= 0; i--) {
      arr[i] = abs_c % 10;
      abs_c /= 10;
    }
  }
  return arr;
}

int process_int(int c, char* str, format_options opt) {
  int count = count_numbers(c);
  int original_count = count;
  int precision = opt.precision == -1 ? 1 : opt.precision;
  int zero = (precision > count) ? (precision - count) : 0;
  if (c == 0 && opt.precision == 0) {
    count = 0;
    zero = 0;
  }
  int total_len = count + zero;
  int sign_len = (c < 0 || opt.plus || opt.space) ? 1 : 0;
  int space = 0;
  if (opt.width > (total_len + sign_len)) {
    space = opt.width - (total_len + sign_len);
  }
  int* arr = array_numbers(c, original_count);
  if (!arr) return 0;
  int i = 0;
  if (opt.minus) {
    if (c < 0)
      str[i++] = '-';
    else if (opt.plus)
      str[i++] = '+';
    else if (opt.space)
      str[i++] = ' ';
    for (int j = 0; j < zero; j++) str[i++] = '0';
    if (!(c == 0 && opt.precision == 0)) {
      for (int j = 0; j < original_count; j++) str[i++] = arr[j] + '0';
    }
    while (space-- > 0) str[i++] = ' ';
  } else {
    if (!opt.zero) {
      while (space-- > 0) str[i++] = ' ';
    }
    if (c < 0)
      str[i++] = '-';
    else if (opt.plus)
      str[i++] = '+';
    else if (opt.space)
      str[i++] = ' ';
    if (opt.zero) {
      while (space-- > 0) str[i++] = '0';
    }
    for (int j = 0; j < zero; j++) str[i++] = '0';
    if (!(c == 0 && opt.precision == 0)) {
      for (int j = 0; j < original_count; j++) str[i++] = arr[j] + '0';
    }
  }
  free(arr);
  return i;
}

int process_unsigned_int(int c, char* str, format_options opt) {
  int zero = 0, space = 0;
  int count = count_numbers(c);
  int i = 0;
  int n_zeros = 0;
  int* arr = array_numbers(c, count);
  if (arr == NULL) {
    return 0;
  }
  if (count < opt.precision) {
    zero = opt.precision - count;
  }
  if (count + zero < opt.width && opt.width != -1) {
    space = opt.width - zero - count;
  }
  n_zeros = zero;
  if (opt.minus == 1) {
    for (; i < n_zeros; i++) {
      str[i] = '0';
    }
    for (int j = 0; j <= count - 1; j++) {
      str[i] = arr[j] + '0';
      i++;
    }
    for (; i < opt.width; i++) {
      str[i] = ' ';
    }
  } else {
    for (; i < space; i++) {
      str[i] = ' ';
    }
    for (; i < n_zeros + space; i++) {
      str[i] = '0';
    }
    for (int j = 0; j <= count - 1; j++) {
      str[i] = arr[j] + '0';
      i++;
    }
  }
  free(arr);
  return i;
}

int process_float_prefix(double num, char* buffer, format_options opt) {
  int len = 0;
  char sign = '\0';
  if (isnan(num)) {
    if (opt.plus) {
      buffer[len++] = '+';
    } else if (opt.space) {
      buffer[len++] = ' ';
    }
    s21_strcpy(buffer + len, "nan");
    len += 3;
  } else if (isinf(num)) {
    if (num < 0) {
      sign = '-';
    } else if (opt.plus) {
      sign = '+';
    } else if (opt.space) {
      sign = ' ';
    }
    if (sign != '\0') {
      buffer[len++] = sign;
    }
    s21_strcpy(buffer + len, "inf");
    len += 3;
  }
  return len;
}

int process_float_number(double num, char* buffer, int precision, char* int_str,
                         char* frac_str, format_options opt, char* sign_char) {
  int len = 0;
  int is_negative = num < 0;
  if (is_negative) {
    num = -num;
    *sign_char = '-';
  } else if (opt.plus) {
    *sign_char = '+';
  } else if (opt.space) {
    *sign_char = ' ';
  }

  double integer_part;
  double fractional = modf(num, &integer_part);
  s21_itoa((long)integer_part, int_str, 10);
  double frac_temp = fractional;
  int carry = 0;
  for (int i = 0; i < precision; i++) {
    frac_temp *= 10;
    int digit = (int)frac_temp;
    frac_str[i] = digit + '0';
    frac_temp -= digit;
  }
  frac_temp *= 10;
  int next_digit = (int)(frac_temp + 1e-10);

  if (next_digit >= 5) {
    int i = precision - 1;
    while (i >= 0 && frac_str[i] == '9') {
      frac_str[i] = '0';
      i--;
    }
    (i >= 0) ? (frac_str[i]++) : (carry = 1);
  }
  if (carry) {
    long new_int = (long)integer_part + 1;
    s21_itoa(new_int, int_str, 10);
  }
  if (*sign_char) buffer[len++] = *sign_char;
  s21_strcpy(buffer + len, int_str);
  len += s21_strlen(int_str);
  if (precision > 0 || opt.hash) {
    buffer[len++] = '.';
    if (precision > 0) {
      s21_strcpy(buffer + len, frac_str);
      len += precision;
    }
  }
  return len;
}

int process_float_width(char* str, const char* buffer, int len, int width,
                        format_options opt) {
  if (width > len) {
    if (opt.minus) {
      s21_strcpy(str, buffer);
      s21_memset(str + len, ' ', width - len);
    } else {
      char pad_char = (opt.zero && !opt.minus) ? '0' : ' ';
      s21_memset(str, pad_char, width - len);
      s21_strcpy(str + (width - len), buffer);
    }
    return width;
  } else {
    s21_strcpy(str, buffer);
    return len;
  }
}

int process_float(double num, char* str, format_options opt) {
  char buffer[256] = {0};
  int len = 0;
  len = process_float_prefix(num, buffer, opt);

  int precision = opt.precision == -1 ? 6 : opt.precision;

  if (!isnan(num) && !isinf(num)) {
    char int_str[64] = {0};
    char frac_str[64] = {0};
    char sign_char = '\0';
    len += process_float_number(num, buffer, precision, int_str, frac_str, opt,
                                &sign_char);
  }
  return process_float_width(str, buffer, len, opt.width, opt);
}

void s21_itoa(long num, char* buffer, int base) {
  int i = 0;
  int is_negative = 0;
  if (num < 0 && base == 10) {
    is_negative = 1;
    num = -num;
  }
  if (num == 0) {
    buffer[i++] = '0';
    return;
  }
  char temp[64];
  int temp_index = 0;
  while (num > 0) {
    int remainder = num % base;
    temp[temp_index++] =
        (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
    num /= base;
  }
  if (is_negative) {
    buffer[i++] = '-';
  }
  while (temp_index > 0) {
    buffer[i++] = temp[--temp_index];
  }
}
