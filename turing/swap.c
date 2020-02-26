#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int a, b, c;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    //classic swap with 3d variable
    c = a;
    a = b;
    b = c;
    printf("swapped: %d %d\n", a, b);

    //with subtraction
    a -= b;
    b += a;
    a = b - a;
    printf("swapped back: %d %d\n", a, b);

    //with bitwise XOR
    a ^= b; //11101100 01011100 -> 10110000 01011100
    b ^= a; //10110000 01011100 -> 10110000 11101100
    a ^= b; //10110000 11101100 -> 01011100 11101100
    printf("swapped: %d %d\n", a, b);

    //slow, unsafe but why not
    char buffer[32];

    snprintf(buffer, sizeof(char) * 32, "%d %d", b, a);
    sscanf(buffer, "%d %d", &a, &b);
    printf("swapped back: %d %d\n", a, b);

    return 0;
}