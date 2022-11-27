#include "s21_string.h"

struct Code_s {
    int minus;
    int plus;
    int space;
    int width;
    int precission;
    int precission_zero;
    char lenght;
    char specifier;
};

typedef struct Code_s Code_t;

void s21_write_to_buf(char **str, const char **format) {
    char *str_local = *str;
    const char *format_local = *format;
    int i = 0;

    while (format_local[i] != '%' && format_local[i] != '\0') {
        str_local[i] = format_local[i];
        i++;
    }
    *str += i;
    *format += i;
}

void s21_long_unsigned_itoa(unsigned long int num, char *str) {
    unsigned long int pow = 1;
    unsigned long int j = 0;

    j = num;
    while (j >= 10) {
        pow *= 10;
        j /= 10;
    }
    while (pow > 0) {
        *str++ = 48 + num / pow;
        num %= pow;
        pow /= 10;
    }
    *str = '\0';
}

void s21_unsigned_itoa(unsigned int num, char *str) {
    unsigned int pow = 1;
    unsigned int j = 0;
        j = num;
        while (j >= 10) {
            pow *= 10;
            j /= 10;
        }
        while (pow > 0) {
            *str++ = 48 + num / pow;
            num %= pow;
            pow /= 10;
        }
        *str = '\0';
}

void s21_itoa(int num, char *str) {
    int pow = 1;
    int j = 0;

    if (num < 0) {
        num = abs(num);
        j = num;
        while (j >= 10) {
            pow = pow * 10;
            j /= 10;
        }
        *str++ = '-';
        while (pow > 0) {
            *str++ = 48 + num / pow;
            num %= pow;
            pow /= 10;
        }
        *str = '\0';
    } else {
        j = num;
        while (j >= 10) {
            pow *= 10;
            j /= 10;
        }
        while (pow > 0) {
            *str++ = 48 + num / pow;
            num %= pow;
            pow /= 10;
        }
        *str = '\0';
    }
}

void s21_long_itoa(long long num, char *str) {
    long long pow = 1;
    long long j = 0;
    // int flag = 0;


    if (num == LONG_MIN) {
        s21_strcpy(str, "9223372036854775808");
    } else if (num < 0) {
        num = labs(num);
        j = num;

        while (j >= 10) {
            pow = pow * 10;
            j /= 10;
        }
        *str++ = '-';
        while (pow > 0) {
            *str++ = 48 + num / pow;
            num %= pow;
            pow /= 10;
        }
        *str = '\0';
    } else {
        j = num;
        while (j >= 10) {
            pow *= 10;
            j /= 10;
        }
        while (pow > 0) {
            *str++ = 48 + num / pow;
            num %= pow;
            pow /= 10;
        }
//         if (flag == 1)
//         {
// //            *str += 1;
//         }
        *str = '\0';
    }
}

void s21_code_parser(const char **format, Code_t *code_params) {
    char specifiers[] = S21_CODE_SPECIFIERS;
    char flags[] = S21_CODE_FLAGS;
    char lenght[] = S21_CODE_LENGTH;

    while (s21_strchr(flags, **format)) {
        if (**format == '+') code_params->plus = '+';
        if (**format == '-') code_params->minus = 1;
        if (**format == ' ') code_params->space = 1;
        (*format)++;
    }
    if (code_params->space > 1)
        code_params->space = 1;

    if (**format >= '1' && **format <= '9') {
        while (**format >= '0' && **format <= '9') {
            code_params->width = code_params->width * 10 + **format - 48;
            (*format)++;
        }
    }
    if (**format == '.') {
        (*format)++;
        code_params->precission_zero = 1;
        while (**format >= '0' && **format <= '9') {
            if (**format >= '1' && **format <= '9')
                code_params->precission_zero = 0;
            code_params->precission = code_params->precission * 10 + **format - 48;
            (*format)++;;
        }
    }


    while (s21_strchr(lenght, **format)) {
        code_params->lenght = **format;
        (*format)++;
    }

    if (s21_strchr(specifiers, **format)) {
        code_params->specifier = **format;
        (*format)++;
    }
}

void    s21_c_formatting(char **str, char arg, Code_t code_params) {
    int width_counter = code_params.width - 1;
    if (code_params.minus == 0) {
        while (width_counter > 0) {
            **str = ' ';
            *str += 1;
            width_counter--;
        }
        **str = arg;
        *str += 1;
    } else if (code_params.minus > 0) {
        **str = arg;
        *str += 1;
        if (code_params.width > 0) {
            while (width_counter > 0) {
                **str = ' ';
                *str += 1;
                width_counter--;
            }
        }
    }
}

void s21_s_formatting(char **str, char *arg, Code_t code_params) {
if (arg == S21_NULL) {
    arg = "(null)";
}
    if ((long unsigned int)code_params.precission > s21_strlen(arg) || code_params.precission == 0)
        code_params.precission = s21_strlen(arg);

    if (code_params.precission_zero)
        code_params.precission = 0;

    if (code_params.minus == 0) {
        if (code_params.width > code_params.precission)
            (code_params.width -= code_params.precission);
        else
            code_params.width = 0;

        int width = code_params.width;

        while (width > 0) {
            **str = ' ';
            (*str)++;
            width -= 1;
        }
    }
    int precission = code_params.precission;

    while (precission != 0) {
        **str = *arg;
        (*str)++;
        arg++;
        precission--;
    }
    if (code_params.minus) {
        if (code_params.width > code_params.precission)
            (code_params.width -= code_params.precission);
        else
        code_params.width = 0;

        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
}

void s21_lu_formatting(char **str, unsigned long arg, Code_t code_params) {
    char number[32];

    code_params.plus = 0;

    s21_long_unsigned_itoa(arg, number);

    if ((long unsigned int)code_params.precission > s21_strlen(number))
        code_params.precission -= s21_strlen(number);
    else
        code_params.precission = 0;
    if (code_params.minus == 0) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                code_params.width -= code_params.precission + 1 + s21_strlen(number);
            else
                code_params.width = 0;
        } else {
            if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                code_params.width -= code_params.precission + s21_strlen(number);
            else
                code_params.width = 0;
        }

        int width = code_params.width;
        while (width > 0) {
            **str = ' ';
            (*str)++;
            width -= 1;
        }
    }
    int precission = code_params.precission;

    while (precission > 0) {
        **str = '0';
        (*str)++;
        precission -= 1;
    }
    s21_strcpy(*str, number);
    *str += s21_strlen(number);

    if (code_params.minus) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                code_params.width -= code_params.precission + 1 + s21_strlen(number);
            else
                code_params.width = 0;

        } else {
            if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                code_params.width -= code_params.precission +  s21_strlen(number);
            else
                code_params.width = 0;
        }

        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
}

void s21_u_formatting(char **str, unsigned long arg, Code_t code_params) {
    char number[32];

    code_params.plus = 0;

    s21_unsigned_itoa(arg, number);

    if ((long unsigned int)code_params.precission > s21_strlen(number))
        code_params.precission -= s21_strlen(number);
    else
        code_params.precission = 0;
    if (code_params.minus == 0) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                code_params.width -= code_params.precission + 1 + s21_strlen(number);
            else
                code_params.width = 0;
        } else {
            if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                code_params.width -= code_params.precission + s21_strlen(number);
            else
                code_params.width = 0;
        }

        int width = code_params.width;
        while (width > 0) {
            **str = ' ';
            (*str)++;
            width -= 1;
        }
    }
    int precission = code_params.precission;

    while (precission > 0) {
        **str = '0';
        (*str)++;
        precission -= 1;
    }
    s21_strcpy(*str, number);
    *str += s21_strlen(number);

    if (code_params.minus) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                code_params.width -= code_params.precission + 1 + s21_strlen(number);
            else
                code_params.width = 0;

        } else {
            if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                code_params.width -= code_params.precission +  s21_strlen(number);
            else
                code_params.width = 0;
        }

        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
}

void s21_d_formatting(char **str, long arg, Code_t code_params) {
    char number[16];
    if (arg < 0) {
        code_params.plus = '-';
        arg = -arg;
    }
    if (code_params.plus)
        code_params.space = 0;

    s21_long_itoa(arg, number);

    if ((long unsigned int)code_params.precission > s21_strlen(number))
        code_params.precission -= s21_strlen(number);
    else
        code_params.precission = 0;
    if (code_params.minus == 0) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                code_params.width -= code_params.precission + 1 + s21_strlen(number);
            else
                code_params.width = 0;
        } else {
            if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                code_params.width -= code_params.precission + s21_strlen(number);
            else
                code_params.width = 0;
        }

        int width = code_params.width;
        while (width > 0) {
            **str = ' ';
            (*str)++;
            width -= 1;
        }
    }
    if (code_params.space && code_params.width == 0 && code_params.plus == 0) {
        **str = ' ';
        (*str)++;
    }
    if (code_params.space && code_params.width != 0 && code_params.minus && code_params.plus == 0) {
        **str = ' ';
        (*str)++;
    }
    if (code_params.plus) {
        **str = code_params.plus;
        (*str)++;
    }
    int precission = code_params.precission;

    while (precission > 0) {
        **str = '0';
        (*str)++;
        precission -= 1;
    }
    s21_strcpy(*str, number);
    *str += s21_strlen(number);

    if (code_params.minus) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > code_params.precission
            + 1 + code_params.space + s21_strlen(number))
                code_params.width -= code_params.precission
                + 1 + code_params.space + s21_strlen(number);
            else
                code_params.width = 0;

        } else {
            if ((long unsigned int)code_params.width > code_params.precission
            + code_params.space + s21_strlen(number))
                code_params.width -= code_params.precission
                + code_params.space +  s21_strlen(number);
            else
                code_params.width = 0;
        }

        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
}


void s21_ld_formatting(char **str, long arg, Code_t code_params) {
        char number[36] = {'\0'};
        if (arg < 0) {
            code_params.plus = '-';
            arg = -arg;
        }
        s21_long_itoa(arg, number);

        if (code_params.plus)
            code_params.space = 0;
        if ((long unsigned int)code_params.precission > s21_strlen(number))
            code_params.precission -= s21_strlen(number);
        else
            code_params.precission = 0;
        if (code_params.minus == 0) {
            if (code_params.plus) {
                if ((long unsigned int)code_params.width > code_params.precission + 1 + s21_strlen(number))
                    code_params.width -= code_params.precission + 1 + s21_strlen(number);
                else
                    code_params.width = 0;
            } else {
                if ((long unsigned int)code_params.width > code_params.precission + s21_strlen(number))
                    code_params.width -= code_params.precission + s21_strlen(number);
                else
                    code_params.width = 0;
            }
            int width = code_params.width;
            while (width > 0) {
                **str = ' ';
                (*str)++;
                width -= 1;
            }
        }

    if (code_params.space && code_params.width == 0) {
        **str = ' ';
        (*str)++;
    }
    if (code_params.space && code_params.width != 0 && code_params.minus) {
        **str = ' ';
        (*str)++;
    }

        if (code_params.plus) {
            **str = code_params.plus;
            (*str)++;
        }
        int precission = code_params.precission;
        while (precission > 0) {
            **str = '0';
            (*str)++;
            precission -= 1;
        }
        s21_strcpy(*str, number);
        *str += s21_strlen(number);

        if (code_params.minus) {
            if (code_params.plus) {
                if ((long unsigned int)code_params.width > code_params.precission
                + code_params.space + 1 + s21_strlen(number))
                    code_params.width -= code_params.precission
                    + code_params.space + 1 + s21_strlen(number);
                else
                    code_params.width = 0;
            } else {
                if ((long unsigned int)code_params.width > code_params.precission
                + code_params.space + s21_strlen(number))
                    code_params.width -= code_params.precission
                    + code_params.space + s21_strlen(number);
                else
                    code_params.width = 0;
            }
            while (code_params.width > 0) {
                **str = ' ';
                (*str)++;
                code_params.width -= 1;
            }
        }
}

void s21_f_formatting(char **str, double arg, Code_t code_params) {
    long double integer = 0;
    long double fract = 0;
    char float_buf[1024] = {'\0'};
    char fract_buf[1024] = {'\0'};
    int i = 0;
    long double character = 0;
    int flag_minus = 0;

    if (code_params.precission == 0 && code_params.precission_zero == 0)
        code_params.precission = 6;

    fract = modfl(arg, &integer);
    if (fract < 0 || fract == -0)
        fract = -fract;

    if (code_params.precission_zero == 0) {
        while (code_params.precission + 1 != 0) {
            fract = modfl(fract * 10, &character);
            fract_buf[i] = (char) (character + 48);
            i++;
            code_params.precission -= 1;
        }
        i--;
        if ((fract_buf[i]) >= '5')
            fract_buf[i - 1] += 1;
        fract_buf[i] = '\0';
        i--;
        for (; (i > 0) && (fract_buf[i] > '9'); i--) {
            fract_buf[i] = '0';
            fract_buf[i - 1] += 1;
        }
        if (fract_buf[0] > '9') {
            fract_buf[0] = '0';
            if (integer < 0)
                integer -= 1;
            else
                integer += 1;
        }
    }
    if (code_params.precission_zero == 1) {
        if ((fract * 10) >= 5) {
            if (integer < 0 || integer == -0)
                integer -= 1;
            else
                integer += 1;
        }
    }
    if (integer == -0) {
        flag_minus = 1;
    }
    s21_long_itoa(integer, float_buf);
    i = 0;
    if (code_params.precission_zero == 0) {
        while (float_buf[i] != '\0')
            i++;
        float_buf[i] = '.';
    }
    s21_strcat(float_buf, fract_buf);

    if (arg < 0) {
        code_params.space = 0;
        code_params.plus = 0;
            if (flag_minus == 1) {
                code_params.plus = '-';
            }
    }
    if (code_params.plus)
        code_params.space = 0;
    if (code_params.minus == 0) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > s21_strlen(float_buf) + 1)
                code_params.width -= s21_strlen(float_buf) + 1;
            else
                code_params.width = 0;
        } else {
            if ((long unsigned int)code_params.width > s21_strlen(float_buf))
                code_params.width -= s21_strlen(float_buf);
            else
                code_params.width = 0;
        }
        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
    if (code_params.space && code_params.width == 0 && code_params.plus == 0) {
        **str = ' ';
        (*str)++;
    }
    if (code_params.space && code_params.width != 0 && code_params.minus && code_params.plus == 0) {
        **str = ' ';
        (*str)++;
    }
    if (code_params.plus) {
        **str = code_params.plus;
        (*str)++;
    }
    s21_strcpy(*str, float_buf);
    *str += s21_strlen(float_buf);

    if (code_params.minus) {
        if (code_params.plus) {
            if ((long unsigned int)code_params.width > s21_strlen(float_buf) + 1 + code_params.space)
                code_params.width -= s21_strlen(float_buf) + 1 + code_params.space;
            else
                code_params.width = 0;
        } else {
            if ((long unsigned int)code_params.width > code_params.space + s21_strlen(float_buf))
                code_params.width -= code_params.space + s21_strlen(float_buf);
            else
                code_params.width = 0;
        }
        while (code_params.width > 0) {
            **str = ' ';
            (*str)++;
            code_params.width -= 1;
        }
    }
}

void s21_arg_to_buffer(char **str, va_list *arg, Code_t code_params) {
    if (code_params.specifier == 'c') {
        s21_c_formatting(str, va_arg(*arg, int), code_params);
    } else if (code_params.specifier == 's') {
        s21_s_formatting(str, va_arg(*arg, char *), code_params);
    } else if (code_params.specifier == 'u' && code_params.lenght == 'l') {
        s21_lu_formatting(str, va_arg(*arg, unsigned long), code_params);
    } else if (code_params.specifier == 'u') {
         s21_u_formatting(str, va_arg(*arg, unsigned int), code_params);
    } else if (code_params.lenght == 'l' && code_params.specifier == 'd') {
        s21_ld_formatting(str, va_arg(*arg, long), code_params);
    } else if (code_params.lenght == 'h' && code_params.specifier == 'd') {
        short int i = va_arg(*arg, int);
        s21_d_formatting(str, i, code_params);
    } else if (code_params.specifier == 'd') {
        s21_d_formatting(str, va_arg(*arg, int), code_params);
    } else if (code_params.specifier == 'i' && code_params.lenght == 'l') {
        s21_ld_formatting(str, va_arg(*arg, long), code_params);
    } else if (code_params.specifier == 'i') {
        s21_d_formatting(str, va_arg(*arg, int), code_params);
    } else if (code_params.specifier == '%') {
            s21_c_formatting(str, '%', code_params);
    } else if (code_params.specifier == 'f') {
        double i = va_arg(*arg, double);
        s21_f_formatting(str, i , code_params);
    }
}

void s21_if_code(char **str, const char **format, va_list *arg) {
    Code_t code_params = {0};

    *format += 1;
    s21_code_parser(format, &code_params);
    s21_arg_to_buffer(str, arg, code_params);
}

int s21_sprintf(char *str, const char *format, ...) {
    char    *start;
    va_list arg;
    va_start(arg, format);
    start = str;
    while (*format != '\0') {
        if (*format == '%') {
            s21_if_code(&str, &format, &arg);
        } else {
            s21_write_to_buf(&str, &format);
        }
    }
    va_end(arg);
    return (s21_strlen(start));
}
