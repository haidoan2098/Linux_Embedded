#include <stdio.h>
#include <string.h>
#include "strutils.h"  // Giả định bạn đã định nghĩa các hàm trong file này

int main() {
    // Test str_reverse
    char str1[] = "Embedded";
    printf("Original: %s\n", str1);
    str_reverse(str1);
    printf("Reversed: %s\n", str1);

    // Test str_trim
    char str2[] = "   Hello, world!   ";
    printf("\nOriginal with spaces: \"%s\"\n", str2);
    str_trim(str2);
    printf("Trimmed: \"%s\"\n", str2);

    // Test str_to_int
    const char *str3 = "12345";
    const char *str4 = "abc123";
    int number;

    if (str_to_int(str3, &number) == 1) {
        printf("\nConverted '%s' to integer: %d\n", str3, number);
    } else {
        printf("\nFailed to convert '%s' to integer.\n", str3);
    }

    if (str_to_int(str4, &number) == 1) {
        printf("Converted '%s' to integer: %d\n", str4, number);
    } else {
        printf("Failed to convert '%s' to integer.\n", str4);
    }

    return 0;
}
