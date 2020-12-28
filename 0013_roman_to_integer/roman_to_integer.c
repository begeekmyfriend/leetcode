#include <stdio.h>
#include <stdlib.h>

static int roman_to_integer(char c)
{
    switch(c) {
    case 'I':  
        return 1;  
    case 'V':  
        return 5;  
    case 'X':  
        return 10;  
    case 'L':  
        return 50;  
    case 'C':  
        return 100;  
    case 'D':  
        return 500;  
    case 'M':  
        return 1000;  
    default:
        return 0;
    }
}

int romanToInt (char *s)
{
    int i, curr = roman_to_integer(s[0]);
    int result = curr;

    for (i = 1; s[i] != '\0'; i++) {
        int prev = curr;
        curr = roman_to_integer(s[i]);
        /* left < right : IV(4), XL(40), IX(9) ... */
        if (prev < curr) {
            result -= prev - (curr - prev);
        } else {
            result += curr;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test roman\n");
        exit(-1);
    }
    printf("%d\n", romanToInt(argv[1]));
    return 0;
}
