#include "s21_string.h"

void s21_reverse_string(char *line_for_num, int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        char buffer = line_for_num[i];
        line_for_num[i] = line_for_num[j];
        line_for_num[j] = buffer;
    }
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *final = S21_NULL;
    if (src) {
        char *str = (char *)src;
        s21_size_t len = s21_strlen(str);
        if (!trim_chars || trim_chars[0] == '\0') {
            trim_chars = " ";
        }
        if (len > 0) {
            s21_reverse_string(str, len);
            int right_side = s21_strspn(str, trim_chars);
            s21_reverse_string(str, len);
            int left_side = s21_strspn(str, trim_chars);
            int new_size = len - left_side - right_side;
            if (new_size < 0) {
                new_size = 0;
            }
            str += left_side;
            final = (char *)calloc(new_size + 1, sizeof(char));
            if (final) {
                s21_strncpy(final, str, new_size);
            }
        } else {
            final = (char *)calloc(1, sizeof(char));
        }
    }

    return final;
}
