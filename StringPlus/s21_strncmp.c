#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    unsigned int i;
    int flag = 0;
    i = 0;
    while ((str1[i] || str2[i]) && (i < n)) {
        if (str1[i] < str2[i])
            flag = -1;
        if (str1[i] > str2[i])
            flag = 1;
        i++;
    }
    return flag;
}
