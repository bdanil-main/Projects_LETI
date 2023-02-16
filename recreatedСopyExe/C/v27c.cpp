#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <conio.h>
int main() {
    printf("%s", "Please, enter 5 unsigned decimal numbers from 0 to 255 inclusively:\n");
    unsigned char num[5] = { 0, 0, 0, 0, 0 };
    for (unsigned char i = 0; i < 5; i++) {
        scanf("%hhu", &num[i]);
    }
    printf("%s", "\n\nEntered numbers (decimal):\n");
    for (unsigned int i = 0; i < 5; i++) {
        printf("%hhu ", num[i]);
    }
    uint8_t M = 0x4D, Z = 0x5A;
    for (unsigned int i = 0; i < 5; i++) {
        num[i] = (num[i] ^ Z) | (M & i);
    }
    printf("%s", "\n\nResult (decimal):\n");
    for (unsigned int i = 0; i < 5; i++) {
        printf("%hhu ", num[i]);
    }
    printf("%s", "\n\nPress any key...\n");
    _getch();
}