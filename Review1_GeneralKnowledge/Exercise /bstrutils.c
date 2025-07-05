#include "strutils.h"
#include <stdio.h>

static uint32_t lengthString(char *str) {
    uint32_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void str_reverse(char *str) {
    uint32_t lengStr = lengthString(str);           

    for (uint32_t i = 0; i < lengStr / 2; i++) {
        char tmp = str[i];
        str[i] = str[lengStr - 1 - i];
        str[lengStr - 1 - i] = tmp;
    }
}

void str_trim(char *str) {
    uint32_t firstCharPos = 0;
    uint32_t lastCharPos = lengthString(str) - 1; // kí tự -> vị trí

    while (str[firstCharPos] == ' ') {
        firstCharPos++;
    }
    while (str[lastCharPos] == ' ') {
        lastCharPos--;
    }

    uint32_t newPos = 0;
    for (int i = firstCharPos; i <= lastCharPos; i++) {
        str[newPos] = str[i];
        newPos++;
    }
    str[newPos] = '\0';
}

int str_to_int(const char *str, int *out_num) {
    uint32_t result = 0;
    uint8_t check = 1; // Giả sử ban đầu là dương   
    
    // Xử lý khoảng trắng đầu 
    while (*str == ' ') {
        str++;
    }

    // Kiểm tra dấu
    if (*str == '-') {
        check = 0;
        str++;
    }

    // Phía sau dấu ko có số thì lỗi
    if (*str < '0' || *str > '9') {
        return 0;
    }

    //Duyệt 
    while(*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        } else {    // gặp chữ thì out
            return 0;
        }
        str++;
    }

    if (check == 0) {
        result = -result;
    }

    *out_num = result;

    return 1;
}