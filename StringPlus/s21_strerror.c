#include "s21_string.h"

char *s21_strerror(int errnum) {
    char* arroferrors[] = _ERRORS_LIST_;
    char* retstr;
    char error[4096] = {'\0'};
    char stt[10];
    #if defined __APPLE__
    if (errnum < 0 || errnum > _ERRORS_MAX_) {
    s21_itoa(errnum, stt);
    s21_strcpy(error, "Unknown error: ");
    retstr = s21_strncat(error, stt, s21_strlen(error));
    } else {
    retstr = arroferrors[errnum];
    }
    #elif defined __linux__
    if (errnum < 0 || errnum > _ERRORS_MAX_) {
    s21_itoa(errnum, stt);
    s21_strcpy(error, "Unknown error ");
    retstr = s21_strncat(error, stt, s21_strlen(error));
    } else {
    retstr = arroferrors[errnum];
    }
    #endif
    return retstr;
}
