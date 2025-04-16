#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  // флаги
  int minus;
  int plus;
  int space;
  int zero;
  int hash;

  // длина  
  int h;
  int l;
  int L;
  int h_count; // количество h
  int l_count; // количество l

  // спецификаторы ???
  /*int d;
  unsigned int u;
  short int hd;
  short unsigned int hu;
  long int ld;
  long unsigned int lu;
  char c;
  double f;
  int s;
  char percent;*/

  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
  int percent;

  // ширина и точность  
  int width;
  int precision;
  int width_star;
  int precision_star;
} format_options;

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
            opt = parse_format(format, &i); 
            count += process_specifiers(args, str + count, opt);
        } else {
            str[count] = format[i];
            count++;
        }
    }
    return count;
}


format_options parse_format(const char* format, int* i) {
    format_options options = {0};
    options = parser_flags(format, i, options);
    //options = parser_width(format, i, options);
    //options = parser_precision(format, i, options);
    options = parser_length(format, i, options);
    options = parser_specificators(format, i, options);
    return options;

}


format_options parser_flags(const char* format, int* i, format_options opt) {
    while (format[*i] == '-' || format[*i] == '+' || format[*i] == ' ' || format[*i] == '0') {
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
    if (opt.minus == 1) { //Если указан флаг -, то флаг 0 игнорируется.
        opt.zero = 0; 
    } 
    if (opt.plus == 1) { //Если указан флаг +, то флаг пробел игнорируется.
        opt.space = 0;
    }
    return opt;
}
// Если указана точность, то флаг 0 игнорируется. Это справедливо только для целых чисел. 
// Для чисел с плавающей точкой, флаг 0 работает вместе с точностью и шириной поля.
// Если ширина поля не указана, флаг - не оказывает никакого эффекта.
// + Занимает дополнительное место в выводе.

/*

format_options parser_width(const char* format, int* i, format_options opt) {
    while (format[*i] >= '0' && format[*i] <= '9') {
        opt.widthWithouttochka = opt.widthWithouttochka * 10 + (format[*i] - '0');
        (*i)++;
    }
    return opt;
}
 width = width * 10 + (format[*i] - '0') возвращает числовое значение цифры, 
вычитая '0' из ASCII-кода символа. 
Например, если c равен '7', то c - '0' будет равно 7 
(так как коды цифр идут последовательно в таблице ASCII).
ASCII-код символа '0' равен 48.


format_options parser_precision(const char* format, int* i, format_options opt) {
    if (format[*i] == '.') {
        (*i)++;
        while (format[*i] >= '0' && format[*i] <= '9') {
            opt.widthWithtochka = opt.widthWithtochka * 10 + (format[*i] - '0');
            (*i)++;
        }
    }
    return opt;
} */

format_options parser_length(const char* format, int* i, format_options opt) {
    while(format[*i] == 'h' || format[*i] == 'l') {
        switch(format[*i]) {
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


format_options parser_specificators(const char* format, int* i, format_options opt) {
    int flag = 0; // флаг на найденный спецификатор
    while (!flag) {
        switch(format[*i]) {
        case 'c':
            opt.c = 1;
            flag = 1;
            (*i)++;
            continue;
        case 'd':
        case 'i':
            opt.d = 1;
            flag = 1;
            (*i)++;
            continue;
        case 'f':
            opt.f = 1;
            flag = 1;
            (*i)++;
            continue;
        case 'u':
            opt.u = 1;
            flag = 1;
            (*i)++;
            continue;
        case 's':
            opt.s = 1;
            flag = 1;
            (*i)++;
            continue;
        case '%':
            opt.percent = 1;
            flag = 1;
            (*i)++;
            continue;
        default:
            flag = 1;
            (*i)++;
            break;
        }
    }
    return opt;
}

int process_specifiers(va_list args, char* str, format_options opt) {
    int res = 0;
    if (opt.c) {
        res = process_char(va_arg(args, int), str, opt);
    } else if (opt.d) {
        res = process_int(va_arg(args, int), str, opt);
    } else if (opt.f) {
        res = process_float(va_arg(args, double), str, opt);
    } else if (opt.s) {
        res = process_string(va_arg(args, char*), str, opt);
    } else if (opt.u) {
        res = process_unsigned(va_arg(args, unsigned int), str, opt);
    } else if (opt.percent) {
        str[res++] = '%';
    }

    return res;
}



/*format_options parser_specificators(char specificator, va_list args, char* str, Flags* flags, Width* width, Length* length) {
    int res = 0; // счетчик записанных символов
    int flag = 1;
    switch (specificator) {
        case 'c':
            if (flag == 1) {
                res = process_char(va_arg(args, int), str, flags, width); // обработка чара
            // для символа флаги, ширина, точность(но на с она никак не влияет)
            flag = 0;
            }
        case 'd': // подумать как еще можно объединить обработку d и i
        case 'i':
            if (flag == 1) {
                res = process_int(va_arg(args, int), str, flags, width, length); // обработка зцд числа
                // для целого числа флаги, ширина, точность, длина
                flag = 0;
            }
        case 'f':
            if (flag == 1) {
                res = process_float(va_arg(args, double), str, flags, width); // обработка ф
                // для флоата флаги, ширина, точность
                flag = 0;
            }
        case 's':
            if (flag == 1) {
                res = process_string(va_arg(args, char*), str, flags, width); // обработка строки
                flag = 0;
                // для строки флаги, ширина, точность
            }
        case 'u':
            if (flag == 1) {
                res = process_unsigned(va_arg(args, unsigned int), str, flags, width, length); // обработка бцд числа
                // для беззнакового инта ширина, точность, длина
                flag = 0;
            }
        case '%':
            if (flag == 1) {
                str[res++] = '%';
                flag = 0;
            }
    }
    return res;
}*/






// подсчет разрядов в числе 
int count_digits(long long num, int base) {
    int count = 0;
    if (num == 0) {
        count = 1;
    } else {
        while (num != 0) {
        num /= base;
        count++;
        }
    }
    return count;
}


// отзеркаливание строки 
void reverse_s(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

}


int main() {
    const char* format_string = "- 0";
    int index = 0;
    format_options options = {0, 0, 0, 0};
    options = parser_flags(format_string, &index, options);

    printf("minus: %s\n", options.minus ? "true" : "false");
    printf("plus: %s\n", options.plus ? "true" : "false");
    printf("space: %s\n", options.space ? "true" : "false");
    printf("zero: %s\n", options.zero ? "true" : "false");

    return 0;
}
