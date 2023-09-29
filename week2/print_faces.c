#include <stdio.h>

int main() {
    char eye1 = ' ';
    char eye2 = ' ';
    char nose = ' ';
    char mouth = ' ';
    char line1_1 = ' ';
    char line1_2 = ' ';
    char line1_3 = ' ';
    char line2_1 = 'O';
    char line2_2 = ' ';
    char line2_3 = 'O';
    char line3_1 = ' ';
    char line3_2 = ' ';
    char line3_3 = ' ';
    char line4_1 = ' ';
    char line4_2 = ' ';
    char line4_3 = ' ';

    printf("How do you want to build a face?: ");

    scanf("%c%c%c%c", &eye1, &eye2, &nose, &mouth);

    char eye1Code, eye2Code, noseCode, mouthCode;

    if (mouth == 'g' || mouth == 'h' || mouth == 'i') {
        eye1Code = eye1;
        eye2Code = eye2;
        noseCode = nose;
        mouthCode = mouth;
    } else {
        eye1Code = eye1;
        eye2Code = eye1;
        noseCode = eye2;
        mouthCode = nose;
    }

    if (eye1Code == 'a') {
        line1_1 = '_';
    } else if (eye1Code == 'b') {
        line1_1 = '~';
    } else if (eye1Code == 'c') {
        line1_1 = '\\';
    } else if (eye1Code == 'd') {
        line1_1 = '/';
    } else {
        line1_1 = ' ';
    }

    if (eye2Code == 'a') {
        line1_3 = '_';
    } else if (eye2Code == 'b') {
        line1_3 = '~';
    } else if (eye2Code == 'c') {
        line1_3 = '\\';
    } else if (eye2Code == 'd') {
        line1_3 = '/';
    } else {
        line1_3 = ' ';
    }

    if (noseCode == 'e') {
        line3_2 = '^';
    } else if (noseCode == 'f') {
        line3_2 = '~';
    } else {
        line3_2 = ' ';
    }

    if (mouthCode == 'g') {
        line4_1 = '\\';
        line4_2 = '_';
        line4_3 = '/';
    } else if (mouthCode == 'h') {
        line4_1 = '/';
        line4_2 = '-';
        line4_3 = '\\';
    } else if (mouthCode == 'i') {
        line4_1 = ' ';
        line4_2 = 'o';
        line4_3 = ' ';
    } else {
        line4_1 = ' ';
        line4_2 = ' ';
        line4_3 = ' ';
    }

    printf("%c%c%c\n", line1_1, line1_2, line1_3);
    printf("%c%c%c\n", line2_1, line2_2, line2_3);
    printf("%c%c%c\n", line3_1, line3_2, line3_3);
    printf("%c%c%c\n", line4_1, line4_2, line4_3);

    return 0;
}