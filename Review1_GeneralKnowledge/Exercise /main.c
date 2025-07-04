#include <stdio.h>
#include <string.h>
#include "strutils.h" 

int main() {
    char str1[100] = "Hello World";
    char str2[100] = "   Trim me   ";
    char str3[100];
    int number;

    // Test str_reverse
    printf("=== Test str_reverse ===\n");
    printf("Original: '%s'\n", str1);
    str_reverse(str1);


    // Test str_trim
    printf("=== Test str_trim ===\n");
    printf("Before trim: '%s'\n", str2);
    str_trim(str2);


    // Test str_to_int
    printf("=== Test str_to_int ===\n");
    printf("Enter the number string : ");
    fgets(str3, sizeof(str3), stdin);
    str3[strcspn(str3, "\n")] = '\0';  // Xoá '\n'

    if (str_to_int(str3, &number)) {
        printf("Successfull Conversion: %d\n", number);
    } else {
        printf("ERROR!\n");
    }

    return 0;
}
