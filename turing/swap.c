#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int a, b, c;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    //Klasszikus megoldás segédváltozóval:
    c = a;
    a = b;
    b = c;
    printf("swapped: %d %d\n", a, b);

    //Kivonással:
    a -= b;
    b += a;
    a = b - a;
    printf("swapped back: %d %d\n", a, b);

    //Bitenkénti XOR-ral:
    a ^= b;
    b ^= a;
    a ^= b;
    printf("swapped: %d %d\n", a, b);

    //Lassú, nem túl biztonságos, de ha nagyon akarjuk, ilyet is lehet:
    char buffer[32];

    snprintf(buffer, 32, "%d %d", b, a);
    sscanf(buffer, "%d %d", &a, &b);
    printf("swapped back: %d %d\n", a, b);

    return 0;
}